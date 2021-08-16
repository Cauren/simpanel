// SimpanelPlug.cpp : Defines the entry point for the application.
//

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "simconnect.lib")
#pragma comment(lib, "comctl32.lib")

// I fucking *know* how to use str[n]cpy safely, Microsoft!
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <cfgmgr32.h>
#include <hidsdi.h>
#include <hidpi.h>
#include <SetupAPI.h>
#include <stdio.h>
#include <Dbt.h>
#include <WinUser.h>
#include <strsafe.h>
#include <shellapi.h>

#include <assert.h>
#include <wrl.h>
#include <WebView2.h>
using Microsoft::WRL::Callback;

#include "framework.h"
#include "SimpanelPlug.h"
#include "Resource.h"

#include <SimConnect.h>
#include <cstring>
#include <string>

CRITICAL_SECTION cs_Expressions;
CRITICAL_SECTION cs_Devices;


struct GaugeExpression {
    enum State {
        Free, Updated, Sent, Invalid, Valid, Set, Get, Stale,
    };

    State   state;
    const char* expression;
    union {
        double  value;
        int     next;
    };

    GaugeExpression(void) : state(Free), expression(0), next(-1) { };
    ~GaugeExpression() { empty(); };

    GaugeExpression& operator = (const char* exp) {
        empty();
        state = Updated;
        char* x = new char[strlen(exp) + 1];
        strcpy(x, exp);
        expression = x;
        return *this;
    }

    void empty(void) {
        state = Free;
        if (expression)
            delete[] expression;
        expression = 0;
    }

    void setup(void);
    void fire(double parm = 0.0);
};

static GaugeExpression gexp[256];
static int gfree = -1;
static const char* current_plane = 0;
static bool current_plane_changed = false;

int ge_alloc()
{
    int e = gfree;
    if (e >= 0) {
        gfree = gexp[e].next;
        gexp[e].state = GaugeExpression::Updated;
        return e;
    }
    return e;
}

void ge_free(int e)
{
    if (e < 0)
        return;
    gexp[e].empty();
    gexp[e].next = gfree;
    gfree = e;
}

enum GaugeInputCommands {
    GISetExpr, GIEvaluate,
};

enum GaugeOutputResults {
    GIError, GIOk, GIMore, GIComplete,
};

struct GaugeInputStruct
{
    UINT32	sequence;
    UINT16	command;
    UINT16	param;
    char	data[248];
};

struct GaugeOutputStruct
{
    UINT32	sequence;
    UINT16	result;
    UINT16	count;
    struct {
        UINT16 index;
        UINT16 valid;
        double value;
    }		values[20];
};

struct GaugeRequest : public GaugeInputStruct {
    static GaugeRequest* head;
    static GaugeRequest* tail;
    static UINT32 rn;

    GaugeRequest* prev;
    GaugeRequest* next;
    bool sent;

    GaugeRequest(GaugeInputCommands cmd);
    ~GaugeRequest();
    void send(void);
};

GaugeRequest* GaugeRequest::head = 0;
GaugeRequest* GaugeRequest::tail = 0;
UINT32 GaugeRequest::rn = 1;

GaugeRequest::GaugeRequest(GaugeInputCommands cmd)
{
    command = cmd;
    sent = false;
}

void GaugeRequest::send(void)
{
    sequence = rn++;
    if (prev = tail)
        tail->next = this;
    else
        head = this;
    next = 0;
    tail = this;
}

GaugeRequest::~GaugeRequest()
{
    if (sent) {
        (next ? next->prev : tail) = prev;
        (prev ? prev->next : head) = next;
    }
}

struct EvaluateRequest {
    size_t numx;
    UINT16 xnum[256];
    double xval[256];

    EvaluateRequest(void) : numx(0) { };

    void add(UINT16 i, double v = 0.0) { xnum[numx] = i; xval[numx++] = v; }
    void request(void) {
        if (numx == 0)
            return;
        size_t sent = 0;
        static const size_t max_per_req = 248 / (sizeof(double) + sizeof(UINT16));
        while (sent < numx) {
            size_t send = numx - sent;
            if (send > max_per_req)
                send = max_per_req;
            GaugeRequest* req = new GaugeRequest(GIEvaluate);
            req->param = send;
            for (int i = 0; i < send; i++) {
                reinterpret_cast<double*>(req->data)[i] = xval[sent + i];
                reinterpret_cast<UINT16*>(req->data + sizeof(double) * send)[i] = xnum[sent + i];
            }
            req->send();
            sent += send;
        }
    }
};




struct Expression {
    std::string expression;
    bool fixed;
    bool val;
    UINT16 index;

    Expression(void) : fixed(true), val(false) { };
    ~Expression() { blank(); };

    void blank(void);
    Expression& operator = (const char*);
    Expression& operator = (bool f) { blank(); val = f; expression.clear(); return *this; }

    operator bool(void) { return fixed ? val : ((gexp[index].state == GaugeExpression::Valid) ? gexp[index].value: false); };
    double value(void) { return fixed ? val : ((gexp[index].state == GaugeExpression::Valid) ? gexp[index].value : 0.0); };

    void add(EvaluateRequest& ev, double val = 0.0) {
        if (fixed)
            return;
        if (gexp[index].state != GaugeExpression::Updated)
            ev.add(index, val);
        gexp[index].value = val;
    }

};

void Expression::blank(void)
{
    if (!fixed)
        ge_free(index);
    fixed = true;
    val = false;
}

Expression& Expression::operator=(const char* exp)
{
    if (exp && exp[0]) {
        if (!fixed && expression == exp)
            return *this;
        if (fixed) {
            fixed = false;
            index = ge_alloc();
        }
        expression = exp;
        gexp[index] = expression.c_str();
    }
    else
        blank();
    
    return *this;
}

DWORD WINAPI device_thread_reader(void*);

struct Device {
    struct Setting {
        enum SettingType {
            Action, GetExpression, SetExpression, Value, Enumerator,
        };
        std::string control;
        std::string label;
        union {
            Expression* expression;
            double* value;
            UINT32* enumer;
        };
        SettingType type;
    };

    std::string name;
    std::basic_string<wchar_t> serial;
    Device* next;
    HANDLE hid;
    HANDLE whid;
    HANDLE reader_thread;
    bool end_reader;
    Setting* settings;
    size_t num_settings;
    bool active;

