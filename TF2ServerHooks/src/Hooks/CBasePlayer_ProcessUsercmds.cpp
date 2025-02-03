#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBasePlayer_ProcessUsercmds, "server.dll", "40 53 55 56 57 41 54 48 83 EC ? 4C 89 6C 24", 0x0);

MAKE_HOOK(CBasePlayer_ProcessUsercmds, S::CBasePlayer_ProcessUsercmds(), void,
	void* rcx, CUserCmd* cmds, int numcmds, int totalcmds, int dropped_packets, bool paused)
{
	bool bPrint = false;
	for (int i = totalcmds - 1; i >= 0; i--)
	{
		CUserCmd* pCmd = &cmds[totalcmds - 1 - i];
		if (pCmd && pCmd->buttons & IN_ATTACK)
			bPrint = true;
	}
	SDK::Output("ProcessUsercmds", std::format("{}: {}", SDK::PlatFloatTime(), std::bit_cast<int32_t>(float(SDK::PlatFloatTime() * 1000.0)) & 255).c_str(), { 255, 0, 0, 255 }, bPrint);

	return CALL_ORIGINAL(rcx, cmds, numcmds, totalcmds, dropped_packets, paused);
}