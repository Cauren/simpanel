// SimpanelModule.cpp

#include <cstddef>
#include <cstring>
#include <initializer_list>
#include <MSFS/MSFS.h>
#include <MSFS/MSFS_WindowsTypes.h>
#include <MSFS/Legacy/gauges.h>
#include <SimConnect.h>
#include "SimpanelModule.h"


class Simvar {
public:

	enum Variant {
		Default, TBM9, B78X, B748, A20N,
		_max,
	};

	struct VariantVars {
		Simvar& var;
		const char* varname;
	};

	int				id;
	double			value;
	const char*		name;
	const char*		default_vname;
	const char*		vname;
	Simvar*			prev;

	static Simvar*	all;

	Simvar(Simvar* p, const char* n, const char* dvn) :
		id(-1),
		value(0),
		name(n),
		default_vname(dvn),
		vname(0),
		prev(p)
	{
	};

	struct _setup {
		Simvar& var;
		const char* name;
	};

	static void Setup(Variant);

	explicit operator bool(void) const { return int(value) != 0; };
};

static const char* const variant_names[Simvar::Variant::_max] = {
	"----", "TBM9", "B78X", "B748", "A20N",
};

static Simvar::Variant	airframe = Simvar::Variant::Default;

static Simvar Heading		(0,			"AP Heading",		"(A:AUTOPILOT HEADING LOCK DIR, degrees)");
static Simvar Airspeed		(&Heading,	"AP Airspeed",		"(A:AUTOPILOT AIRSPEED HOLD VAR, knots)");
static Simvar Mach			(&Airspeed,	"AP Mach",			"(A:AUTOPILOT AIRSPEED HOLD VAR, number)");
static Simvar VS			(&Mach,		"AP VS",			"(A:AUTOPILOT VERTICAL HOLD VAR, feet/minute)");
static Simvar Pitch			(&VS,		"AP Pitch",			"(A:AUTOPILOT PITCH HOLD REF, degrees)");
static Simvar Altitude		(&Pitch,	"AP Altitude",		"(A:AUTOPILOT ALTITUDE LOCK VAR, feet)");
static Simvar BankRate		(&Altitude,	"AP Max Bank",		"(A:AUTOPILOT MAX BANK, degrees)");
static Simvar ClimbMode		(&BankRate,	"AP Climb Hold",	0);
static Simvar HdgHold		(&ClimbMode,"AP Heading Hold",	"(A:AUTOPILOT HEADING LOCK, bool)");
static Simvar MachMode		(&HdgHold,	"AP Mach mode",		"XMLVAR_AirSpeedIsInMach");
static Simvar AT			(&MachMode,	"AP Autothrottle",	"(A:AUTOPILOT AIRSPEED HOLD, Bool) (A:AUTOPILOT MACH HOLD, Bool) or");
static Simvar SpdHold		(&AT,		"AP Airspeed Hold",	0);
static Simvar FLC			(&SpdHold,	"AP FL Change",		"AP_FLCH_ACTIVE");
static Simvar LNAV			(&FLC,		"AP LNAV",			"(A:AUTOPILOT NAV1 LOCK, bool)");
static Simvar VNAV			(&LNAV,		"AP VNAV",			"AP_VNAV_ARMED");
static Simvar VSHold		(&VNAV,		"AP VS Hold",		"(A:AUTOPILOT VERTICAL HOLD, bool)");
static Simvar AltHold		(&VSHold,	"AP Altitude Hold",	"(A:AUTOPILOT ALTITUDE LOCK, bool)");
static Simvar Approach		(&AltHold,	"AP Approach Hold",	"(A:AUTOPILOT APPROACH HOLD, Bool) (A:AUTOPILOT GLIDESLOPE HOLD, Bool) and");
static Simvar YawDamper		(&Approach,	"AP Yaw Damper",	"(A:AUTOPILOT YAW DAMPER, bool)");
static Simvar Expedite		(&YawDamper,"AP Expedite",		0);
static Simvar Autopilot		(&Expedite,	"AP Master",		"(A:AUTOPILOT MASTER, bool)");
static Simvar FDirector		(&Autopilot,"AF FD",			"(A:AUTOPILOT FLIGHT DIRECTOR ACTIVE, bool)");

