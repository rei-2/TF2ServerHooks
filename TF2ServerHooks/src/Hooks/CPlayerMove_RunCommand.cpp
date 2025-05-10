#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CPlayerMove_RunCommand, "server.dll", "55 8B EC 83 EC ? 56 57 8B 7D ? 89 4D ? 8B B7", 0x0);
#else
MAKE_SIGNATURE(CPlayerMove_RunCommand, "server.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 8B 9A", 0x0);
#endif

static std::unordered_map<int, int> mTickStorage = {};

#if x86
MAKE_HOOK(CPlayerMove_RunCommand, S::CPlayerMove_RunCommand(), void, __fastcall,
	void* ecx, void* edx, CBasePlayer* player, CUserCmd* ucmd, IMoveHelper* moveHelper)
#else
MAKE_HOOK(CPlayerMove_RunCommand, S::CPlayerMove_RunCommand(), void,
	void* rcx, CBasePlayer* player, CUserCmd* ucmd, IMoveHelper* moveHelper)
#endif
{
	if (G::TickInfo)
	{
		int nTicks = player->m_nMovementTicksForUserCmdProcessingRemaining() - 1;
		int iIndex = player->entindex();
		if (nTicks != mTickStorage[iIndex])
		{
			mTickStorage[iIndex] = nTicks;
			SDK::OutputClient("Ticks", std::format("{}", nTicks).c_str(), player, HUD_PRINTTALK);
		}
	}

#if x86
	CALL_ORIGINAL(ecx, edx, player, ucmd, moveHelper);
#else
	CALL_ORIGINAL(rcx, player, ucmd, moveHelper);
#endif
}