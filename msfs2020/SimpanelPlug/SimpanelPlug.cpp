// SimpanelPlug.cpp : Defines the entry point for the application.
//

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "hid.lib")
#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "simconnect.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "windowsapp")
#pragma comment(lib, "ole32")

// I fucking *know* how to use str[n]cpy safely, Microsoft!
#define _CRT_SECURE_NO_WARNINGS

#include <winrt/base.h>

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
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Data.Json.h>
#include <wrl\wrappers\corewrappers.h>
#include <wrl\client.h>
#include <wrl.h>
#include <WebView2.h>
using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Data::Json;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;


#include "framework.h"
#include "SimpanelPlug.h"
#include "Resource.h"

#include <SimConnect.h>
#include <cstring>
#include <string>
#include <initializer_list>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


CRITICAL_SECTION cs_Expressions;
CRITICAL_SECTION cs_Devices;


struct GaugeExpression {
    enum State {
        Free, Updated, Sent, Invalid, Valid, Stale,
    };

    static GaugeExpression gexp[256];

    State   state;
    bool readable;
    unsigned short refs;
    const char* expression;
    double  value;

    GaugeExpression(State s = Free) : state(s), readable(false), refs(0), expression(0), value(0.0) { };
    ~GaugeExpression() { delete[] expression; };

    void free(void) {
        if (--refs)
            return;
        delete[] expression;
        expression = 0;
        state = Free;
    }

    struct Ref {
        short i;

        bool valid(void) const { return i >= 0 && gexp[i].state == Valid; };
        double value(void) const { return valid() ? gexp[i].value : 0.0; };

        Ref(void) : i(-1) { };
        Ref(const Ref& r) : i(r.i) { if (i >= 0) gexp[i].refs++; };
        Ref(Ref&& r) : i(r.i) { r.i = -1; };
        ~Ref() { free(); };

        void free(void) {
            if (i >= 0) {
                gexp[i].free();
                i = -1;
            }
        }
        void set(const char* exp, bool readable) {
            if (i >= 0) {
                if (gexp[i].expression && !strcmp(exp, gexp[i].expression)) {
                    if (readable)
                        gexp[i].readable = true;
                    return;
                }
                gexp[i].free();
            }
            short free = -1;
            for (short e = 0; e < 256; e++) {
                if (gexp[e].state == Free) {
                    if (free < 0)
                        free = e;
                }
                else {
                    if (gexp[e].expression && !strcmp(exp, gexp[e].expression)) {
                        i = e;
                        gexp[e].refs++;
                        if (readable)
                            gexp[e].readable = true;
                        return;
                    }
                }
            }
            if (free < 0) {
                i = -1;
                return;
            }

            char* nexp = new char[strlen(exp) + 1];
            strcpy(nexp, exp);

            i = free;
            gexp[i].state = Updated;
            gexp[i].readable = readable;
            gexp[i].refs = 1;
            gexp[i].expression = nexp;
            gexp[i].value = 0.0;
        }

        bool update(double v) {
            if (i < 0)
                return false;
            switch (gexp[i].state) {
            case Stale:
                gexp[i].state = Valid;
                [[fallthrough]];
            case Valid:
                gexp[i].value = v;
                return true;
            default:
                return false;
            }
        }

        std::string expr(void) { return (i<0)? "": gexp[i].expression; }

    };

};

GaugeExpression GaugeExpression::gexp[256];

static const char* current_plane = 0;
static bool current_plane_changed = false;
static size_t current_model_loaded = 0;

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

    void update(const GaugeExpression::Ref& ge, double v = 0.0) {
        if (ge.i >= 0) {
            xnum[numx] = ge.i; xval[numx++] = v;
        }
    }
    void fetch(UINT16 i) {
        xnum[numx] = i; xval[numx++] = 0.0;
    }

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


struct Value {

    enum Kind {
        Boolean, Natural, Floating, Gauge,
    };
    Kind kind;
    GaugeExpression::Ref ge;
    union {
        double val;
        int nat;
    };

    Value(void) : kind(Boolean), nat(0) { };
    ~Value() { blank(); };

    void blank(void) {
        if (kind == Gauge)
            ge.free();
        kind = Boolean;
        nat = 0;
    }