    Device(const char* n, HANDLE h, HANDLE wh, size_t ns) : name(n), next(0), hid(h), whid(wh), settings(new Setting[ns]), num_settings(0), active(true)
    {
        end_reader = false;
        reader_thread = CreateThread(0, 0, device_thread_reader, this, 0, 0);
    };
    ~Device() {
        end_reader = true;
        WaitForSingleObject(reader_thread, INFINITE);
        delete[] settings;
    };

    Setting& add(const std::string& c, const std::string& l, Setting::SettingType t) {
        Setting& s = settings[num_settings++];
        s.control = c;
        s.label = l;
        s.type = t;
        return s;
    };
    void add(const std::string& c, const std::string& l, Expression* exp, Setting::SettingType st = Setting::Action) {
        add(c, l, st).expression = exp;
    };
    void add(const std::string& c, const std::string& l, double* val) {
        add(c, l, Setting::Value).value = val;
    };
    void add(const std::string& c, const std::string& l, UINT32* val) {
        add(c, l, Setting::Enumerator).enumer = val;
    };

    virtual unsigned char in_report_id(void) { return 0; };
    virtual size_t in_report_len(void) { return 0; };
    virtual void recv_hid_report(void* buf, size_t len) = 0;
    virtual void update(void) = 0;
    virtual void load_plane(const char*) = 0;
};

DWORD WINAPI device_thread_reader(void* dp)
{
    Device* device = reinterpret_cast<Device*>(dp);
    size_t in_report_len = device->in_report_len();
    unsigned char in_report_id = device->in_report_id();
    unsigned char* in_report = new unsigned char[in_report_len];

    while (!device->end_reader) {
        DWORD read_len;
        if (ReadFile(device->hid, in_report, in_report_len, &read_len, 0)) {
            if (read_len == in_report_len && in_report[0] == in_report_id) {
                device->recv_hid_report(in_report + 1, in_report_len - 1);
            }
        }
        else
            break;
    }
    device->end_reader = true;
    delete[] in_report;
    return 0;
}

// workflow: on 6Hz:
//   (a) if plane changed, load settings
//   (b) update all new expressions
//   (c) make a list of expression to evaluate and send it
//   -- after all expressions evaluated --
//   (d) panel->update()

struct SPDial {
    enum ValueType {
        Blank, Error, Track, IAS, Mach, VS, Angle, Altitude,
    };
    Expression mode_select;
    struct Set {
        Expression active;
        Expression value;
        UINT32 value_type;
        Expression set_value;
        double unpressed_scale;
        double pressed_scale;
        Expression press_action;
    } mode[2];

    void add_settings(Device* dev, const std::string& label) {
        dev->add(label, "mode select", &mode_select, Device::Setting::GetExpression);
        dev->add(label, "mode 1 active", &mode[0].active, Device::Setting::GetExpression);
        dev->add(label, "mode 1 value", &mode[0].value, Device::Setting::GetExpression);
        dev->add(label, "mode 1 value type", &mode[0].value_type);
        dev->add(label, "mode 1 unpressed scale", &mode[0].unpressed_scale);
        dev->add(label, "mode 1 pressed scale", &mode[0].pressed_scale);
        dev->add(label, "mode 1 set value", &mode[0].set_value, Device::Setting::SetExpression);
        dev->add(label, "mode 1 press action", &mode[0].press_action);
        dev->add(label, "mode 2 active", &mode[1].active, Device::Setting::GetExpression);
        dev->add(label, "mode 2 value", &mode[1].value, Device::Setting::GetExpression);
        dev->add(label, "mode 2 value type", &mode[1].value_type);
        dev->add(label, "mode 2 unpressed scale", &mode[1].unpressed_scale);
        dev->add(label, "mode 2 pressed scale", &mode[1].pressed_scale);
        dev->add(label, "mode 2 set value", &mode[1].set_value, Device::Setting::SetExpression);
        dev->add(label, "mode 2 press action", &mode[1].press_action);
    };
};

struct SPButton {
    Expression led_value;
    Expression press_action;

    void add_settings(Device* dev, const std::string& label) {
        dev->add(label, "led value", &led_value, Device::Setting::GetExpression);
        dev->add(label, "press action", &press_action);
    };
};

struct SPSwitch {
    Expression set_action;
    Expression reset_action;

    void add_settings(Device* dev, const std::string& label) {
        dev->add(label, "on action", &set_action);
        dev->add(label, "off action", &reset_action);
    };
};


struct SIMPANEL_AP_rev_C: public Device {

    signed short    dial_delta[4];
    bool            dial_closed[4];
    bool            dial_pushed[4];
    bool            leds[11];
    bool            button_closed[11];
    bool            button_pushed[11];
    bool            switch_closed[20];
    bool            switch_on[20];

    SPDial d[4];
    SPButton b[11];
    SPSwitch sw[20];

    SIMPANEL_AP_rev_C(HANDLE hid, HANDLE whid): Device("SimPanel A/P rev. C", hid, whid, 122) {
        for (int i = 0; i < 4; i++) {
            dial_delta[i] = 0;
            dial_closed[i] = dial_pushed[i] = false;
        }
        for (int i = 0; i < 11; i++)
            button_closed[i] = button_pushed[i] = leds[i] = false;
        for (int i = 0; i < 20; i++)
            switch_closed[i] = switch_on[i] = false;

        d[0].add_settings(this, "Speed");
        d[1].add_settings(this, "Heading");
        d[2].add_settings(this, "VS");
        d[3].add_settings(this, "Altitude");
        b[1].add_settings(this, "Button 1");
        b[10].add_settings(this, "Button 2");
        b[7].add_settings(this, "Button 3");
        b[8].add_settings(this, "Button 4");
        b[9].add_settings(this, "Button 5");
        b[6].add_settings(this, "Button 6");
        b[5].add_settings(this, "Button 7");
        b[4].add_settings(this, "Button 8");
        b[0].add_settings(this, "Button 9");
        b[2].add_settings(this, "Button 10");
        b[3].add_settings(this, "Button 11");
        for (int i = 0; i < 20; i++)
            sw[i].add_settings(this, "Switch " + std::to_string(i));
        if (current_plane)
            load_plane(current_plane);
    }

