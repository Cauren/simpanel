// SimpanelModule.cpp

#include <cstddef>
#include <cstring>
#include <stdlib.h>
#include <ctype.h>
#include <initializer_list>
#include <MSFS/MSFS.h>
#include <MSFS/MSFS_WindowsTypes.h>
#include <MSFS/Legacy/gauges.h>
#include <SimConnect.h>
#include "SimpanelModule.h"
#include <malloc.h>


class Expression {
public:
	int				id;
	double			value;
	bool			synthetic;
	char*			off;
	char			key[32];
	char			expr[128];

public:
	Expression(const char* k) : id(-1), value(0), synthetic(true), off(0) { strncpy(key, k, 31); key[31] = 0; expr[0] = 0; };

	void fire(void);
	operator int(void) { return int(value); };
	operator double(void) { return value; };
	void clear(void) { expr[0] = 0; id = -1; };
	const char* exp(void) { return expr; };
	Expression& operator = (int n) { value = n; synthetic = true;  return *this; };
	Expression& operator = (double n) { value = n; synthetic = true;  return *this; };
	explicit operator bool(void) { return id != -1 && int(value)!=0; };

	void setexp(const char* x) {
		strncpy(expr, x, 127);
		expr[127] = 0;
		id = -1;
		value = 0;
		synthetic = true;
	};
};

enum Vid {
	Avionics_ON,
	Autopilot_ON,
	AP_Heading,
	AP_Heading_Show,
	AP_Max_Bank,
	AP_Mach_Mode,
	AP_Airspeed,
	AP_Airspeed_Show,
	AP_Mach,
	AP_Mach_Show,
	AP_Pitch_Mode,
	AP_VS,
	AP_VS_Show,
	AP_Pitch_Show,
	AP_Pitch,
	AP_Altitude,
	AP_Altitude_Show,
	AP_Dial_Push_0,
	AP_Dial_Push_3=AP_Dial_Push_0+3,
	AP_Led_0,
	AP_Led_10=AP_Led_0+10,
	AP_Toggle_0,
	AP_Toggle_10=AP_Toggle_0+10,
	Switch_0,
	Switch_21=Switch_0+21,
};

static Expression  V[] = {
	"Avionics_ON",
	"Autopilot_ON",
	"AP_Heading",
	"AP_Heading_Show",
	"AP_Max_Bank",
	"AP_Mach_Mode",
	"AP_Airspeed",
	"AP_Airspeed_Show",
	"AP_Mach",
	"AP_Mach_Show",
	"AP_Pitch_Mode",
	"AP_VS",
	"AP_VS_Show",
	"AP_Pitch_Show",
	"AP_Pitch",
	"AP_Altitude",
	"AP_Altitude_Show",
	"Dial0_push", "Dial1_push", "Dial2_push", "Dial3_push",
	"led0", "led1", "led2", "led3", "led4", "led5", "led6", "led7", "led8", "led9", "led10",
	"toggle0", "toggle1", "toggle2", "toggle3", "toggle4", "toggle5", "toggle6", "toggle7", "toggle8", "toggle9", "toggle10",
	"switch0", "switch1", "switch2", "switch3", "switch4", "switch5", "switch6", "switch7",
	"switch8up", "switch8down", "switch9up", "switch9down", "switch10up", "switch10down", "switch11up", "switch11down",
	"switch12up", "switch12down", "switch13up", "switch13down",
	"switch14", "switch15",
};

static int button_remap[24] = {
	3, 4, 5, 2, 1, 14, 16, 15, 17, 12, 6, 9, 10, 11, 8, 7, 0, 20, 21, 18, 19, 13, 
};

static char airframe[5] = "----";
static char ap_model[256] = "";