    bool set(const char* exp, size_t count, const char* const* enums) {
        if (exp && exp[0])
            for (int e = 0; e < count; e++)
                if (!_stricmp(exp, enums[e])) {
                    blank();
                    kind = Natural;
                    nat = e;
                    return true;
                }
        return false;
    }

    void set(const char* exp, bool readable) {
        if (!exp || !exp[0]) {
            blank();
            return;
        }

        static constexpr const char* bool_true[] = { "True", "On", "Yes" };
        static constexpr const char* bool_false[] = { "False", "Off", "No" };

        if (set(exp, 3, bool_true)) {
            nat = 1;
            kind = Boolean;
            return;
        }
        if (set(exp, 3, bool_false)) {
            nat = 0;
            kind = Boolean;
            return;
        }

        std::from_chars_result fcr;
        const char* end = exp + strlen(exp);

        fcr = std::from_chars(exp, end, nat);
        if (fcr.ptr == end) {
            blank();
            kind = Natural;
            return;
        }
        fcr = std::from_chars(exp, end, val);
        if (fcr.ptr == end) {
            blank();
            kind = Floating;
            return;
        }
        kind = Gauge;
        ge.set(exp, readable);
    }

    operator bool(void) { return natural(); };
    operator UINT32(void) { return natural(); };
    operator int(void) { return natural(); };
    operator double(void) { return value(); };
    UINT32 natural(void) { return (kind == Natural || kind==Boolean) ? nat : value(); };
    double value(void) { return (kind == Natural || kind == Boolean) ? nat : ((kind == Floating) ? val : ge.value()); };

    void update(EvaluateRequest& ev, double val = 0.0) {
        if (kind != Gauge)
            return;
        if(ge.update(val))
            ev.update(ge, val);
    }

};

struct Control {
    static Control prototype_;

    template<typename T, typename C> static constexpr size_t offset(C T::* PM) { return static_cast<char*>((void*)&(prototype_.*static_cast<C Control::*>(PM))) - static_cast<char*>((void*)&prototype_); }
    Value* o_value(size_t o) { return static_cast<Value*>((void*)(static_cast<char*>((void*)this) + o)); };
};
Control Control::prototype_;

struct Setting {
    enum Type {
        Subcontrol, Readable, Writable, Action, Enumerated,
    };
    Type type;
    const char* label;
    size_t offset;
    size_t count;
    union {
        const Setting* settings;
        const char* const* enums;
    };

    template<typename C, typename T> constexpr Setting(const char* l, C T::* sc) : type(Subcontrol), label(l), offset(Control::offset(sc)), count(sizeof(C::settings) / sizeof(Setting)), settings(C::settings) { }
    template<typename C, typename T, size_t N> constexpr Setting(const char* l, C (T::* sc)[N], int i) : type(Subcontrol), label(l), offset(Control::offset(sc)+i*sizeof(C)), count(sizeof(C::settings)/sizeof(Setting)), settings(C::settings) { }
    template<typename T> constexpr Setting(const char* l, Value T::* sv, Type t = Readable) : type(t), label(l), offset(Control::offset(sv)), count(0), settings(0) { };
    template<typename T> constexpr Setting(const char* l, Value T::* sv, int i, Type t = Readable) : type(t), label(l), offset(Control::offset(sv)+i*sizeof(Value)), count(0), settings(0) { };
    template<typename T, size_t N> constexpr Setting(const char* l, Value T::* sv, const char* const (&e)[N]) : type(Enumerated), label(l), offset(Control::offset(sv)), count(N), enums(e) { };
};

struct Config {
    Setting::Type type;
    const char* label;
    union {
        Value* value;
        Config* config;
    };
    size_t count_enums;
    const char* const* enums;
    Config* next;

    struct KVPair {
        std::vector<std::string> keys;
        std::string value;

        KVPair(const char* line) {
            if (!line)
                return;
            const char* end;
            while (*line && *line!='=') {
                while (*line == '.')
                    *line++;
                while (isspace(*line))
                    line++;
                end = line + 1;
                while (*end && *end != '=' && *end != '.')
                    end++;
                const char* next = end;
                while (isspace(end[-1]))
                    --end;
                if(end > line)
                    keys.push_back(std::basic_string(line, end - line));
                line = next;
            }
            if (*line != '=')
                return;
            line++;
            while (isspace(*line))
                line++;
            if (!*line)
                return;
            end = line + strlen(line);
            while (isspace(end[-1]))
                --end;
            value = std::basic_string(line, end - line);
        }
    };