    virtual unsigned char in_report_id(void) { return 1; };
    virtual size_t in_report_len(void) { return 10; };
    virtual void recv_hid_report(void* buf, size_t len);
    virtual void update(void);
    virtual void load_plane(const char*);
};

void SIMPANEL_AP_rev_C::recv_hid_report(void* buf, size_t len)
{
    struct in_report {
        unsigned char dials[4];
        unsigned char buttons[2];
        unsigned char switches[3];
    };

    in_report* report = reinterpret_cast<in_report*>(buf);
    if (len != sizeof(in_report))
        return;
    for (int d = 0; d < 4; d++) {
        if (report->dials[d] & 0x80) {
            if (!dial_closed[d])
                dial_pushed[d] = true;
            dial_closed[d] = true;
        }
        else {
            dial_closed[d] = false;
        }
        signed short delta = ((report->dials[d] & 0x40) ? 0xFFC0: 0) | (report->dials[d]&0x3f);
        dial_delta[d] += delta;
    }
    for (int b = 0; b < 11; b++) {
        if (report->buttons[b >> 3] & (1 << (b & 7))) {
            if (!button_closed[b])
                button_pushed[b] = true;
            button_closed[b] = true;
        }
        else {
            button_closed[b] = false;
        }
    }

    for (int s = 0; s < 20; s++) {
        switch_closed[s] = report->switches[s >> 3] & (1 << (s & 7));
    }
}

void SIMPANEL_AP_rev_C::update(void)
{
    struct {
        unsigned char id;
        unsigned char digits[18];
        unsigned char leds[2];
    } out_report;

    EvaluateRequest ev;

    for (int i = 0; i < 11; i++) {
        leds[i] = b[i].led_value;
        if (button_pushed[i]) {
            b[i].press_action.add(ev);
            button_pushed[i] = false;
        }
    }

    for (int i = 0; i < 20; i++) {
        if (switch_on[i] && !switch_closed[i]) {
            switch_on[i] = false;
            sw[i].reset_action.add(ev);
        }
    }
    for (int i = 0; i < 20; i++) {
        if (switch_closed[i] && !switch_on[i]) {
            switch_on[i] = true;
            sw[i].set_action.add(ev);
        }
    }

    static const int disp_offset[4] = { 0, 3, 6, 12 };
    static const int disp_width[4] = { 3, 3, 6, 6 };
    static const unsigned char sevenseg[] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66,
        0x6D, 0x7D, 0x07, 0x7F, 0x6F,
        0x00, 0x40, 0x49, 0x63, 0x08,
    };
    for (int i = 0; i < 4; i++) {
        SPDial::Set& mode = d[i].mode_select ? d[i].mode[1] : d[i].mode[0];
        SPDial::ValueType vt = static_cast<SPDial::ValueType>(mode.value_type);
        double val = mode.value.value();

        if (mode.active) {
            bool change = false;
            double scale = dial_closed[i] ? mode.pressed_scale : mode.unpressed_scale;
            if (dial_delta[i] > 0) {
                val = (floor(val / scale) + dial_delta[i]) * scale;
                change = true;
            }
            else if (dial_delta[i] < 0) {
                val = (ceil(val / scale) + dial_delta[i]) * scale;
                change = true;
            }
            dial_delta[i] = 0;
            if (change) {
                switch (vt) {
                case SPDial::Track:
                    while (val < 0)
                        val += 360;
                    while (val >= 360)
                        val -= 360;
                    break;
                case SPDial::IAS:
                    if (val < 0)
                        val = 0.0;
                    break;
                }
                mode.set_value.add(ev, val);
            }
            if (dial_pushed[i]) {
                mode.press_action.add(ev);
                dial_pushed[i] = false;
            }
        }
        else
            vt = SPDial::Blank;

        char pad[8] = "-------";

        switch (vt) {
        case SPDial::Blank:
            pad[0] = 0;
            break;
        case SPDial::Error:
            break;
        case SPDial::Track:
            sprintf(pad, "%03d", int(val));
            break;
        case SPDial::Mach:
            sprintf(pad, "%3.2g", val);
            break;
        case SPDial::VS:
            sprintf(pad, "%5d", int(val));
            break;
        case SPDial::Angle:
            sprintf(pad, "%+4.2go", val);
            break;
        case SPDial::IAS:
        case SPDial::Altitude:
            sprintf(pad, "%6ld", long(val));
            break;
        }

        int pi = strlen(pad);
        int di = 0;
        unsigned char* dp = out_report.digits + disp_offset[i];

        for (di = 0; di < disp_width[i]; di++)
            dp[di] = 0;
        while (di-- > 0 && pi-- > 0) {
            switch (pad[pi]) {
            case '.':
                dp[di++] |= 0x80;
                break;
            case '-':
                dp[di] |= sevenseg[11];
                break;
            case ' ':
                dp[di] |= sevenseg[10];
                break;
            case 'o':
                dp[di] |= sevenseg[13];
                break;
            case '+':
                dp[di] |= sevenseg[14];
                break;
            default:
                dp[di] |= sevenseg[(pad[pi] >= '0' && pad[pi] <= '9') ? pad[pi] - '0' : 12];
                break;
            }
        }

    }

    ev.request();

    out_report.id = 2;
    out_report.leds[0] = 0;
    out_report.leds[1] = 0;
    for (int i = 0; i < 3; i++)
        if (leds[i])
            out_report.leds[0] |= 0x04 >> i;
    for (int i = 0; i < 8; i++)
        if (leds[3+i])
            out_report.leds[1] |= 1 << (7-i);
    WriteFile(whid, &out_report, 21, 0, 0);
}