bool setup_expressions(const char* model)
{
	const int num = sizeof(V)/sizeof(Expression);

	if (!strcmp(model, ap_model))
		return true;
	strcpy(ap_model, model);

	for (int i = 0; i < num; i++)
		V[i].clear();

	FILE* ini = fopen(".\\modules\\simpanel.ini", "r");
	if (!ini) {
		perror("[SIMPANEL] Unable to read ini file\n");
		fflush(stderr);
		return false;
	}

	bool generic = false;
	bool found = false;
	char  buf[256];

	while (fgets(buf, 256, ini))
	{
		char* s = buf;
		while (*s && isspace(*s))
			s++;
		char* e = s + strlen(s);
		while (e > s && isspace(e[-1]))
			--e;
		*e = 0;
		if (!*s)
			continue;
		if (s[0] == '[' && e[-1] == ']') {
			if (found)
				break;
			if (!strcasecmp(s, "[default]")) {
				if (found || generic) {
					fprintf(stderr, "[SIMPANEL] Default section not where expected in simpanel.ini\n");
					fflush(stderr);
					return false;
				}
				generic = true;
			}
			else {
				generic = false;
				s++;
				--e;
				if (s >= e)
					continue;
				*e = 0;
				if (strstr(model, s)) {
					found = true;
					e -= 4;
					if (e < s)
						e = s;
					strcpy(airframe, e);
					printf("[SIMPANEL] Configuring controls for airframe %s\n", airframe);
					fflush(stdout);
				}
			}
		}
		else if (found || generic) {
			if (*s == ';')
				continue;
			char* v = s;
			while (*v && *v != '=')
				v++;
			if (!*v)
				continue;
			e = v;
			while (e > s && isspace(e[-1]))
				--e;
			*e = 0;
			if (!*s)
				continue;
			++v;
			while (isspace(*v))
				v++;
			if (!*v)
				continue;
			int i = 0;
			while (i < num && strcasecmp(s, V[i].key))
				i++;
			if (i >= num) {
				fprintf(stderr, "[SIMPANEL] unknown key %s in ini\n", s);
				fflush(stderr);
				continue;
			}
			V[i].setexp(v);
		}
	}
	fclose(ini);

	if (!found) {
		printf("[SIMPANEL] I don't have a section for aircraft model '%s'\n", model);
		fflush(stdout);
	}

	for (size_t i = 0; i < num; i++)
	{
		if (V[i].expr[0] == '1') {
			V[i].id = -3;
			V[i].value = 1;
		} else if (V[i].expr[0] == '(')
			V[i].id = strchr(V[i].expr, '>')? -3: -2;
		else if (V[i].expr[0])
			V[i].id = check_named_variable(V[i].expr);
		else
			V[i].id = -1;
	}
	for (int i = AP_Toggle_0; i <= AP_Toggle_10; i++)
		V[i].id = -3;

	return true;
}

bool fetch_expressions(void)
{
	const int num = sizeof(V) / sizeof(Expression);

	bool changed = false;
	for (size_t i = 0; i < num; i++) {
		if (V[i].id == -3)
			continue;
		double nval = 0;
		if (V[i].id >= 0) {
			nval = get_named_variable_value(V[i].id);
		} else {
			if (V[i].id == -2)
			{
				if (!execute_calculator_code(V[i].expr, &nval, 0, 0)) {
					fprintf(stderr, "[SIMPANEL] Expression '%s' for %s does not work\n", V[i].expr, V[i].key);
					fflush(stderr);
					V[i].id = -1;
				}
			}
		}
		if ((V[i].id != -1) && (V[i].synthetic || nval != V[i].value)) {
//			printf("[SIMPANEL] %s = %g\n", V[i].key, V[i].value);
			V[i].value = nval;
			V[i].synthetic = false;
			changed = true;
		}
	}
//	fflush(stdout);
	return changed;
}

void Expression::fire(void)
{
	double nval = -666;
	int ival = -666;
	char* sval = 0;

	// printf("[SIMPANEL] Firing %s: %s\n", key, expr);
	if (id == -3)
		if (!execute_calculator_code(expr, &nval, &ival, 0)) {
			fprintf(stderr, "[SIMPANEL] Toggle code failed\n");
			fflush(stderr);
			id = -1;
		}
	// printf("[SIMPANEL] results %g %d %p\n", nval, ival, sval);
	fflush(stdout);
}