    template<typename C> Config(C* base) : Config(C::settings, sizeof(C::settings) / sizeof(Setting), base, 0) { };
    Config(const Setting* s, size_t count, Control* base, size_t offset) : type(s->type), label(s->label), count_enums(0), enums(0), next(0) {
        switch (type) {
        case Setting::Subcontrol:
            config = new Config(s->settings, s->count, base, offset + s->offset);
            break;
        case Setting::Enumerated:
            count_enums = s->count;
            enums = s->enums;
            [[fallthrough]];
        default:
            value = base->o_value(offset + s->offset);
            break;
        }
        if(count > 1)
            next = new Config(s+1, count - 1, base, offset);
    }
    bool load(const KVPair& kv, int key) {
        if (kv.keys[key] == label) {
            if (kv.keys.size() == key + 1 && type != Setting::Subcontrol && value) {
                if (type == Setting::Enumerated)
                    value->set(kv.value.c_str(), count_enums, enums);
                else
                    value->set(kv.value.c_str(), type==Setting::Readable);
                return true;
            }
            if(kv.keys.size() > key+1 && type == Setting::Subcontrol && config)
                return config->load(kv, key + 1);
            return false;
        }
        if (!next)
            return false;
        return next->load(kv, key);
    }
    void save(std::ostream& out, std::string prefix) {
        using namespace std::literals;
        if (type == Setting::Subcontrol && config)
            config->save(out, prefix + label + "."s);
        else if(value) {
            out << prefix << std::string(label) << " = "s;
            if (type == Setting::Enumerated) {
                int v = value->natural();
                out << std::string(enums[(v<0 || v>=count_enums)? 0: v]) << std::endl;
            }
            else switch (value->kind) {
            case Value::Boolean:
                out << (value->natural() ? "True"s : "False"s) << std::endl;
                break;
            case Value::Natural:
                out << value->natural() << std::endl;
                break;
            case Value::Floating:
                out << value->value() << std::endl;
                break;
            case Value::Gauge:
                out << value->ge.expr() << std::endl;
                break;
            default:
                out << "0" << std::endl;
                break;
            }
        }
        if (next)
            next->save(out, prefix);
    }
};

DWORD WINAPI device_thread_reader(void*);
struct Device;
static Device* panels = 0;

struct Device {

    std::string name;
    std::string label;
    std::basic_string<wchar_t> serial;
    Config* config;
    Device* next;
    HANDLE hid;
    HANDLE whid;
    HANDLE reader_thread;
    bool end_reader;
    bool active;

    Device(const char* n, const char* l, HANDLE h, HANDLE wh) : name(n), label(l), config(0), next(0), hid(h), whid(wh), active(true)
    {
        end_reader = false;
        reader_thread = CreateThread(0, 0, device_thread_reader, this, 0, 0);
    };
    ~Device() {
        end_reader = true;
        WaitForSingleObject(reader_thread, INFINITE);
        delete config;
    };

    virtual unsigned char in_report_id(void) { return 0; };
    virtual size_t in_report_len(void) { return 0; };
    virtual void recv_hid_report(void* buf, size_t len) = 0;
    virtual void update(void) = 0;
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

struct SPIndicator : public Control
{
    Value   value;

    static const Setting settings[];
};

const Setting SPIndicator::settings[]{
    Setting("value", &SPIndicator::value),
};

struct SPButton : public Control
{
    Value   led;
    Value   push;

    static const Setting settings[];
};

const Setting SPButton::settings[]{
    Setting("led", &SPButton::led),
    Setting("push action", &SPButton::push, Setting::Action),
};

struct SPToggle : public Control
{
    Value on;
    Value off;

    static const Setting settings[];
};

const Setting SPToggle::settings[]{
    Setting("on action", &SPToggle::on, Setting::Action),
    Setting("off action", &SPToggle::off, Setting::Action),
};

struct SP3Way : public Control
{
    Value top;
    Value middle;
    Value bottom;