void SIMPANEL_AP_rev_C::load_plane(const char*)
{
    // Right now, we hardcode "TBM 930 Asobo"

    // Dial 0 is configured with sane defaults, but not active
    // because we don't have a 940.  :-)
    d[0].mode_select = "(L:XMLVAR_AirSpeedIsInMach,Bool)";
    d[0].mode[0].active = true;
    d[0].mode[0].pressed_scale = 1.0;
    d[0].mode[0].unpressed_scale = 1.0;
    d[0].mode[0].value_type = SPDial::IAS;
    d[0].mode[0].value = "(A:AUTOPILOT AIRSPEED HOLD VAR, knots)";
    d[0].mode[0].set_value = "(L:GCVAL) (>K:AP_SPD_VAR_SET)";
    d[0].mode[0].press_action = "1 (>L:XMLVAR_AirSpeedIsInMach)";
    d[0].mode[1].active = true;
    d[0].mode[1].pressed_scale = 0.01;
    d[0].mode[1].unpressed_scale = 0.01;
    d[0].mode[1].value_type = SPDial::Mach;
    d[0].mode[1].value = "(A:AUTOPILOT MACH HOLD VAR, number)";
    d[0].mode[1].set_value = "(L:GCVAL) (>K:AP_MACH_VAR_SET)";
    d[0].mode[1].press_action = "0 (>L:XMLVAR_AirSpeedIsInMach)";

    d[1].mode_select = false;
    d[1].mode[0].active = true;
    d[1].mode[0].pressed_scale = 10.0;
    d[1].mode[0].unpressed_scale = 1.0;
    d[1].mode[0].value_type = SPDial::Track;
    d[1].mode[0].value = "(A:AUTOPILOT HEADING LOCK DIR,degrees)";
    d[1].mode[0].set_value = "(L:GCVAL) (>K:HEADING_BUG_SET)";
    d[1].mode[0].press_action = false;

    d[2].mode_select = false;
    d[2].mode[0].active = "(A:AUTOPILOT VERTICAL HOLD,bool)";
    d[2].mode[0].pressed_scale = 100.0;
    d[2].mode[0].unpressed_scale = 100.0;
    d[2].mode[0].value_type = SPDial::VS;
    d[2].mode[0].value = "(A:AUTOPILOT VERTICAL HOLD VAR,feet/minute)";
    d[2].mode[0].set_value = "(L:GCVAL) (>K:AP_VS_VAR_SET_ENGLISH)";
    d[2].mode[0].press_action = false;

    d[3].mode_select = false;
    d[3].mode[0].active = true;
    d[3].mode[0].pressed_scale = 100.0;
    d[3].mode[0].unpressed_scale = 1000.0;
    d[3].mode[0].value_type = SPDial::Altitude;
    d[3].mode[0].value = "(A:AUTOPILOT ALTITUDE LOCK VAR, feet)";
    d[3].mode[0].set_value = "(L:GCVAL) (>K:AP_ALT_VAR_SET_ENGLISH)";
    d[2].mode[0].press_action = false;

    // A/T
    b[1].led_value = "(A:PITOT HEAT SWITCH:2, Bool)"; // "(A:AUTOPILOT THROTTLE ARM,bool)";
    b[1].press_action = "123 'DEICE_Engine_1_Toggle' (>F:InputEvent)"; // "(>K:AUTO THROTTLE ARM)";
    // SPD but we use it for bank limit in the TBM
    b[10].led_value = "(A:AUTOPILOT MAX BANK,degrees) 30 <";
    b[10].press_action = "(A:AUTOPILOT MAX BANK, degrees) 30 < if{ (>K:AP_MAX_BANK_INC) } els{ (>K:AP_MAX_BANK_DEC) }";
    // LNAV
    b[7].led_value = "(A:AUTOPILOT NAV1 LOCK,bool)";
    b[7].press_action = "(>K:AP_NAV1_HOLD)";
    // VNAV
    b[8].led_value = "(L:XMLVAR_VNAVButtonValue)";
    b[8].press_action = "(L:XMLVAR_VNAVButtonValue) ! (>L:XMLVAR_VNAVButtonValue)";
    // FLCH
    b[9].led_value = "(A:AUTOPILOT FLIGHT LEVEL CHANGE, bool)";
    b[9].press_action = "(>K:FLIGHT_LEVEL_CHANGE) (A:AIRSPEED INDICATED, knots) (>K:AP_SPD_VAR_SET)";
    // HDG HOLD
    b[6].led_value = "(A:AUTOPILOT HEADING LOCK,bool)";
    b[6].press_action = "(>K:AP_HDG_HOLD)";
    // VS HOLD
    b[5].led_value = "(A:AUTOPILOT VERTICAL HOLD,bool)";
    b[5].press_action = "(>K:AP_PANEL_VS_HOLD)";
    // ALT HOLD
    b[4].led_value = "(A:AUTOPILOT ATTITUDE HOLD,bool)";
    b[4].press_action = "(>K:AP_ALT_HOLD)";
    // A/P MASTER
    b[0].led_value = "(A:AUTOPILOT MASTER,bool)";
    b[0].press_action = "(A:AUTOPILOT DISENGAGED, Bool) ! if{ (>K:AP_MASTER) }";
    // LOC/YD
    b[2].led_value = "(A:AUTOPILOT YAW DAMPER,bool)";
    b[2].press_action = "(>K:YAW_DAMPER_TOGGLE)";
    // APPR
    b[3].led_value = "(A:AUTOPILOT APPROACH HOLD, Bool) (A:AUTOPILOT GLIDESLOPE HOLD, Bool) and";
    b[3].press_action = "(A:AUTOPILOT APPROACH HOLD, Bool) (A:AUTOPILOT GLIDESLOPE HOLD, Bool) ! and if{ (>K:AP_APR_HOLD) } (>K:AP_APR_HOLD)";

    // DE-ICE airframe
    sw[0].set_action = "(A:STRUCTURAL DEICE SWITCH, Bool) ! if{ (>K:TOGGLE_STRUCTURAL_DEICE) }";
    sw[0].reset_action = "(A:STRUCTURAL DEICE SWITCH, Bool) if{ (>K:TOGGLE_STRUCTURAL_DEICE) }";
    // DE-ICE ice light
    sw[1].set_action = false;
    sw[1].reset_action = false;
    // DE-ICE prop
    sw[2].set_action = "(A:PROP DEICE SWITCH:1, Bool) ! if{ 1 (>K:1:TOGGLE_PROPELLER_DEICE) }";
    sw[2].reset_action = "(A:PROP DEICE SWITCH:1, Bool) if{ 1 (>K:1:TOGGLE_PROPELLER_DEICE) }";
    // DE-ICE windshield
    sw[3].set_action = "(A:WINDSHIELD DEICE SWITCH, Bool) ! if{ (>K:WINDSHIELD_DEICE_TOGGLE) }";
    sw[3].reset_action = "(A:WINDSHIELD DEICE SWITCH, Bool) if{ (>K:WINDSHIELD_DEICE_TOGGLE) }";
    // DE-ICE pitot L
    sw[4].set_action = "1 (>K:0:PITOT_HEAT_SET)";
    sw[4].reset_action = "0 (>K:0:PITOT_HEAT_SET)";
    // DE-ICE pitot R
    sw[5].set_action = false;
    sw[5].reset_action = false;
    // DE-ICE inert sep
    sw[6].set_action = false;
    sw[6].reset_action = false;
    // BLEED AUTO
    sw[7].set_action = false;
    sw[7].reset_action = false;
    // BLEED OFF
    sw[8].set_action = false;
    sw[8].reset_action = false;
    // ENGINE starter ON
    sw[9].set_action = false;
    sw[9].reset_action = false;
    // ENGINE starter ABORT
    sw[10].set_action = false;
    sw[10].reset_action = false;
    // ENGINE ignition AUTO
    sw[11].set_action = false;
    sw[11].reset_action = false;
    // ENGINE ignition OFF
    sw[12].set_action = false;
    sw[12].reset_action = false;
    // FUEL aux BP AUTO
    sw[13].set_action = false;
    sw[13].reset_action = false;
    // FUEL aux BP OFF
    sw[14].set_action = false;
    sw[14].reset_action = false;
    // FUEL fuel sel AUTO
    sw[15].set_action = false;
    sw[15].reset_action = false;
    // AP/TRIM ON
    sw[16].set_action = false;
    sw[16].reset_action = false;
    // AP/TRIM OFF
    sw[17].set_action = false;
    sw[17].reset_action = false;
    //
    sw[18].set_action = false;
    sw[18].reset_action = false;
    //
    sw[19].set_action = false;
    sw[19].reset_action = false;

}