enum class PanelState {
	SimStopped, AskATC, Configured,
} panel_state;

struct InputState {
	int8_t		dial[4];
	uint8_t		dswitch;
	uint16_t	apswitch;
	uint32_t	toggles;
};

InputState	cur_in;
bool		sim_running = false;
bool		sim_paused = true;

enum Event: DWORD {
	SimStart, SimStop, AircraftLoaded, Frame, Pause, Sim,
	SimpanelDisplay, SimpanelInput,
};

enum SCData : DWORD {
	ATCInfoData, SPDIsplayData, SPInputData,
};

enum SCRequest : DWORD {
	ATCInfoReq, SPDisplayReq, SPDisplayCD, SPInputReq, SPInputCD,
};

enum SCGroup : DWORD {
	SimpanelGroup,
};

struct ATCInfoStruct {
	char	type[64];
	char	model[64];
} ATCInfo;

struct SPDisplayStruct {
	char		data[32];
};

HANDLE sim = 0;

template<typename T> void sim_recv(T* ev, DWORD data, void* ctx) {
	fprintf(stderr, "[SIMPANEL] unhandled RECV type %d\n", ev->dwID);
	fflush(stderr);
}

#define RECV(tn) case SIMCONNECT_RECV_ID_##tn: sim_recv(static_cast<SIMCONNECT_RECV_##tn*>(recv), data, ctx); return
#define RECV_FUNC(tn) template<> void sim_recv(SIMCONNECT_RECV_##tn* ev, DWORD data, void* ctx)

RECV_FUNC(EXCEPTION)
{
	fprintf(stderr, "[SIMPANEL] SimConnect exception %ld\n", ev->dwException);
	fflush(stderr);
}

RECV_FUNC(OPEN)
{
	printf("[SIMPANEL] Open (%s)\n", ev->szApplicationName);;
	panel_state = PanelState::SimStopped;
	cur_in.apswitch = 0;
	cur_in.dswitch = 0;
	cur_in.toggles = 0;
}

static inline uint8_t unhex(char c) {
	return ((c > '9') ? c + 9 : c) & 0x0F;
}

static inline uint8_t unhex(const char* s) {
	return (unhex(s[0]) << 4) | unhex(s[1]);
}