    static const Setting settings[];
};

const Setting SP3Way::settings[]{
    Setting("top action", &SP3Way::top, Setting::Action),
    Setting("middle action", &SP3Way::middle, Setting::Action),
    Setting("bottom action", &SP3Way::bottom, Setting::Action),
};

struct SPDial : public Control
{
    enum ValueType {
        Blank, Error, Track, IAS, Mach, VS, Angle, Altitude,
    };
    static constexpr const char* vt_names[] = { "Blank", "Error", "Track", "IAS", "Mach", "VS", "Angle", "Altitude", };

    Value active;
    Value value;
    Value value_type;
    Value set_value;
    Value unpressed_scale;
    Value pressed_scale;
    Value push;

    static const Setting settings[];
};

const Setting SPDial::settings[]{
    Setting("active", &SPDial::active),
    Setting("value", &SPDial::value),
    Setting("type", &SPDial::value_type, SPDial::vt_names),
    Setting("set value", &SPDial::set_value, Setting::Writable),
    Setting("unpressed scale", &SPDial::unpressed_scale),
    Setting("pressed scale", &SPDial::pressed_scale),
    Setting("push action", &SPDial::push, Setting::Action),
};

struct SPModeDial : public Control
{
    Value mode_select;
    SPDial dial[2];

    static const Setting settings[];
};

const Setting SPModeDial::settings[]{
    Setting("mode select", &SPModeDial::mode_select),
    Setting("primary", &SPModeDial::dial, 0),
    Setting("alternate", &SPModeDial::dial, 1),
};

struct SP_AP_C : public Control {
    SPIndicator power;
    SPModeDial d[4];
    SPButton b[11];
    SPToggle t[10];
    SP3Way tw[5];

    static const Setting settings[];
};

const Setting SP_AP_C::settings[]{
    Setting("avionics power", &SP_AP_C::power),

    Setting("speed", &SP_AP_C::d, 0),
    Setting("heading", &SP_AP_C::d, 1),
    Setting("vs", &SP_AP_C::d, 2),
    Setting("altitude", &SP_AP_C::d, 3),

    Setting("autothrottle", &SP_AP_C::b, 1),
    Setting("speed hold", &SP_AP_C::b, 10),
    Setting("lnav", &SP_AP_C::b, 7),
    Setting("vnav", &SP_AP_C::b, 8),
    Setting("flch", &SP_AP_C::b, 9),
    Setting("heading hold", &SP_AP_C::b, 6),
    Setting("vs hold", &SP_AP_C::b, 5),
    Setting("alt hold", &SP_AP_C::b, 4),
    Setting("autopilot", &SP_AP_C::b, 0),
    Setting("yd", &SP_AP_C::b, 2),
    Setting("approach", &SP_AP_C::b, 3),

    Setting("deice airframe", &SP_AP_C::t, 0),
    Setting("ice light", &SP_AP_C::t, 1),
    Setting("deice prop", &SP_AP_C::t, 2),
    Setting("deice windshield", &SP_AP_C::t, 3),
    Setting("pitot left", &SP_AP_C::t, 4),
    Setting("pitot right", &SP_AP_C::t, 5),
    Setting("inertial separator", &SP_AP_C::t, 6),
    Setting("fuel select", &SP_AP_C::t, 7),
    Setting("spare 1", &SP_AP_C::t, 8),
    Setting("spare 2", &SP_AP_C::t, 9),

    Setting("bleed", &SP_AP_C::tw, 0),
    Setting("starter", &SP_AP_C::tw, 1),
    Setting("ignition", &SP_AP_C::tw, 2),
    Setting("fuel pump", &SP_AP_C::tw, 3),
    Setting("autopilot master", &SP_AP_C::tw, 4),
};

using namespace std::string_literals;

namespace Configuration {

    static std::vector<std::string> models;
    static std::map<std::string, size_t> map;

    static std::vector<std::string> loaded_config;
    static size_t current_model;

    static std::string name(size_t i) { return models[(i < models.size()) ? i : 0]; }
    static size_t model(const char* title) {
        auto found = map.find(std::string(title));
        if (found != map.end())
            return found->second;
        return 0;
    }

