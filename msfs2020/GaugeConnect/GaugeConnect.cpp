// GaugeConnect.cpp

#include <MSFS/MSFS.h>
#include <MSFS/MSFS_WindowsTypes.h>
#include <MSFS/Legacy/gauges.h>
#include <SimConnect.h>
#include <cstring>
#include "GaugeConnect.h"

struct Expression {
	bool	valid;
	double	value;
	char*	expression;
	UINT32	expr_len;

	Expression(void) : valid(false), expression(0), expr_len(0) { };
	~Expression() { remove(); };

	void remove(void) { if (valid && expression) delete[] expression; valid = false; expression = 0; };
};

Expression* exprs = 0;
size_t num_exprs = 0;

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
		INT16 index;
		INT16 valid;
		FLOAT64 value;
	}		values[20];
};

enum Event : DWORD {
	GaugeInput, GaugeOutput,
};

enum SCData : DWORD {
	GaugeInputData, GaugeOutputData,
};

enum SCRequest : DWORD {
	GaugeInputReq, GaugeInputCD, GaugeOutputReq, GaugeOutputCD,
};

enum SCGroup : DWORD {
	GaugeConnectGroup,
};

HANDLE sim = 0;
ID gvar;

template<typename T> void sim_recv(T* ev, DWORD data, void* ctx) {
	fprintf(stderr, "[GaugeConnect] unhandled RECV type %ld\n", ev->dwID);
	fflush(stderr);
}

#define RECV(tn) case SIMCONNECT_RECV_ID_##tn: sim_recv(static_cast<SIMCONNECT_RECV_##tn*>(recv), data, ctx); return
#define RECV_FUNC(tn) template<> void sim_recv(SIMCONNECT_RECV_##tn* ev, DWORD data, void* ctx)

RECV_FUNC(EXCEPTION)
{
	fprintf(stderr, "[GaugeConnect] SimConnect exception %ld\n", ev->dwException);
	fflush(stderr);
}

RECV_FUNC(OPEN)
{
	printf("[GaugeConnect] Open (%s)\n", ev->szApplicationName);;
}

RECV_FUNC(CLIENT_DATA)
{
	switch (ev->dwRequestID) {
	case GaugeInputReq: {
		const GaugeInputStruct& inp = *reinterpret_cast<GaugeInputStruct*>(&ev->dwData);
		GaugeOutputStruct out;
		out.sequence = inp.sequence;
		out.result = GIError;
		switch (inp.command) {
		case GISetExpr: {
			if (inp.param >= num_exprs) {
				size_t nn = (inp.params+256) & ~255;
				Expression* ne = new Expression[nn];
				if(ne) {
					if (exprs) {
						std::memcpy(ne, exprs, num_exprs*sizeof(Expression));
						std::memset(exprs, 0, num_exprs*sizeof(Expression));
						delete[] exprs;
					}
					exprs = ne;
					num_exprs = nn;
				}
			}
			if (exprs && inp.param < num_exprs) {
				Expression& e = exprs[inp.param];
				e.remove();
				if ((e.expression = new char[strlen(inp.data)+1])) {
					strcpy(e.expression, inp.data);
					e.valid = true;
					out.result = GIOk;
					printf("[GaugeConnect] expression %d registered (%s)\n", int(inp.param), inp.data);
					fflush(stdout);
				}
				else
					e.valid = false;
			}
		}
					  break;
		case GIEvaluate: {
			out.result = GIMore;
			out.count = 0;
			for (int i = 0; i < inp.param; i++) {
				UINT16 index = reinterpret_cast<const UINT16*>(inp.data + inp.param * sizeof(FLOAT64))[i];
				FLOAT64 value = reinterpret_cast<const FLOAT64*>(inp.data)[i];
				if (index < num_exprs && exprs[index].valid) {
					auto& v = out.values[out.count++];
					char* str = 0;
					int vi;
					v.index = index;
					set_named_variable_value(gvar, value);
					v.valid = execute_calculator_code(exprs[index].expression, &v.value, (SINT32*)0, (PCSTRINGZ * )0);
//					printf("[GaugeConnect] eval '%s': returns %g ('%s')\n", exprs[index].expression, v.value, str ? str : "<no string>");
//					fflush(stdout);
				}
				if (out.count == 20) {
					SimConnect_SetClientData(sim, GaugeOutputCD, GaugeOutputData, 0, 0, sizeof(GaugeOutputStruct), &out);
					out.count = 0;
				}
			}
			out.result = GIComplete;
		}
					   break;
		}
		
		SimConnect_SetClientData(sim, GaugeOutputCD, GaugeOutputData, 0, 0, sizeof(GaugeOutputStruct), &out);
		break;
	}
	}
}