Simvar* Simvar::all = &FDirector;

Simvar::VariantVars B78X_variant[] = {
	{ SpdHold,		"AP_HEADING_HOLD_ACTIVE" },
	{ VSHold,		"AP_VS_ACTIVE" },
	{ AltHold,		"AP_ALT_HOLD_ACTIVE" },
	{ LNAV,			"AP_LNAV_ARMED" },
	{ AT,			"AP_SPD_ACTIVE" },
};

Simvar::VariantVars B748_variant[] = {
	{ SpdHold,		"AP_HEADING_HOLD_ACTIVE" },
	{ VSHold,		"AP_VS_ACTIVE" },
	{ AltHold,		"AP_ALT_HOLD_ACTIVE" },
	{ LNAV,			"AP_LNAV_ARMED" },
	{ AT,			"AP_SPD_ACTIVE" },
};

Simvar::VariantVars A20N_variant[] = {
	{ SpdHold,		"AP_HEADING_HOLD_ACTIVE" },
};

Simvar::VariantVars TBM9_variant[] = {
	{ SpdHold,		"AP_HEADING_HOLD_ACTIVE" },
};

void Simvar::Setup(Simvar::Variant variant)
{
	const Simvar::VariantVars* var = 0;
	int numvv = 0;
	switch (variant) {
	case Simvar::Variant::B78X:
		var = B78X_variant;
		numvv = sizeof(B78X_variant) / sizeof(Simvar::VariantVars);
		printf("[SIMPANEL] Setting up panel for B78X\n");
		break;
	case Simvar::Variant::B748:
		var = B748_variant;
		numvv = sizeof(B748_variant) / sizeof(Simvar::VariantVars);
		printf("[SIMPANEL] Setting up panel for B748\n");
		break;
	case Simvar::Variant::A20N:
		var = A20N_variant;
		numvv = sizeof(A20N_variant) / sizeof(Simvar::VariantVars);
		printf("[SIMPANEL] Setting up panel for A20N\n");
		break;
	case Simvar::Variant::TBM9:
		var = TBM9_variant;
		numvv = sizeof(TBM9_variant) / sizeof(Simvar::VariantVars);
		printf("[SIMPANEL] Setting up panel for TBM9\n");
		break;
	case Simvar::Variant::Default:
		var = 0;
		printf("[SIMPANEL] Unknown airframe, setting up default panel\n");
		break;
	}
	fflush(stdout);
	for (Simvar* sv = all; sv; sv = sv->prev)
		sv->vname = sv->default_vname;
	if(var)
		while (numvv--) {
			var->var.vname = var->varname;
			var++;
		}
	for (Simvar* sv = all; sv; sv = sv->prev) {
		if (sv->vname) {
			if (sv->vname[0] == '(')
				sv->id = -2;
			else
				sv->id = check_named_variable(sv->vname);
			sv->value = -666.666;
		}
		else
			sv->id = -1;
	}
}

bool vars_setup = false;


enum Event: DWORD {
	SimStart, SimStop, AircraftLoaded, Frame,
	SimpanelDisplay, SimpanelInput,
};

enum SCData : DWORD {
	ATCInfoData, SPDIsplayData, SPInputData,
};

enum SCRequest : DWORD {
	ATCInfoReq, SPDisplayReq, SPInputReq, SPInputCD,
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

static int frames = 0;

HANDLE sim = 0;

template<typename T> void sim_recv(T* ev, DWORD data, void* ctx) {
	fprintf(stderr, "[SIMPANEL] unhandled RECV type %d\n", ev->dwID);
	fflush(stderr);
}

#define RECV(tn) case SIMCONNECT_RECV_ID_##tn: sim_recv(static_cast<SIMCONNECT_RECV_##tn*>(recv), data, ctx); return
#define RECV_FUNC(tn) template<> void sim_recv(SIMCONNECT_RECV_##tn* ev, DWORD data, void* ctx)

RECV_FUNC(EXCEPTION)
{
	fprintf(stderr, "[SIMPANEL] SimConnect exception %d\n", ev->dwException);
	fflush(stderr);
}

int id = 0;
double val = -666.666;

RECV_FUNC(OPEN)
{
	printf("[SIMPANEL] Open (%s)\n", ev->szApplicationName);
	Simvar::Setup(airframe);
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
		char inp[32];
		std::strncpy(inp, (char*)(&ev->dwData), 31);
		inp[31] = 0;
		int hdg = int(Heading.value+int8_t(unhex(inp)))%360;
		int rv = 0;
		send_key_event(KEY_HEADING_BUG_SET, hdg);
		printf("[SIMPANEL] tried to set heading to %d (%d)\n", hdg, rv);
		fflush(stdout);
		break;
	}
	}
}