    static void switch_to_model(size_t mdl) {
        loaded_config.clear();
        current_model = mdl;
        std::ifstream cfile;
        cfile.open(models[mdl] + ".spconf");
        for (std::string line; std::getline(cfile, line); )
            loaded_config.push_back(line);
        cfile.close();
    }

    static void create_new_model(std::string name)
    {
        size_t mdl = models.size();
        models.push_back(name);
        current_model = mdl;
        map[name] = mdl;
        save_map();
        save();
    }

    static void load(const char* title) {
        size_t mdl = model(title);
        if (loaded_config.size() > 0 && current_model == mdl)
            return;
        switch_to_model(mdl);
    }

    static void configure(Device* dev) {
        for (auto line : loaded_config) {
            Config::KVPair kv(line.c_str());
            if (kv.keys[0] == dev->label)
                dev->config->load(kv, 1);
        }
    }

    static void save(void) {
        std::ofstream cfile(models[current_model] + ".spconf");
        for (Device* dev = panels; dev; dev = dev->next)
            dev->config->save(cfile, dev->label + "."s);
        cfile.close();
        // force reload of current config so that the in-memory save is synced
        switch_to_model(current_model);
    }

    static void load_map(void) {
        models.clear();
        models.push_back("generic"s);
        map.clear();
        std::ifstream mmfile("modelmap.ini");
        size_t model = 0;
        for (std::string line; std::getline(mmfile, line); ) {
            if (line.empty())
                continue;
            if (line.front() == '[' && line.back() == ']') {
                models.push_back(line.substr(1, line.size()-2));
                model++;
                continue;
            }
            if (!model)
                continue;
            map[line] = model;
        }
        mmfile.close();
    }

    static void save_map(void) {
        std::ofstream mmfile("modelmap.ini");
        for (size_t m = 1; m < models.size(); m++) {
            bool any = false;
            for(auto title: map)
                if (title.second == m) {
                    if (!any) {
                        any = true;
                        mmfile << "["s << models[m] << "]"s << std::endl;
                    }
                    mmfile << title.first << std::endl;
                }
        }
        mmfile.close();
    }
};


struct SIMPANEL_AP_rev_C : public Device, public SP_AP_C {

    struct OutputReport {
        unsigned char id;
        unsigned char digits[18];
        unsigned char leds[2];
    };
    struct InputReport {
        unsigned char dials[4];
        unsigned char buttons[2];
        unsigned char switches[3];
    };

    signed short    dial_delta[4];
    bool            dial_closed[4];
    bool            dial_pushed[4];
    bool            leds[11];
    bool            button_closed[11];
    bool            button_pushed[11];
    bool            switch_closed[20];
    bool            toggle_on[11];
    unsigned char   threeway_state[5];


    SIMPANEL_AP_rev_C(HANDLE hid, HANDLE whid) : Device("SimPanel A/P rev. C", "ap", hid, whid) {
        for (int i = 0; i < 4; i++) {
            dial_delta[i] = 0;
            dial_closed[i] = dial_pushed[i] = false;
        }
        for (int i = 0; i < 11; i++)
            button_closed[i] = button_pushed[i] = leds[i] = false;
        for (int i = 0; i < 20; i++)
            switch_closed[i] = false;
        for (int i = 0; i < 10; i++)
            toggle_on[i] = false;
        for (int i = 0; i < 5; i++)
            threeway_state[i] = 1;

        config = new Config((SP_AP_C*)this);

        if (current_plane) {
            Configuration::load(current_plane);
            Configuration::configure(this);
        } else
            blank();
    }

    ~SIMPANEL_AP_rev_C() {
        blank();
    }

    virtual unsigned char in_report_id(void) { return 1; };
    virtual size_t in_report_len(void) { return 10; };
    virtual void recv_hid_report(void* buf, size_t len);
    virtual void update(void);