RECV_FUNC(SYSTEM_STATE)
{
	printf("[GaugeConnect] System state: %g '%s'\n", ev->fFloat, ev->szString);
	fflush(stdout);
}

RECV_FUNC(QUIT)
{
}

RECV_FUNC(EVENT_FILENAME)
{
	switch (ev->uEventID)
	{
	default:
		fprintf(stderr, "[GaugeConnect] unhandled event %ld (filename)\n", ev->uEventID);
		fflush(stderr);
		break;
	}
}

RECV_FUNC(EVENT)
{
	switch (ev->uEventID)
	{
	default:
		fprintf(stderr, "[GaugeConnect] unhandled event %ld\n", ev->uEventID);
		fflush(stderr);
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
		fprintf(stderr, "[GaugeConnect] unknown recv? (%ld)\n", recv->dwID);
		fflush(stderr);
		break;
	}
}

extern "C" MSFS_CALLBACK void module_init(void) {

	gvar = register_named_variable("GCVAL");

	if (SimConnect_Open(&sim, "GaugeConnect Module", 0, 0, 0, 0) != S_OK) {
		fprintf(stderr, "[GaugeConnect] Unable to open SimConnect.\n");
		return;
	}

	if (SimConnect_MapClientDataNameToID(sim, "org.uberbox.gauge.input", GaugeInputCD) != S_OK)
		fprintf(stderr, "[GaugeConnect] MapClientDataNameToID(org.uberbox.gauge.input) failed\n");
	if(SimConnect_CreateClientData(sim, GaugeInputCD, sizeof(GaugeInputStruct), 0) != S_OK)
		fprintf(stderr, "[GaugeConnect] CreateClientData(org.uberbox.gauge.input) failed\n");

	if (SimConnect_MapClientDataNameToID(sim, "org.uberbox.gauge.output", GaugeOutputCD) != S_OK)
		fprintf(stderr, "[GaugeConnect] MapClientDataNameToID(org.uberbox.gauge.output) failed\n");
	if(SimConnect_CreateClientData(sim, GaugeOutputCD, sizeof(GaugeOutputStruct), SIMCONNECT_CREATE_CLIENT_DATA_FLAG_READ_ONLY) != S_OK)
		fprintf(stderr, "[GaugeConnect] CreateClientData(org.uberbox.gauge.output) failed\n");

	SimConnect_MapClientEventToSimEvent(sim, GaugeInput, "org.uberbox.gauge.input");
	SimConnect_MapClientEventToSimEvent(sim, GaugeOutput, "org.uberbox.gauge.output");

	SimConnect_AddToClientDataDefinition(sim, GaugeInputData, 0, SIMCONNECT_CLIENTDATATYPE_INT32);
	SimConnect_AddToClientDataDefinition(sim, GaugeInputData, 4, SIMCONNECT_CLIENTDATATYPE_INT16);
	SimConnect_AddToClientDataDefinition(sim, GaugeInputData, 6, SIMCONNECT_CLIENTDATATYPE_INT16);
	SimConnect_AddToClientDataDefinition(sim, GaugeInputData, 8, 248);

	SimConnect_AddToClientDataDefinition(sim, GaugeOutputData, 0, SIMCONNECT_CLIENTDATATYPE_INT32);
	SimConnect_AddToClientDataDefinition(sim, GaugeOutputData, 4, SIMCONNECT_CLIENTDATATYPE_INT16);
	SimConnect_AddToClientDataDefinition(sim, GaugeOutputData, 6, SIMCONNECT_CLIENTDATATYPE_INT16);
	SimConnect_AddToClientDataDefinition(sim, GaugeOutputData, 8, sizeof(GaugeOutputStruct)-8);

	SimConnect_CallDispatch(sim, sim_recv, NULL);

	SimConnect_RequestClientData(sim, GaugeInputCD, GaugeInputReq, GaugeInputData, SIMCONNECT_CLIENT_DATA_PERIOD_ON_SET, SIMCONNECT_CLIENT_DATA_REQUEST_FLAG_DEFAULT);

	fflush(stderr);
	printf("[GaugeConnect] Module started!\n");
}

extern "C" MSFS_CALLBACK void module_deinit(void)
{
	printf("[GaugeConnect] Module going away. :-(\n");
	if (!sim)
		return;
	SimConnect_Close(sim);
}
