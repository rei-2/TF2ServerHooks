#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CLagCompensationManager_StartLagCompensation, "server.dll", "55 8B EC 83 EC ? 57 8B F9 89 7D ? 83 BF ? ? ? ? ? 74", 0x0);
#else
MAKE_SIGNATURE(CLagCompensationManager_StartLagCompensation, "server.dll", "40 55 57 41 55 48 81 EC", 0x0);
#endif

#if x86
MAKE_HOOK(CLagCompensationManager_StartLagCompensation, S::CLagCompensationManager_StartLagCompensation(), void, __fastcall,
	void* ecx, void* edx, CBasePlayer* player, CUserCmd* cmd)
#else
MAKE_HOOK(CLagCompensationManager_StartLagCompensation, S::CLagCompensationManager_StartLagCompensation(), void,
	void* rcx, CBasePlayer* player, CUserCmd* cmd)
#endif
{
	G::DebugTarget = player;

	static auto sv_maxunlag = U::ConVars.FindVar("sv_maxunlag");

	int lerpTicks = TIME_TO_TICKS(player->m_fLerpTime());
	int targettick = cmd->tick_count - lerpTicks;

	float correct = 0.f;
	INetChannelInfo* nci = I::EngineServer->GetPlayerNetInfo(player->entindex());
	float flOutgoing = nci ? nci->GetLatency(FLOW_OUTGOING) : 0.f;
	float flIncoming = nci ? nci->GetLatency(FLOW_INCOMING) : 0.f;
	correct += flOutgoing;

	correct += TICKS_TO_TIME(lerpTicks);
	correct = std::clamp(correct, 0.f, sv_maxunlag->GetFloat());

	float deltaTime = correct - TICKS_TO_TIME(I::GlobalVars->tickcount - targettick);

	SDK::Output("StartLagCompensation", std::format("{}, {}; {}, {}, {}; {}, {}", correct, I::GlobalVars->tickcount, deltaTime, lerpTicks, targettick, flOutgoing, flIncoming).c_str());
	SDK::OutputClient("StartLagCompensation", std::format("{}, {}; {}, {}, {}; {}, {}", correct, I::GlobalVars->tickcount, deltaTime, lerpTicks, targettick, flOutgoing, flIncoming).c_str(), player);

	if (fabs(deltaTime) > 0.2f)
	{
		targettick = I::GlobalVars->tickcount - TIME_TO_TICKS(correct);
		SDK::Output("StartLagCompensation", std::format("Delta failed, set to {}", targettick).c_str());
		SDK::OutputClient("StartLagCompensation", std::format("Delta failed, set to {}", targettick).c_str(), player);
	}

	if (!G::DebugVisuals)
#if x86
		CALL_ORIGINAL(ecx, edx, player, cmd);
#else
		CALL_ORIGINAL(rcx, player, cmd);
#endif
	else
	{
		static auto sv_showlagcompensation = U::ConVars.FindVar("sv_showlagcompensation");
		int iOriginal = sv_showlagcompensation->GetInt();
		sv_showlagcompensation->SetValue(1);

#if x86
		CALL_ORIGINAL(ecx, edx, player, cmd);
#else
		CALL_ORIGINAL(rcx, player, cmd);
#endif

		sv_showlagcompensation->SetValue(iOriginal);
	}
}