    void blank(void);
};

void SIMPANEL_AP_rev_C::recv_hid_report(void* buf, size_t len)
{
    InputReport* report = reinterpret_cast<InputReport*>(buf);
    if (len != sizeof(InputReport))
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

    // bits map to switches in a set but arbitrary order
    constexpr static int sw_remap[] = {
        13, 12, 10, 11, 9, 8, 6,
        5, 4,
        15, 16, 17, 18,
        19, 3, 2,
        0, 1,
        7, 14,
    };

    for (int s = 0; s < 20; s++) {
        int n = sw_remap[s];
        switch_closed[s] = report->switches[n>> 3] & (1 << (n & 7));
    }
}

void SIMPANEL_AP_rev_C::blank(void)
{
    OutputReport out_report;

    out_report.id = 2;
    for (int i = 0; i < 17; i++)
        out_report.digits[i] = 0;
    out_report.digits[17] = 0x80;
    out_report.leds[0] = 0;
    out_report.leds[1] = 0;
    WriteFile(whid, &out_report, 21, 0, 0);
}

// workflow: on 6Hz:
//   (a) if plane changed, load settings
//   (b) update all new expressions
//   (c) make a list of expression to evaluate and send it
//   -- after all expressions evaluated --
//   (d) panel->update()

void SIMPANEL_AP_rev_C::update(void)
{
    if (!power.value) {
        blank();
        return;
    }

    OutputReport out_report;
    out_report.id = 2;
    EvaluateRequest ev;

    for (int i = 0; i < 11; i++) {
        leds[i] = b[i].led;
        if (button_pushed[i]) {
            b[i].push.update(ev);
            button_pushed[i] = false;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (toggle_on[i] != switch_closed[i < 9 ? i : 15]) {
            toggle_on[i] = switch_closed[i < 9 ? i : 15];
            (toggle_on[i] ? t[i].on : t[i].off).update(ev);
        }
    }

    static constexpr int twbase[] = { 7, 9, 11, 13, 16 };

    for (int i = 0; i < 5; i++) {
        unsigned char s = switch_closed[twbase[i]] ? 0 : (switch_closed[twbase[i] + 1] ? 2 : 1);
        if (threeway_state[i] != s) {
            threeway_state[i] = s;
            switch (s) {
            case 0: tw[i].top.update(ev); break;
            case 1: tw[i].middle.update(ev); break;
            case 2: tw[i].bottom.update(ev); break;
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
            SPDial& mode = d[i].mode_select ? d[i].dial[1] : d[i].dial[0];
            SPDial::ValueType vt = static_cast<SPDial::ValueType>(mode.value_type.natural());
            double val = mode.value;

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
                    mode.set_value.update(ev, val);
                }
                if (dial_pushed[i]) {
                    mode.push.update(ev);
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
                if (long(val) == 0) {
                    pad[0] = 0;
                    break;
                }
                // Fallthrough
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
            if (leds[3 + i])
                out_report.leds[1] |= 1 << (7 - i);
        WriteFile(whid, &out_report, 21, 0, 0);
    }
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
                GaugeExpression& e = GaugeExpression::gexp[req->param];
                e.state = (g.result == GIOk) ? GaugeExpression::Stale : GaugeExpression::Invalid;
                delete req;
                break;
            }

            case GIEvaluate: {
                for (int i = 0; i < g.count; i++) {
                    GaugeExpression& e = GaugeExpression::gexp[g.values[i].index];
                    e.value = g.values[i].value;
                    e.state = GaugeExpression::Valid;
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
                    if (GaugeExpression::gexp[i].state != GaugeExpression::Free)
                        GaugeExpression::gexp[i].state = GaugeExpression::Updated;

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
                Configuration::load(current_plane);
                for (Device* panel = panels; panel; panel = panel->next)
                    Configuration::configure(panel);
                PostMessage(win, WM_USER_PLANE_CHANGE, 0, 0);
                current_plane_changed = false;
            }
            LeaveCriticalSection(&cs_Devices);

            bool need_registration = false;
            for (int i = 0; i < 256; i++) {
                if (GaugeExpression::gexp[i].state == GaugeExpression::Updated) {
                    need_registration = true;
                    GaugeExpression::gexp[i].state = GaugeExpression::Sent;
                    GaugeRequest* req = new GaugeRequest(GISetExpr);
                    req->param = i;
                    strcpy(req->data, GaugeExpression::gexp[i].expression);
                    req->send();
                }
            }

            EnterCriticalSection(&cs_Devices);
            if (!need_registration)
                switch (panel_status) {

                case PanelsUpdate:
                {
                    EvaluateRequest r;

                    for (int i = 0; i < 256; i++) {
                        GaugeExpression& ge = GaugeExpression::gexp[i];
                        if (ge.readable) {
                            if (ge.state == GaugeExpression::Valid  || ge.state == GaugeExpression::Stale) {
                                ge.state = GaugeExpression::Stale;
                                r.fetch(i);
                            }
                        }
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
    InitializeCriticalSectionAndSpinCount(&cs_Expressions, 256);
    InitializeCriticalSectionAndSpinCount(&cs_Devices, 256);

    Configuration::load_map();
    simconnect_data_waiting = CreateEventA(0, false, false, 0);

    HID_start_monitor(win);

    CreateThread(0, 0, simconnect_thread, reinterpret_cast<void*>(win), 0, 0);
}

#if defined(BRION_STUFF)
// for some reason it tries to release and dies after free if i use com_ptr
ICoreWebView2Environment* webviewEnv = nullptr;
com_ptr<ICoreWebView2Controller> webviewController(nullptr);
com_ptr<ICoreWebView2> webview(nullptr);

std::wstring utf8_to_wstring(const char* data_utf8, size_t bytes_utf8) {
    int chars_utf16 = MultiByteToWideChar(
        CP_UTF8,
        MB_ERR_INVALID_CHARS,
        data_utf8,
        bytes_utf8,
        nullptr,
        0);
    assert(chars_utf16 > 0);

    std::wstring wstr_utf16(chars_utf16, 0);

    int converted = MultiByteToWideChar(
        CP_UTF8,
        MB_ERR_INVALID_CHARS,
        data_utf8,
        bytes_utf8,
        &wstr_utf16[0],
        chars_utf16);
    assert(converted == chars_utf16);

    return wstr_utf16;
}

JsonValue string_to_json(std::string& str_utf8) {
    auto str_utf16 = utf8_to_wstring(str_utf8.data(), str_utf8.length());
    return JsonValue::CreateStringValue(str_utf16);
}

std::wstring load_html_resource(int resource_id) {

    // Load the HTML GUI from a resource, as we can't navigate
    // directly to the filesystem for security!
    HMODULE hmod = GetModuleHandle(nullptr);
    assert(hmod != nullptr);

    HRSRC resource = FindResource(hmod, MAKEINTRESOURCE(resource_id), RT_HTML);
    assert(resource != nullptr);

    size_t bytes_utf8 = SizeofResource(hmod, resource);
    assert(bytes_utf8 > 0);

    HGLOBAL data = LoadResource(hmod, resource);
    assert(data != nullptr);

    // Note there's no need to unlock the resource later; it's read
    // directly from the executable's read-only data sections and is
    // safely unloaded from memory and reloaded by the kernel as needed.
    void* locked = LockResource(data);
    assert(data != nullptr);
    const char* html_utf8 = static_cast<const char*>(locked);

    return utf8_to_wstring(html_utf8, bytes_utf8);
}

void init_gui(HWND win, HINSTANCE hInstance)
{
    // Set up the web view environment for the settings window
    CreateCoreWebView2Environment(
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [win](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
                check_hresult(result);
                webviewEnv = env;
                webviewEnv->AddRef();

                // Get a controller for the view and add it to our main window
                env->CreateCoreWebView2Controller(win,
                    Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [win](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                            check_hresult(result);
                            webviewController.attach(controller);
                            webviewController->AddRef();

                            check_hresult(webviewController->get_CoreWebView2(webview.put()));
                            webview->AddRef();

                            // todo: customize settings to disable web-style context menus etc
                            com_ptr<ICoreWebView2Settings> settings(nullptr);
                            webview->get_Settings(settings.put());
                            // ... settings->...

                            RECT bounds;
                            GetClientRect(win, &bounds);
                            check_hresult(webviewController->put_Bounds(bounds));

                            std::wstring html = load_html_resource(IDR_HTML_GUI);
                            check_hresult(webview->NavigateToString(html.c_str()));

                            result = webview->add_WebMessageReceived(
                                Callback<ICoreWebView2WebMessageReceivedEventHandler>(
                                    [](ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
                                        wchar_t* json_str = nullptr;
                                        check_hresult(args->get_WebMessageAsJson(&json_str));

                                        hstring json_hstr(json_str);
                                        JsonObject data = JsonObject::Parse(json_hstr);

                                        hstring action = data.GetNamedString(L"action");
                                        if (action == L"init") {
                                            // JS is ready; send it the set of control data
                                            {
                                                auto action = JsonValue::CreateStringValue(L"setPlane");
                                                auto payload = JsonValue::CreateStringValue(L"<plane name>");

                                                JsonObject msg;
                                                msg.SetNamedValue(L"action", action);
                                                msg.SetNamedValue(L"payload", payload);

                                                hstring json = msg.ToString();
                                                check_hresult(webview->PostWebMessageAsJson(json.c_str()));
                                            }
                                            {
                                                JsonArray payload;
                                                //assert(panels);
                                                if (!panels) {
                                                    // currently this is null
                                                    return S_OK;
                                                }

                                                auto panel = &panels[0]; // @todo select the right one based on plane
                                                for (int i = 0; i < panel->num_settings; i++) {
                                                    JsonObject item;
                                                    auto setting = &panel->settings[i];
                                                    item.SetNamedValue(L"control", string_to_json(setting->control));
                                                    item.SetNamedValue(L"label", string_to_json(setting->label));
                                                    switch (setting->type) {
                                                    case Device::Setting::SettingType::Action:
                                                        item.SetNamedValue(L"type", JsonValue::CreateStringValue(L"action"));
                                                        //item.SetNamedValue(L"value", JsonValue)
                                                        // expression
                                                        break;
                                                    case Device::Setting::SettingType::GetExpression:
                                                        item.SetNamedValue(L"type", JsonValue::CreateStringValue(L"get expression"));
                                                        //item.SetNamedValue(L"value", JsonValue)
                                                        // expression
                                                        break;
                                                    case Device::Setting::SettingType::SetExpression:
                                                        item.SetNamedValue(L"type", JsonValue::CreateStringValue(L"set expression"));
                                                        //item.SetNamedValue(L"value", JsonValue)
                                                        // expression
                                                        break;
                                                    case Device::Setting::SettingType::Value:
                                                        item.SetNamedValue(L"type", JsonValue::CreateStringValue(L"value"));
                                                        //item.SetNamedValue(L"value", JsonValue)
                                                        // value -> double
                                                        break;
                                                    case Device::Setting::SettingType::Enumerator:
                                                        item.SetNamedValue(L"type", JsonValue::CreateStringValue(L"enumerator"));
                                                        //item.SetNamedValue(L"value", JsonValue)
                                                        // enumer -> what is it? pointer??
                                                        break;
                                                    default:
                                                        assert(0);
                                                    }
                                                    payload.Append(item);
                                                }

                                                JsonObject msg;
                                                msg.SetNamedValue(L"action", JsonValue::CreateStringValue(L"initControls"));
                                                msg.SetNamedValue(L"payload", payload);

                                                hstring json = msg.ToString();
                                                check_hresult(webview->PostWebMessageAsJson(json.c_str()));

                                            }
                                        }
                                        else if (action == L"update") {
                                            JsonObject payload = data.GetNamedObject(L"payload");
                                            hstring control = payload.GetNamedString(L"control");
                                            hstring label = payload.GetNamedString(L"label");
                                            hstring value = payload.GetNamedString(L"value");
                                            // todo: update state
                                        }
                                        else {
                                            assert(0);
                                        }

                                        return S_OK;
                                    }
                                ).Get(),
                                nullptr
                            );
                            assert(result == S_OK);

                            // todo: hide it again when minimized to optimize performance
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
#endif // defined(BRION_STUFF)

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

    // Initialize COM and the Windows Runtime.
    // Must use apartment threading for COM for WebView2?
    HRESULT result = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    assert(result == S_OK);

    RoInitializeWrapper initialize(RO_INIT_SINGLETHREADED);
    assert(!FAILED(initialize));

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
#if defined(BRION_STUFF)
    init_gui(mainwin, hInstance);
#endif

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
#if defined(BRION_STUFF)
        if (webviewController) {
            RECT bounds;
            GetClientRect(win, &bounds);
            webviewController->put_Bounds(bounds);
        }
#endif
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
