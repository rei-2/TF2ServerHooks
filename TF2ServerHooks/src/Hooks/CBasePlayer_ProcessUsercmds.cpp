#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CBasePlayer_ProcessUsercmds, "server.dll", "55 8B EC 83 EC ? 53 8B D9 56 57 FF B3", 0x0);
#else
MAKE_SIGNATURE(CBasePlayer_ProcessUsercmds, "server.dll", "40 53 55 56 57 41 54 48 83 EC ? 4C 89 6C 24", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFWeaponBase_IncrementAmmo, "server.dll", "55 8B EC 83 EC ? 56 57 6A ? 68 ? ? ? ? 68 ? ? ? ? 6A ? 8B F1 E8 ? ? ? ? 50 E8 ? ? ? ? 83 C4", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBase_IncrementAmmo, "server.dll", "40 53 57 48 83 EC ? 48 8B D9 E8 ? ? ? ? 48 8B C8", 0x0);
#endif


#if x86
MAKE_HOOK(CBasePlayer_ProcessUsercmds, S::CBasePlayer_ProcessUsercmds(), void, __fastcall,
	void* ecx, void* edx, CUserCmd* cmds, int numcmds, int totalcmds, int dropped_packets, bool paused)
#else
MAKE_HOOK(CBasePlayer_ProcessUsercmds, S::CBasePlayer_ProcessUsercmds(), void,
	void* rcx, CUserCmd* cmds, int numcmds, int totalcmds, int dropped_packets, bool paused)
#endif
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

		//auto pPlayer = reinterpret_cast<CTFPlayer*>(rcx);

		//float flTime = TICKS_TO_TIME(pPlayer->m_nTickBase());
		//float flAttack = pPlayer->m_flNextAttack();
		//SDK::Output("ProcessUsercmds", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str());
		//SDK::OutputClient("ProcessUsercmds", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str(), pPlayer);
	}

	if (G::ServerHitboxes)
	{
#if x86
		G::DebugTarget = reinterpret_cast<CTFPlayer*>(ecx);
#else
		G::DebugTarget = reinterpret_cast<CTFPlayer*>(rcx);
#endif

		// don't send every tick to prevent throttling
		if (!(I::GlobalVars->tickcount % G::ServerHitboxesRate))
		{
			for (CBaseEntity* pEntity = I::GlobalEntityList->FirstEnt(); pEntity; pEntity = I::GlobalEntityList->NextEnt(pEntity))
			{
				auto pPlayer = pEntity->As<CTFPlayer>();
				if (!pEntity->IsPlayer() || pEntity->entindex() == G::DebugTarget->entindex())
					continue;
#if !x86
				pPlayer->DrawServerHitboxes(TICK_INTERVAL * G::ServerHitboxesRate, true);
#endif
			}
		}
	}
#if x86
	return CALL_ORIGINAL(ecx, edx, cmds, numcmds, totalcmds, dropped_packets, paused);
#else
	return CALL_ORIGINAL(rcx, cmds, numcmds, totalcmds, dropped_packets, paused);
#endif
}

#if x86
MAKE_HOOK(CTFWeaponBase_IncrementAmmo, S::CTFWeaponBase_IncrementAmmo(), void, __fastcall,
	void* ecx, void* edx)
#else
MAKE_HOOK(CTFWeaponBase_IncrementAmmo, S::CTFWeaponBase_IncrementAmmo(), void,
	void* rcx)
#endif
{
#if x86
	auto pWeapon = reinterpret_cast<CTFWeaponBase*>(ecx);
#else
	auto pWeapon = reinterpret_cast<CTFWeaponBase*>(rcx);
#endif
	auto pLocal = pWeapon->m_hOwnerEntity()->As<CTFPlayer>();
	if (pLocal && pWeapon)
	{
		SDK::Output("IncrementAmmo", std::format("{}\n\t{}, {}\n\t{}, {}",
			pWeapon->m_iClip1(),
			TIME_TO_TICKS(pLocal->m_flNextAttack() - I::GlobalVars->curtime),
			pLocal->m_flNextAttack() - I::GlobalVars->curtime,
			TIME_TO_TICKS(I::GlobalVars->curtime - pWeapon->m_flReloadPriorNextFire()),
			I::GlobalVars->curtime - pWeapon->m_flReloadPriorNextFire()).c_str());
	}

#if x86
	CALL_ORIGINAL(ecx, edx);
#else
	CALL_ORIGINAL(rcx);
#endif
}