RECV_FUNC(SYSTEM_STATE)
{
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
	default:
		fprintf(stderr, "[SIMPANEL] unhandled event %d (filename)\n", ev->uEventID);
		fflush(stderr);
		break;
	}
}

RECV_FUNC(EVENT)
{
	switch (ev->uEventID)
	{
	case Event::SimStart:
		printf("[SIMPANEL] Sim started\n");
		Simvar::Setup(Simvar::Default);
		fflush(stdout);
		break;
	case Event::SimStop:
		printf("[SIMPANEL] Sim stopped\n");
		fflush(stdout);
		break;
	case Event::SimpanelInput:
		break;
	default:
		fprintf(stderr, "[SIMPANEL] unhandled event %d\n", ev->uEventID);
		fflush(stderr);
		break;
	}
}

static char simpanel_dpy[17] = "---5IMPANEL-----";
static uint16_t simpanel_leds = 0xFFFF;

RECV_FUNC(EVENT_FRAME)
{
	bool changed = false;
	for (Simvar* sv = Simvar::all; sv; sv = sv->prev) {
		double nval;
		if (sv->id >= 0)
			nval = get_named_variable_value(sv->id);
		else if (sv->id == -2) {
			if (!execute_calculator_code(sv->vname, &nval, 0, 0))
				sv->id = -1;
		}
		if (sv->id != -1 && nval != sv->value) {
			sv->value = nval;
			changed = true;
//			printf("[SIMPANEL] %s = %g\n", sv->name, sv->value);
		}
	}
	if (changed) {
		char dpy[17];;
		uint16_t leds = 0;

		dpy[16] = 0;
		sprintf(dpy, "%03g", Heading.value);
		if (SpdHold) {
			if (MachMode)
				sprintf(dpy + 3, "M%02d", int(100 * Mach.value) % 100);
			else
				sprintf(dpy + 3, "%3d", int(Airspeed.value));
		}
		else
			dpy[3] = dpy[4] = dpy[5] = ' ';
		if (VSHold)
			sprintf(dpy + 6, "%+5d", int(VS.value));
		else
			dpy[6] = dpy[7] = dpy[8] = dpy[9] = dpy[10] = ' ';
		sprintf(dpy + 11, "%5d", int(Altitude.value));

		if (strcmp(dpy, simpanel_dpy)) {
			strcpy(simpanel_dpy, dpy);
			printf("[SIMPANEL] [%-16.16s]\n", simpanel_dpy);
		}

		if (HdgHold)
			leds |= 0x001;
		if (AT)
			leds |= 0x002;
		if (FLC)
			leds |= 0x004;
		if (VNAV)
			leds |= 0x008;
		if (LNAV)
			leds |= 0x010;
		if (VSHold)
			leds |= 0x020;
		if (AltHold)
			leds |= 0x040;
		if (Approach)
			leds |= 0x080;
		if (YawDamper)
			leds |= 0x200;
		if (Autopilot)
			leds |= 0x400;

		if (leds != simpanel_leds) {
			simpanel_leds = leds;
			printf("[SIMPANEL] leds %03x\n", int(simpanel_leds));
		}

		SPDisplayStruct sds;

		sprintf(sds.data, "%4s%16.16s%03x", variant_names[airframe], simpanel_dpy, int(simpanel_leds));
		SimConnect_SetClientData(sim, SPDisplayReq, SPDIsplayData, 0, 0, sizeof(SPDisplayStruct), &sds);
		SimConnect_TransmitClientEvent(sim, SIMCONNECT_OBJECT_ID_USER, SimpanelDisplay, 0, SimpanelGroup, 0);
		
		fflush(stdout);
	}
}