RECV_FUNC(CLIENT_DATA)
{
	switch (ev->dwRequestID) {
	case SPInputReq: {
		InputState in{};
		char inp[32];
		std::strncpy(inp, (char*)(&ev->dwData), 31);
		inp[31] = 0;

		//printf("[SIMPANEL] <%s>\n", inp);

		for (int i = 0; i < 4; i++)
			in.dial[i] = unhex(inp + 2 * i);
		in.apswitch = unhex(inp + 8) | int(unhex(inp + 10) << 8);
		in.toggles = unhex(inp + 12) | int(unhex(inp + 14))<<8 | int(unhex(inp + 16)<<16);
		in.dswitch = unhex(inp + 18);
		//printf("[SIMPANEL] [%x]\n", in.toggles);

		Expression& Heading = V[AP_Heading];
		Expression& MachMode = V[AP_Mach_Mode];
		Expression& Mach = V[AP_Mach];
		Expression& Airspeed = V[AP_Airspeed];
		Expression& PitchMode = V[AP_Pitch_Mode];
		Expression& VS = V[AP_VS];
		Expression& Pitch = V[AP_Pitch];
		Expression& Altitude = V[AP_Altitude];

		int delta = in.dial[0];
		if (delta) {
			if (in.dswitch & 1) {
				delta = (delta * 10);
				if (int(Heading) % 10) {
					if (delta < 0)
						delta += 10;
					delta -= (int(Heading) % 10);
				}
			}
			int nv = (int(Heading) + delta + 360) % 360;
			send_key_event(KEY_HEADING_BUG_SET, nv);
			Heading = nv;
		}
		delta = in.dial[1];
		if (delta) {
			if (MachMode) {
				int mach = (double(Mach)+.005) * 100 + delta;
				send_key_event(KEY_AP_MACH_VAR_SET, mach);
				Mach = mach;
			}
			else {
				int as = int(Airspeed) + delta;
				send_key_event(KEY_AP_SPD_VAR_SET, as);
				Airspeed = as;
			}
		}
		delta = in.dial[2];
		if (delta) {
			int vs = int(VS) + delta * 100;
			send_key_event(KEY_AP_VS_VAR_SET_ENGLISH, vs);
			VS = vs;
		}

		delta = in.dial[3];
		if (delta) {
			int scale = (in.dswitch & 8) ? 100 : 1000;
			int round = int(double(Altitude) / scale) * scale;
			if (delta < 0 && round<int(Altitude))
				delta++;
			round += delta * scale;
			send_key_event(KEY_AP_ALT_VAR_SET_ENGLISH, round);
			Altitude = round;
		}

		for(int i=0; i<4; i++)
			if ((in.dswitch & (1 << i)) && !(cur_in.dswitch & (1 << i))) {
				if (V[AP_Dial_Push_0 + i].expr[0])
					V[AP_Dial_Push_0 + i].fire();
			}
		cur_in.dswitch = in.dswitch;

		for(int i=0; i<11; i++)
			if ((in.apswitch & (1 << i)) && !(cur_in.apswitch & (1 << i))) {
				if (V[AP_Toggle_0+i].expr[0])
					V[AP_Toggle_0 + i].fire();
			}
		cur_in.apswitch = in.apswitch;

		for(int i=0; i<24; i++)
			if ((in.toggles & (1 << i)) && !(cur_in.toggles & (1 << i))) {
				int t = button_remap[i];
				printf("[SIMPANEL] toggle %d\n", t);
			}
		cur_in.toggles = in.toggles;
		fflush(stdout);
		break;
	}
	}
}

RECV_FUNC(SYSTEM_STATE)
{
	printf("[SIMPANEL] System state: %g '%s'\n", ev->fFloat, ev->szString);
	fflush(stdout);
}

RECV_FUNC(QUIT)
{
}

RECV_FUNC(EVENT_FILENAME)
{
	switch (ev->uEventID)
	{
	case Event::AircraftLoaded:
		printf("[SIMPANEL] Aircraft loaded: %s\n", ev->szFileName);
		fflush(stdout);
		break;
	case Event::SimpanelDisplay:
		break;
	default:
		fprintf(stderr, "[SIMPANEL] unhandled event %ld (filename)\n", ev->uEventID);
		fflush(stderr);
		break;
	}
}

void display_now(const char*);

RECV_FUNC(EVENT)
{
	switch (ev->uEventID)
	{
	case Event::SimStart:
		break;
	case Event::SimStop:
		break;
	case Event::SimpanelInput:
		break;
	case Event::Sim:
		sim_running = ev->dwData;
		break;
	case Event::Pause:
		sim_paused = ev->dwData;
		break;
	default:
		fprintf(stderr, "[SIMPANEL] unhandled event %ld\n", ev->uEventID);
		fflush(stderr);
		break;
	}
	if(sim_running && !sim_paused)
	{
		if (panel_state == PanelState::SimStopped)
		{
			printf("[SIMPANEL] Sim started\n");
			panel_state = PanelState::AskATC;
			SimConnect_RequestDataOnSimObject(sim, ATCInfoReq, ATCInfoData, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE, SIMCONNECT_DATA_REQUEST_FLAG_DEFAULT);
			fflush(stdout);
		}
	}
	else {
		if (panel_state != PanelState::SimStopped) {
			printf("[SIMPANEL] Sim stopped\n");
			panel_state = PanelState::SimStopped;
			fflush(stdout);
			display_now("n/a qqqqqqqqqqqqqqqq");
		}
	}
}