HANDLE sim = 0;
enum PanelStatus {
    NoPanels, PanelsReady, PanelsUpdate, PanelsFetch,
};
static PanelStatus panel_status = NoPanels;

static const int WM_USER_SIMCONNECT = 0x0402;
static const int WM_USER_PANEL_CHANGE = 0x0403;
static const int WM_USER_PLANE_CHANGE = 0x0404;
static const int WM_USER_SIM_CONNECTED = 0x0405;
static const int WM_USER_SIM_DISCONNECTED = 0x0406;
static const int WM_USER_NOTIFY = 0x0407;

static Device* panels = 0;

void HID_find_panels(HWND win)
{
    GUID hidgid;
    HidD_GetHidGuid(&hidgid);

    EnterCriticalSection(&cs_Devices);
    for (Device* dev = panels; dev; dev = dev->next)
        dev->active = false;
    LeaveCriticalSection(&cs_Devices);

    HDEVINFO di = SetupDiGetClassDevsW(&hidgid, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    SP_DEVICE_INTERFACE_DATA did;
    struct didetails : public SP_DEVICE_INTERFACE_DETAIL_DATA_A {
        char path[256];
    } didd;
    did.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    for (DWORD mi = 0; SetupDiEnumDeviceInterfaces(di, 0, &hidgid, mi, &did); mi++)
    {

        didd.cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA_A);
        if (!SetupDiGetDeviceInterfaceDetailA(di, &did, &didd, sizeof(didetails), 0, 0))
            continue;

        HANDLE hid = CreateFileA(didd.DevicePath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
        if (hid == INVALID_HANDLE_VALUE)
            continue;

        HIDD_ATTRIBUTES attr;
        attr.Size = sizeof(attr);
        if (HidD_GetAttributes(hid, &attr) && attr.VendorID == 0x1209 && attr.ProductID == 0xC00C)
        {
            HANDLE whid = CreateFileA(didd.DevicePath, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
            Device* simpanel = 0;
            
            wchar_t    phys[256];
            if (HidD_GetSerialNumberString(hid, phys, 256*sizeof(wchar_t))) {
                EnterCriticalSection(&cs_Devices);
                for (Device* dev = panels; dev; dev = dev->next) {
                    if (dev->serial == phys) {
                        simpanel = dev;
                        break;
                    }
                }
                LeaveCriticalSection(&cs_Devices);
            }

            if (!simpanel) {
                if(!wcsncmp(phys, L"AP-2100-", 8))
                    simpanel = new SIMPANEL_AP_rev_C(hid, whid);
            }

            if (simpanel) {
                simpanel->serial = phys;
                simpanel->active = true;
                EnterCriticalSection(&cs_Devices);
                simpanel->next = panels;
                panels = simpanel;
                LeaveCriticalSection(&cs_Devices);
                PostMessage(win, WM_USER_PANEL_CHANGE, 0, 0);
            }
            else {
                CloseHandle(whid);
                CloseHandle(hid);
            }
        }

    }

    EnterCriticalSection(&cs_Devices);
    for (Device** dp = &panels; *dp; )
        if ((*dp)->active)
            dp = &((*dp)->next);
        else {
            Device* gone = *dp;
            *dp = gone->next;
            delete gone;
        }

    if (panels && panel_status == NoPanels)
        panel_status = PanelsReady;
    if (!panels)
        panel_status = NoPanels;
    LeaveCriticalSection(&cs_Devices);
}

bool HID_start_monitor(HWND window)
{
    struct _dbdwithroom : public DEV_BROADCAST_DEVICEINTERFACE_A {
        char room[63];
    } dbd;

    memset(&dbd, 0, sizeof(dbd));
    dbd.dbcc_size = sizeof(dbd);
    dbd.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
    HidD_GetHidGuid(&dbd.dbcc_classguid);
    HDEVNOTIFY res = RegisterDeviceNotificationA(window, &dbd, DEVICE_NOTIFY_WINDOW_HANDLE);
    if (res) {
        HID_find_panels(window);
        return true;
    }
    return false;
}


enum PlugStatus {
    Unconnected, SimConnecting, SimConnected, Starting, Ready, Paused, Exiting,
};
static PlugStatus plug_status = Unconnected;


enum Event : DWORD {
    GaugeInput, GaugeOutput, Sim6Hz, SimPaused, SimState, SimLoaded, SimPlane,
};

enum SCData : DWORD {
    GaugeInputData, GaugeOutputData, SimPlaneData,
};

enum SCRequest : DWORD {
    GaugeInputReq, GaugeInputCD, GaugeOutputReq, GaugeOutputCD,
};

enum SCGroup : DWORD {
    GaugeConnectGroup,
};

template<typename T> void sim_recv(T* ev, DWORD data) {
    fprintf(stderr, "[SIMPANEL] unhandled RECV type %d\n", ev->dwID);
    fflush(stderr);
}

#define RECV(tn) case SIMCONNECT_RECV_ID_##tn: sim_recv(reinterpret_cast<SIMCONNECT_RECV_##tn*>(data), dlen); return
#define RECV_FUNC(tn) template<> void sim_recv(SIMCONNECT_RECV_##tn* ev, DWORD data)


RECV_FUNC(OPEN)
{
    plug_status = SimConnected;
    SimConnect_RequestDataOnSimObject(sim, SimPlane, SimPlaneData, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
}

RECV_FUNC(QUIT)
{
    plug_status = Unconnected;
}

RECV_FUNC(EVENT)
{
    switch (ev->uEventID) {
    case GaugeOutput:
        break;
    case SimPaused:
        break;
    case SimState:
        SimConnect_RequestDataOnSimObject(sim, SimPlane, SimPlaneData, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
        break;
    case Sim6Hz:
        if (panel_status == PanelsReady)
            panel_status = PanelsUpdate;
        break;
    }
}

RECV_FUNC(EVENT_FILENAME)
{
    switch (ev->uEventID) {
    case SimLoaded:
        SimConnect_RequestDataOnSimObject(sim, SimPlane, SimPlaneData, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
        break;
    }
}

RECV_FUNC(CLIENT_DATA)
{
    GaugeOutputStruct& g = *reinterpret_cast<GaugeOutputStruct*>(&ev->dwData);
    if (GaugeRequest* req = GaugeRequest::head) {
        if (req->sequence == g.sequence) {
            switch (req->command) {
            
            case GISetExpr: {
                GaugeExpression& e = gexp[req->param];
                e.state = (g.result == GIOk) ? GaugeExpression::Stale : GaugeExpression::Invalid;
                delete req;
                break;
            }

            case GIEvaluate: {
                for (int i = 0; i < g.count; i++) {
                    gexp[g.values[i].index].value = g.values[i].value;
                    gexp[g.values[i].index].state = GaugeExpression::Valid;
                }
                if (g.result == GIComplete) {
                    delete req;
                }
                break;
            }

            default:
                delete req;
                break;
            }
        }
    }
}

RECV_FUNC(EXCEPTION)
{
}

RECV_FUNC(SIMOBJECT_DATA)
{
    switch (ev->dwRequestID) {
    case SimPlane:
        const char* plane = (const char*)(&ev->dwData);
        if (current_plane && !strcmp(plane, current_plane))
            break;
        char* cp = new char[strlen(plane)];
        if (current_plane)
            delete current_plane;
        strcpy(cp, plane);
        current_plane = cp;
        current_plane_changed = true;
        break;
    }
}

void CALLBACK simconnect_recv(SIMCONNECT_RECV* data, DWORD dlen, void*)
{
    switch (data->dwID) {
        RECV(EXCEPTION);
        RECV(OPEN);
        RECV(EVENT);
        RECV(EVENT_FILENAME);
        RECV(QUIT);
        RECV(CLIENT_DATA);
        RECV(SIMOBJECT_DATA);
    default:
        sim_recv(data, dlen);
        return;
    }
}

HANDLE simconnect_data_waiting;

DWORD WINAPI simconnect_thread(void* vp)
{
    HWND win = reinterpret_cast<HWND>(vp);

    while (plug_status != Exiting) {

        while (plug_status == Unconnected) {

            if (SimConnect_Open(&sim, "Simpanel Plug", win, WM_USER_SIMCONNECT, 0, 0) != S_OK) {
                Sleep(2000);
                continue;
            }

            if (
                SimConnect_MapClientDataNameToID(sim, "org.uberbox.gauge.input", GaugeInputCD) == S_OK
                && SimConnect_MapClientDataNameToID(sim, "org.uberbox.gauge.output", GaugeOutputCD) == S_OK
                && SimConnect_MapClientEventToSimEvent(sim, GaugeInput, "org.uberbox.gauge.input") == S_OK
                && SimConnect_MapClientEventToSimEvent(sim, GaugeOutput, "org.uberbox.gauge.output") == S_OK)
            {
                SimConnect_AddToClientDataDefinition(sim, GaugeInputData, 0, SIMCONNECT_CLIENTDATATYPE_INT32);
                SimConnect_AddToClientDataDefinition(sim, GaugeInputData, 4, SIMCONNECT_CLIENTDATATYPE_INT16);
                SimConnect_AddToClientDataDefinition(sim, GaugeInputData, 6, SIMCONNECT_CLIENTDATATYPE_INT16);
                SimConnect_AddToClientDataDefinition(sim, GaugeInputData, 8, 248);

                SimConnect_AddToClientDataDefinition(sim, GaugeOutputData, 0, SIMCONNECT_CLIENTDATATYPE_INT32);
                SimConnect_AddToClientDataDefinition(sim, GaugeOutputData, 4, SIMCONNECT_CLIENTDATATYPE_INT16);
                SimConnect_AddToClientDataDefinition(sim, GaugeOutputData, 6, SIMCONNECT_CLIENTDATATYPE_INT16);
                SimConnect_AddToClientDataDefinition(sim, GaugeOutputData, 8, sizeof(GaugeOutputStruct) - 8);

                SimConnect_SubscribeToSystemEvent(sim, Sim6Hz, "6Hz");
                SimConnect_SubscribeToSystemEvent(sim, SimLoaded, "AircraftLoaded");
                SimConnect_SubscribeToSystemEvent(sim, SimPaused, "Pause");
                SimConnect_SubscribeToSystemEvent(sim, SimState, "Sim");
                SimConnect_RequestClientData(sim, GaugeOutputCD, GaugeOutputReq, GaugeOutputData, SIMCONNECT_CLIENT_DATA_PERIOD_ON_SET, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG_DEFAULT);

                SimConnect_AddToDataDefinition(sim, SimPlaneData, "TITLE", 0, SIMCONNECT_DATATYPE_STRING32);
                plug_status = SimConnecting;

                for (int i = 0; i < 256; i++)
                    if (gexp[i].state != GaugeExpression::Free)
                        gexp[i].state = GaugeExpression::Updated;

                PostMessage(win, WM_USER_SIM_CONNECTED, 0, 0);
            }
        }

        // check if there are things to send
        if (GaugeRequest* req = GaugeRequest::head) {
            if (!req->sent) {
                int rv = SimConnect_SetClientData(sim, GaugeInputCD, GaugeInputData, 0, 0, sizeof(GaugeInputStruct), static_cast<GaugeInputStruct*>(req));
                req->sent = true;
            }
        }
        else {
            // If we have no outstanding requests, it means that we have all the answers we're going to have.
            
            EnterCriticalSection(&cs_Devices);
            if (panels && current_plane_changed) {
                for(Device* panel=panels; panel; panel=panel->next)
                    panel->load_plane(current_plane);
                PostMessage(win, WM_USER_PLANE_CHANGE, 0, 0);
                current_plane_changed = false;
            }
            LeaveCriticalSection(&cs_Devices);

            bool need_registration = false;
            for (int i = 0; i < 256; i++) {
                if (gexp[i].state == GaugeExpression::Updated) {
                    need_registration = true;
                    gexp[i].state = GaugeExpression::Sent;
                    GaugeRequest* req = new GaugeRequest(GISetExpr);
                    req->param = i;
                    strcpy(req->data, gexp[i].expression);
                    req->send();
                }
            }

            EnterCriticalSection(&cs_Devices);
            if (!need_registration)
                switch (panel_status) {

                case PanelsUpdate:
                {
                    EvaluateRequest r;
                    for (Device* panel = panels; panel; panel = panel->next)
                        for(int i=0; i<panel->num_settings; i++)
                            if (panel->settings[i].type == Device::Setting::GetExpression) {
                                if (!panel->settings[i].expression->fixed)
                                    r.add(panel->settings[i].expression->index);
                            }

                    r.request();
                    panel_status = PanelsFetch;
                    break;
                }

                case PanelsFetch:
                {
                    for (Device* panel = panels; panel; panel = panel->next)
                        panel->update();
                    panel_status = PanelsReady;
                    break;
                }

                }
            LeaveCriticalSection(&cs_Devices);

        }

        switch (WaitForSingleObject(simconnect_data_waiting, INFINITE)) {
        case WAIT_OBJECT_0:

            if (SimConnect_CallDispatch(sim, simconnect_recv, 0) != S_OK) {
                plug_status = Unconnected;
                SimConnect_Close(sim);
                sim = 0;
                PostMessage(win, WM_USER_SIM_DISCONNECTED, 0, 0);
            }

        }

    } // while !plug_shutdown
    return 0;
}


void startup(HWND win)
{
    for (int i = 0; i < 255; i++)
        gexp[i].next = i + 1;
    gexp[255].next = -1;
    gfree = 0;
    InitializeCriticalSectionAndSpinCount(&cs_Expressions, 256);
    InitializeCriticalSectionAndSpinCount(&cs_Devices, 256);

    simconnect_data_waiting = CreateEventA(0, false, false, 0);

    HID_start_monitor(win);

    CreateThread(0, 0, simconnect_thread, reinterpret_cast<void*>(win), 0, 0);
}

ICoreWebView2Controller* webviewController = nullptr;
ICoreWebView2* webview = nullptr;

void init_gui(HWND win, HINSTANCE hInstance)
{
    // Set up the web view environment for the settings window
    HRESULT result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    assert(result == S_OK);

    CreateCoreWebView2Environment(
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [win](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
                assert(result == S_OK);
                env->AddRef();

                // Get a controller for the view and add it to our main window
                env->CreateCoreWebView2Controller(win,
                    Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [win](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                            assert(result == S_OK);

                            webviewController = controller;
                            webviewController->AddRef(); // is this necessary?
                            result = controller->get_CoreWebView2(&webview);
                            assert(result == S_OK);
                            webview->AddRef(); // is this necessary?

                            // todo: customize settings to disable web-style context menus etc
                            ICoreWebView2Settings* Settings;
                            webview->get_Settings(&Settings);

                            RECT bounds;
                            GetClientRect(win, &bounds);
                            result = controller->put_Bounds(bounds);
                            assert(result == S_OK);

                            // Load the HTML GUI from a resource, as we can't navigate
                            // directly to the filesystem for security!
                            HMODULE hmod = GetModuleHandle(nullptr);
                            assert(hmod != nullptr);

                            HRSRC resource = FindResource(hmod, MAKEINTRESOURCE(IDR_HTML_GUI), RT_HTML);
                            assert(resource != nullptr);

                            HGLOBAL data = LoadResource(hmod, resource);
                            assert(data != nullptr);

                            // Note there's no need to unlock the resource later; it's read
                            // directly from the executable's read-only data sections and is
                            // safely unloaded from memory and reloaded by the kernel as needed.
                            void* locked = LockResource(data);
                            assert(data != nullptr);
                            const wchar_t* html = static_cast<const wchar_t*>(locked);

                            result = webview->NavigateToString(html);
                            assert(result == S_OK);

                            webviewController->put_IsVisible(TRUE);
                            
                            return S_OK;
                        }
                    ).Get()
                );
                return S_OK;
            }
        ).Get()
    );
}

/// WINDOWS DEFAULT STUFF BELOW


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE instance;                            // current instance
wchar_t main_title[MAX_LOADSTRING];            // The title bar text
wchar_t main_class[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                register_class(const wchar_t* name, WNDPROC);
BOOL                init_instance(HINSTANCE, int);
LRESULT CALLBACK    main_proc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    status_proc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    instance = hInstance;

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, main_title, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SIMPANELPLUG, main_class, MAX_LOADSTRING);
    register_class(main_class, main_proc);
    register_class(L"PlugStatus", status_proc);

    HWND mainwin = CreateWindowW(main_class, main_title, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_SYSMENU,
            0, 0, 640, 480, nullptr, nullptr, hInstance, nullptr);

    if (!mainwin)
    {
        return FALSE;
    }

    startup(mainwin);
    init_gui(mainwin, hInstance);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPANELPLUG));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (IsChild(mainwin, msg.hwnd))
        {
            if (TranslateAccelerator(mainwin, hAccelTable, &msg))
                continue;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    plug_status = Exiting;

    return (int)msg.wParam;
}



//
//  FUNCTION: RegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM register_class(const wchar_t* name, WNDPROC proc)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = proc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = instance;
    wcex.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_SIMPANELPLUG));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
    wcex.lpszClassName = name;
    wcex.lpszMenuName = nullptr;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