RECV_FUNC(SIMOBJECT_DATA)
{
	switch (ev->dwRequestID) {
		case ATCInfoReq: {
			Simvar::Variant af = Simvar::Variant::Default;
			ATCInfo = *reinterpret_cast<ATCInfoStruct*>(&ev->dwData);
			if (strstr(ATCInfo.model, "AC_MODEL_B78X")) {
				af = Simvar::Variant::B78X;
			}
			else if (strstr(ATCInfo.model, "AC_MODEL_TBM9")) {
				af = Simvar::Variant::TBM9;
			}
			else if (strstr(ATCInfo.model, "AC_MODEL_B748")) {
				af = Simvar::Variant::B748;
			}
			else if (strstr(ATCInfo.model, "AC_MODEL_A20N")) {
				af = Simvar::Variant::A20N;
			}
			if (af != airframe) {
				airframe = af;
				Simvar::Setup(airframe);
			}
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
//	FLOAT64 att_pitch = 0;
//	FLOAT64 att_bank = 0;
//	execute_calculator_code("(A:ATTITUDE INDICATOR PITCH DEGREES:2, degrees)", &att_pitch, 0, 0);
//	execute_calculator_code("(A:ATTITUDE INDICATOR BANK DEGREES:2, degrees)", &att_bank,0, 0);
	if (SimConnect_Open(&sim, "Simpanel Module", 0, 0, 0, 0) != S_OK) {
		fprintf(stderr, "[SIMPANEL] Unable to open SimConnect.\n");
		return;
	}

	SimConnect_AddToDataDefinition(sim, ATCInfoData, "ATC TYPE", 0, SIMCONNECT_DATATYPE_STRING64);
	SimConnect_AddToDataDefinition(sim, ATCInfoData, "ATC MODEL", 0, SIMCONNECT_DATATYPE_STRING64);
	SimConnect_RequestDataOnSimObject(sim, ATCInfoReq, ATCInfoData, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SIM_FRAME, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED);

	SimConnect_MapClientDataNameToID(sim, "simpanel.display", SPDisplayReq);
	SimConnect_CreateClientData(sim, SPDisplayReq, sizeof(SPDisplayStruct), 0);
	SimConnect_AddToClientDataDefinition(sim, SPDIsplayData, 0, 32);

	SimConnect_MapClientDataNameToID(sim, "simpanel.input", SPInputCD);
	SimConnect_CreateClientData(sim, SPInputCD, sizeof(SPDisplayStruct), 0);
	SimConnect_AddToClientDataDefinition(sim, SPInputData, 0, 32);

	SimConnect_MapClientEventToSimEvent(sim, SimpanelDisplay, "simpanel.display");
	SimConnect_AddClientEventToNotificationGroup(sim, SimpanelGroup, SimpanelDisplay);
	SimConnect_MapClientEventToSimEvent(sim, SimpanelInput, "simpanel.input");
	SimConnect_AddClientEventToNotificationGroup(sim, SimpanelGroup, SimpanelInput);
	SimConnect_SetNotificationGroupPriority(sim, SimpanelGroup, SIMCONNECT_GROUP_PRIORITY_HIGHEST);

	SimConnect_SubscribeToSystemEvent(sim, Event::SimStart, "SimStart");
	SimConnect_SubscribeToSystemEvent(sim, Event::SimStop, "SimStop");
	SimConnect_SubscribeToSystemEvent(sim, Event::AircraftLoaded, "AircraftLoaded");
	SimConnect_SubscribeToSystemEvent(sim, Event::Frame, "Frame");
	SimConnect_CallDispatch(sim, sim_recv, NULL);

	SimConnect_RequestClientData(sim, SPInputCD, SPInputReq, SPInputData, SIMCONNECT_CLIENT_DATA_PERIOD_ON_SET, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG_DEFAULT);

	printf("[SIMPANEL] Simpanel Module started!\n");
}

extern "C" MSFS_CALLBACK void module_deinit(void)
{
	printf("[SIMPANEL] Simpanel Module going away. :-(\n");
	if (!sim)
		return;
	SimConnect_Close(sim);
}