static char simpanel_dpy[17] = "---5IMPANEL-----";
static uint16_t simpanel_leds = 0xFFFF;

void update_display(bool xmit)
{
	if (double(V[Autopilot_ON]) < 0.5) {
		display_now(airframe);
		return;
	}

	char dpy[17];;
	uint16_t leds = 0;

	dpy[16] = 0;

	if (V[AP_Heading_Show])
		sprintf(dpy, "%03g", V[AP_Heading].value);

	if (V[AP_Mach_Mode] && V[AP_Mach_Show])
		sprintf(dpy + 3, "M%02d", int(100 * (V[AP_Mach].value + .005)) % 100);
	else if (V[AP_Airspeed_Show] && !V[AP_Mach_Mode])
		sprintf(dpy + 3, "%3d", int(V[AP_Airspeed].value));
	else
		dpy[3] = dpy[4] = dpy[5] = ' ';

	if (V[AP_Pitch_Mode] && V[AP_Pitch_Show])
		sprintf(dpy + 6, "%+3do%d", int(V[AP_Pitch].value), int(10 * (double(V[AP_Pitch]) - int(V[AP_Pitch]))));
	else if (V[AP_VS_Show] && !V[AP_Pitch_Mode])
		sprintf(dpy + 6, "%+5d", int(V[AP_VS].value));
	else
		dpy[6] = dpy[7] = dpy[8] = dpy[9] = dpy[10] = ' ';

	if (V[AP_Altitude_Show]) {
		sprintf(dpy + 11, "%5d", int(V[AP_Altitude].value));
	}
	else
		sprintf(dpy + 11, "     ");

	if (strcmp(dpy, simpanel_dpy)) {
		strcpy(simpanel_dpy, dpy);
		xmit = true;
	}

	for (int i = 0; i < 11; i++)
		if (V[AP_Led_0+i])
			leds |= 1 << i;

	if (leds != simpanel_leds) {
		simpanel_leds = leds;
		xmit = true;
	}

	SPDisplayStruct sds;

	if (xmit) {
		sprintf(sds.data, "%4s%16.16s%03x", airframe, simpanel_dpy, int(simpanel_leds));
		SimConnect_SetClientData(sim, SPDisplayCD, SPDIsplayData, 0, 0, sizeof(SPDisplayStruct), &sds);
		SimConnect_TransmitClientEvent(sim, SIMCONNECT_OBJECT_ID_USER, SimpanelDisplay, 0, SimpanelGroup, 0);
	}
}

void display_now(const char* msg) {
	SPDisplayStruct sds;

	sprintf(sds.data, "%-20.20s000", msg);
	SimConnect_SetClientData(sim, SPDisplayCD, SPDIsplayData, 0, 0, sizeof(SPDisplayStruct), &sds);
	SimConnect_TransmitClientEvent(sim, SIMCONNECT_OBJECT_ID_USER, SimpanelDisplay, 0, SimpanelGroup, 0);
}

RECV_FUNC(EVENT_FRAME)
{
	if (panel_state == PanelState::Configured)
		if (fetch_expressions())
			update_display(false);
}

RECV_FUNC(SIMOBJECT_DATA)
{
	switch (ev->dwRequestID) {
		case ATCInfoReq: {
			ATCInfo = *reinterpret_cast<ATCInfoStruct*>(&ev->dwData);
			if (setup_expressions(ATCInfo.model)) {
				if (panel_state != PanelState::Configured) {
					panel_state = PanelState::Configured;
					SimConnect_RequestDataOnSimObject(sim, ATCInfoReq, ATCInfoData, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);
				}
				update_display(true);
			}
			else
				panel_state = PanelState::SimStopped;
		}
		break;
	}
}

void CALLBACK sim_recv(SIMCONNECT_RECV* recv, DWORD data, void* ctx)
{
	switch (recv->dwID)
	{
		RECV(EVENT_FRAME);
		RECV(EVENT_FILENAME);
		RECV(EVENT);
		RECV(EXCEPTION);
		RECV(CLIENT_DATA);
		RECV(SYSTEM_STATE);
		RECV(SIMOBJECT_DATA);
		RECV(OPEN);
		RECV(QUIT);

	default:
		fprintf(stderr, "[SIMPANEL] unknown recv? (%ld)\n", recv->dwID);
		fflush(stderr);
		break;
	}
}

