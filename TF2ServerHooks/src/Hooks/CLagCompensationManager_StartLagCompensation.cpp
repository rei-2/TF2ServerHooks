#include "../SDK/SDK.h"

MAKE_SIGNATURE(CLagCompensationManager_StartLagCompensation, "server.dll", "40 55 57 41 55 48 81 EC", 0x0);

MAKE_HOOK(CLagCompensationManager_StartLagCompensation, S::CLagCompensationManager_StartLagCompensation(), void,
	void* rcx, CBasePlayer* player, CUserCmd* cmd)
{
	static auto sv_maxunlag = U::ConVars.FindVar("sv_maxunlag");

	int lerpTicks = TIME_TO_TICKS(player->m_fLerpTime());
	int targettick = cmd->tick_count - lerpTicks;

	float correct = 0.f;
	if (INetChannelInfo* nci = I::EngineServer->GetPlayerNetInfo(player->entindex()))
		correct += nci->GetLatency(FLOW_OUTGOING);

	correct += TICKS_TO_TIME(lerpTicks);
	correct = std::clamp(correct, 0.f, sv_maxunlag->GetFloat());

	float deltaTime = correct - TICKS_TO_TIME(I::GlobalVars->tickcount - targettick);

	SDK::Output("StartLagCompensation", std::format("{}, {}, {}, {}, {}", correct, I::GlobalVars->tickcount, deltaTime, lerpTicks, targettick).c_str());

	if (fabs(deltaTime) > 0.2f)
	{
		targettick = I::GlobalVars->tickcount - TIME_TO_TICKS(correct);
		SDK::Output("StartLagCompensation", std::format("Delta failed, set to {}", targettick).c_str());
	}

	return CALL_ORIGINAL(rcx, player, cmd);
}