struct Noticon : public NOTIFYICONDATA {
    static constexpr GUID noticon_guid = { 0x2a36d23e, 0x5795, 0x472b, { 0x8f, 0xcd, 0x98, 0xa3, 0xa8, 0x28, 0x79, 0x5c } };

    Noticon(HWND win) {
        cbSize = sizeof(NOTIFYICONDATA);
        hWnd = win;
        uFlags = NIF_GUID;
        guidItem = noticon_guid;
    }

    operator NOTIFYICONDATA* (void) { return this; };
    operator const NOTIFYICONDATA* (void) const { return this; };

};

HWND popup;

void show_status(HWND main) {

    RECT winpos = {};

    winpos.right = 240;
    winpos.bottom = 180;
    AdjustWindowRectEx(&winpos, WS_POPUP | WS_BORDER, false, WS_EX_TOOLWINDOW);
    popup = CreateWindowEx(WS_EX_TOOLWINDOW, L"PlugStatus", 0, WS_POPUP | WS_BORDER, 0, 0, winpos.right - winpos.left, winpos.bottom - winpos.top, main, 0, instance, 0);
    if (!popup)
        return;

    NOTIFYICONIDENTIFIER ii = { sizeof(ii) };
    ii.guidItem = Noticon::noticon_guid;
    RECT ipos;
    if (SUCCEEDED(Shell_NotifyIconGetRect(&ii, &ipos))) {
        const POINT anchor = { (ipos.left + ipos.right) / 2, (ipos.top + ipos.bottom) / 2 };
        SIZE winsize = { winpos.right - winpos.left, winpos.bottom - winpos.top };
        CalculatePopupWindowPosition(&anchor, &winsize, TPM_VERTICAL | TPM_VCENTERALIGN | TPM_CENTERALIGN | TPM_WORKAREA, &ipos, &winpos);
    }
 
    SetWindowPos(popup, HWND_TOPMOST, winpos.left, winpos.top, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
    SetForegroundWindow(popup);
}

void hide_status(void)
{
    if (!popup)
        return;

    DestroyWindow(popup);
    popup = 0;
}

LRESULT CALLBACK status_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        {
            RECT bounds;
            GetClientRect(hWnd, &bounds);
            HINSTANCE hInstance = reinterpret_cast<HINSTANCE>(GetWindowLongPtr(hWnd, GWLP_HINSTANCE));
            HWND childLabel = CreateWindowW(L"static", SS_LEFT,
                WS_CHILD | WS_VISIBLE,
                bounds.left, bounds.top, bounds.right - bounds.left, bounds.bottom - bounds.top,
                hWnd, nullptr,
                hInstance, nullptr);
            SetWindowTextW(childLabel, L"TODO: place status info here");
            break;
        }

    case WM_DESTROY:
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK main_proc(HWND win, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DEVICECHANGE:
        HID_find_panels(win);
        break;

    case WM_USER_SIMCONNECT:
        SetEvent(simconnect_data_waiting);
        break;

    case WM_USER_PANEL_CHANGE:
    {
        Noticon ni(win);

        ni.uFlags |= NIF_INFO;
        StringCchCopyW(ni.szInfo, ARRAYSIZE(ni.szTip), L"Yeay!");
        StringCchCopyW(ni.szInfoTitle, ARRAYSIZE(ni.szInfoTitle), L"SimPanel connected");
        ni.dwInfoFlags = NIIF_INFO;
        Shell_NotifyIcon(NIM_MODIFY, ni);

        if (popup)
            PostMessage(popup, WM_USER_PANEL_CHANGE, 0, 0);

        break;
    }

    case WM_USER_PLANE_CHANGE:
        if (popup)
            PostMessage(popup, WM_USER_PLANE_CHANGE, 0, 0);
        break;

    case WM_USER_SIM_CONNECTED:
        if (popup)
            PostMessage(popup, WM_USER_SIM_CONNECTED, 0, 0);
        break;

    case WM_USER_SIM_DISCONNECTED:
        if (popup)
            PostMessage(popup, WM_USER_SIM_DISCONNECTED, 0, 0);
        break;

    case WM_USER_NOTIFY:
        switch (LOWORD(lParam)) {
        
        case NIN_SELECT:
        case NIN_KEYSELECT:
        {
            if (IsWindowVisible(win))
                ShowWindow(win, SW_HIDE);
            else
                ShowWindow(win, SW_SHOW);
            break;
        }

        case NIN_POPUPOPEN:
            show_status(win);
            break;

        case NIN_POPUPCLOSE:
            hide_status();
            break;

        case WM_CONTEXTMENU:
        {
            break;
        }

        default:
            Sleep(20);
            break;

        }
        break;

    case WM_CREATE:
    {
        Noticon ni(win);

        ni.uFlags |= NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_INFO;
        ni.uCallbackMessage = WM_USER_NOTIFY;
        LoadIconMetric(instance, MAKEINTRESOURCE(IDI_SMALL), LIM_SMALL, &ni.hIcon);
        LoadString(instance, IDS_APP_TITLE, ni.szTip, ARRAYSIZE(ni.szTip));
        ni.szInfo[0] = 0;
        ni.szInfoTitle[0] = 0;
        ni.dwInfoFlags = NIIF_INFO;
        Shell_NotifyIcon(NIM_ADD, ni);

        ni.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, ni);

        break;
    }

    case WM_SIZE:
    {
        if (webviewController) {
            RECT bounds;
            GetClientRect(win, &bounds);
            webviewController->put_Bounds(bounds);
        }
        break;
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(instance, MAKEINTRESOURCE(IDD_ABOUTBOX), win, About);
            break;
        case IDM_EXIT:
            DestroyWindow(win);
            break;
        default:
            return DefWindowProc(win, message, wParam, lParam);
        }
        break;
    }

    case WM_DESTROY:
    {
        Noticon nid(win);
        Shell_NotifyIcon(NIM_DELETE, &nid);
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(win, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