extern "C" MSFS_CALLBACK void module_init(void){

	if (SimConnect_Open(&sim, "Simpanel Module", 0, 0, 0, 0) != S_OK) {
		fprintf(stderr, "[SIMPANEL] Unable to open SimConnect.\n");
		return;
	}

	SimConnect_AddToDataDefinition(sim, ATCInfoData, "ATC TYPE", 0, SIMCONNECT_DATATYPE_STRING64);
	SimConnect_AddToDataDefinition(sim, ATCInfoData, "ATC MODEL", 0, SIMCONNECT_DATATYPE_STRING64);
	SimConnect_RequestDataOnSimObject(sim, ATCInfoReq, ATCInfoData, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

	if (SimConnect_MapClientDataNameToID(sim, "simpanel.display", SPDisplayCD) != S_OK)
		fprintf(stderr, "[SIMPANEL] MapClientDataNameToID(display) failed\n");
	SimConnect_CreateClientData(sim, SPDisplayCD, sizeof(SPDisplayStruct), SIMCONNECT_CREATE_CLIENT_DATA_FLAG_READ_ONLY);
	fprintf(stderr, "[SIMPANEL] CreateClientData(display) failed\n");
	SimConnect_AddToClientDataDefinition(sim, SPDIsplayData, 0, 32);

	SimConnect_MapClientDataNameToID(sim, "simpanel.input", SPInputCD);
	fprintf(stderr, "[SIMPANEL] MapClientDataNameToID(input) failed\n");
	SimConnect_AddToClientDataDefinition(sim, SPInputData, 0, 32);

	SimConnect_MapClientEventToSimEvent(sim, SimpanelDisplay, "simpanel.display");
//	SimConnect_AddClientEventToNotificationGroup(sim, SimpanelGroup, SimpanelDisplay);
	SimConnect_MapClientEventToSimEvent(sim, SimpanelInput, "simpanel.input");
	SimConnect_AddClientEventToNotificationGroup(sim, SimpanelGroup, SimpanelInput);
	SimConnect_SetNotificationGroupPriority(sim, SimpanelGroup, SIMCONNECT_GROUP_PRIORITY_HIGHEST);

	SimConnect_SubscribeToSystemEvent(sim, Event::SimStart, "SimStart");
	SimConnect_SubscribeToSystemEvent(sim, Event::SimStop, "SimStop");
	SimConnect_SubscribeToSystemEvent(sim, Event::AircraftLoaded, "AircraftLoaded");
	SimConnect_SubscribeToSystemEvent(sim, Event::Pause, "Pause");
	SimConnect_SubscribeToSystemEvent(sim, Event::Sim, "Sim");
	SimConnect_SubscribeToSystemEvent(sim, Event::Frame, "Frame");
	SimConnect_CallDispatch(sim, sim_recv, NULL);

	SimConnect_RequestClientData(sim, SPInputCD, SPInputReq, SPInputData, SIMCONNECT_CLIENT_DATA_PERIOD_ON_SET, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG_DEFAULT);

	panel_state = PanelState::AskATC;
	SimConnect_RequestDataOnSimObject(sim, ATCInfoReq, ATCInfoData, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE, SIMCONNECT_DATA_REQUEST_FLAG_DEFAULT);
	cur_in.apswitch = 0;
	cur_in.dswitch = 0;
	cur_in.toggles = 0;

	fflush(stderr);
	printf("[SIMPANEL] Simpanel Module started!\n");
}

extern "C" MSFS_CALLBACK void module_deinit(void)
{
	printf("[SIMPANEL] Simpanel Module going away. :-(\n");
	if (!sim)
		return;
	SimConnect_Close(sim);
}
