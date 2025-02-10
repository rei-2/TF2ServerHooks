#include "../SDK/SDK.h"

MAKE_SIGNATURE(CBasePlayer_ProcessUsercmds, "server.dll", "40 53 55 56 57 41 54 48 83 EC ? 4C 89 6C 24", 0x0);
MAKE_SIGNATURE(CBaseAnimating_DrawServerHitboxes, "server.dll", "44 88 44 24 ? 53 48 81 EC", 0x0);

MAKE_HOOK(CBasePlayer_ProcessUsercmds, S::CBasePlayer_ProcessUsercmds(), void,
	void* rcx, CUserCmd* cmds, int numcmds, int totalcmds, int dropped_packets, bool paused)
{
	bool bInAttack = false;
	for (int i = totalcmds - 1; i >= 0; i--)
	{
		CUserCmd* pCmd = &cmds[totalcmds - 1 - i];
		if (pCmd && pCmd->buttons & IN_ATTACK)
			bInAttack = true;
	}
	if (bInAttack)
	{
		//SDK::Output("ProcessUsercmds", std::format("{}: {}", SDK::PlatFloatTime(), std::bit_cast<int32_t>(float(SDK::PlatFloatTime() * 1000.0)) & 255).c_str(), { 255, 0, 0, 255 });

		auto pPlayer = reinterpret_cast<CTFPlayer*>(rcx);

		float flTime = TICKS_TO_TIME(pPlayer->m_nTickBase());
		float flAttack = pPlayer->m_flNextAttack();
		SDK::Output("ProcessUsercmds", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str());
		SDK::OutputClient("ProcessUsercmds", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str(), pPlayer);
	}

	if (G::ServerHitboxes)
	{
		G::DebugTarget = reinterpret_cast<CTFPlayer*>(rcx);

		// don't send every tick to prevent throttling
		if (!(I::GlobalVars->tickcount % G::ServerHitboxesRate))
		{
			for (CBaseEntity* pEntity = I::GlobalEntityList->FirstEnt(); pEntity; pEntity = I::GlobalEntityList->NextEnt(pEntity))
			{
				auto pPlayer = pEntity->As<CTFPlayer>();
				if (!pEntity->IsPlayer() || pEntity->entindex() == G::DebugTarget->entindex())
					continue;

				S::CBaseAnimating_DrawServerHitboxes.Call<void>(pPlayer, TICK_INTERVAL * G::ServerHitboxesRate, true);
			}
		}
	}

	return CALL_ORIGINAL(rcx, cmds, numcmds, totalcmds, dropped_packets, paused);
}