#pragma once
#include "Interface.h"

class CSaveRestoreData;

class CGlobalVarsBase
{
public:
	float realtime;
	int framecount;
	float absoluteframetime;
	float curtime;
	float frametime;
	int maxClients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
	int simTicksThisFrame;
	int network_protocol;
	CSaveRestoreData* pSaveData;
	bool m_bClient;
	int nTimestampNetworkingBase;
	int nTimestampRandomizeWindow;
};

MAKE_INTERFACE_SIGNATURE(CGlobalVarsBase, GlobalVars, "server.dll", "48 8B 15 ? ? ? ? 0F 57 D2 F3 0F 10 2D", 0x0, 1);