#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBaseMultiplayerPlayer_EscortScoringThink, "server.dll", "40 57 48 83 EC ? F3 0F 10 81", 0x0);

MAKE_HOOK(CBaseMultiplayerPlayer_EscortScoringThink, S::CBaseMultiplayerPlayer_EscortScoringThink(), void,
	void* rcx)
{
	if (G::DebugInfo)
	{
		auto pPlayer = reinterpret_cast<CBasePlayer*>(rcx);
		float& flAreaCaptureScoreAccumulator = pPlayer->m_flAreaCaptureScoreAccumulator();
		float& flCapPointScoreRate = pPlayer->m_flCapPointScoreRate();
		SDK::Output("CBaseMultiplayerPlayer_EscortScoringThink", std::format("{}, {}; {}", flAreaCaptureScoreAccumulator, flCapPointScoreRate, I::GlobalVars->curtime).c_str());
		SDK::OutputClient("CBaseMultiplayerPlayer_EscortScoringThink", std::format("{}, {}; {}", flAreaCaptureScoreAccumulator, flCapPointScoreRate, I::GlobalVars->curtime).c_str(), pPlayer);
		flAreaCaptureScoreAccumulator += 9999.9f;
	}

	CALL_ORIGINAL(rcx);
}