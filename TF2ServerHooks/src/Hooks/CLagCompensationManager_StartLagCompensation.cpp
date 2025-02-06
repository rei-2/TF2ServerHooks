#include "../SDK/SDK.h"

MAKE_SIGNATURE(CLagCompensationManager_StartLagCompensation, "server.dll", "40 55 57 41 55 48 81 EC", 0x0);
//MAKE_SIGNATURE(CBaseAnimating_DrawServerHitboxes, "server.dll", "44 88 44 24 ? 53 48 81 EC", 0x0);
MAKE_SIGNATURE(NDebugOverlay_BoxAngles, "server.dll", "48 83 EC ? 4C 8B D9 48 8B 0D ? ? ? ? 48 85 C9 74 ? 8B 84 24 ? ? ? ? F3 0F 10 84 24 ? ? ? ? 4C 8B 11 F3 0F 11 44 24 ? 89 44 24 ? 8B 84 24 ? ? ? ? 89 44 24 ? 8B 84 24 ? ? ? ? 89 44 24 ? 8B 84 24 ? ? ? ? 89 44 24 ? 4C 89 4C 24", 0x0);

static CBasePlayer* pTarget = nullptr;

MAKE_HOOK(CLagCompensationManager_StartLagCompensation, S::CLagCompensationManager_StartLagCompensation(), void,
	void* rcx, CBasePlayer* player, CUserCmd* cmd)
{
	pTarget = player;

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
	SDK::OutputClient("StartLagCompensation", std::format("{}, {}, {}, {}, {}", correct, I::GlobalVars->tickcount, deltaTime, lerpTicks, targettick).c_str(), pTarget);

	if (fabs(deltaTime) > 0.2f)
	{
		targettick = I::GlobalVars->tickcount - TIME_TO_TICKS(correct);
		SDK::Output("StartLagCompensation", std::format("Delta failed, set to {}", targettick).c_str());
		SDK::OutputClient("StartLagCompensation", std::format("Delta failed, set to {}", targettick).c_str(), pTarget);
	}

	return CALL_ORIGINAL(rcx, player, cmd);
}

/*
MAKE_HOOK(CBaseAnimating_DrawServerHitboxes, S::CBaseAnimating_DrawServerHitboxes(), void,
	void* rcx, float duration, bool monocolor)
{
	SDK::Output("DrawServerHitboxes", std::format("{}, {}", duration, monocolor).c_str());
	CALL_ORIGINAL(rcx, duration, monocolor);
}
*/


MAKE_HOOK(NDebugOverlay_BoxAngles, S::NDebugOverlay_BoxAngles(), void,
	const Vector& origin, const Vector& mins, const Vector& maxs, const QAngle& angles, int r, int g, int b, int a, float duration)
{
	SDK::OutputClient("BoxAngles", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", origin.x, origin.y, origin.z, mins.x, mins.y, mins.z, maxs.x, maxs.y, maxs.z, angles.x, angles.y, angles.z, r, g, b, a, duration).c_str(), pTarget);
	CALL_ORIGINAL(origin, mins, maxs, angles, r, g, b, a, duration);
}