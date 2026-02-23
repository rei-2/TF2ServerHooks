#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CBaseMultiplayerPlayer_EscortScoringThink, "server.dll", "55 8B EC 51 57 8B F9 D9 87", 0x0);
#else
MAKE_SIGNATURE(CBaseMultiplayerPlayer_EscortScoringThink, "server.dll", "40 57 48 83 EC ? F3 0F 10 81", 0x0);
#endif

#if x86
MAKE_HOOK(CBaseMultiplayerPlayer_EscortScoringThink, S::CBaseMultiplayerPlayer_EscortScoringThink(), void, __fastcall,
	void* ecx, void* edx)
#else
MAKE_HOOK(CBaseMultiplayerPlayer_EscortScoringThink, S::CBaseMultiplayerPlayer_EscortScoringThink(), void,
	void* rcx)
#endif
{
	if (G::DebugInfo)
	{
#if x86
		auto pPlayer = reinterpret_cast<CBasePlayer*>(ecx);
#else
		auto pPlayer = reinterpret_cast<CBasePlayer*>(rcx);
#endif
		float& flAreaCaptureScoreAccumulator = pPlayer->m_flAreaCaptureScoreAccumulator();
		float& flCapPointScoreRate = pPlayer->m_flCapPointScoreRate();
		SDK::Output("CBaseMultiplayerPlayer_EscortScoringThink", std::format("{}, {}; {}", flAreaCaptureScoreAccumulator, flCapPointScoreRate, I::GlobalVars->curtime).c_str());
		SDK::OutputClient("CBaseMultiplayerPlayer_EscortScoringThink", std::format("{}, {}; {}", flAreaCaptureScoreAccumulator, flCapPointScoreRate, I::GlobalVars->curtime).c_str(), pPlayer);
		flAreaCaptureScoreAccumulator += 9999.9f;
	}

#if x86
	CALL_ORIGINAL(ecx, edx);
#else
	CALL_ORIGINAL(rcx);
#endif
}