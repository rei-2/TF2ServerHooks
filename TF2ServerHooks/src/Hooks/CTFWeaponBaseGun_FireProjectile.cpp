#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CTFWeaponBaseGun_FireProjectile, "server.dll", "55 8B EC 81 EC ? ? ? ? 53 56 57 6A ? 6A", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBaseGun_FireProjectile, "server.dll", "48 8B C4 55 56 57 41 56 48 8D 68", 0x0);
#endif

#if x86
MAKE_HOOK(CTFWeaponBaseGun_FireProjectile, S::CTFWeaponBaseGun_FireProjectile(), CBaseEntity*, __fastcall,
	void* ecx, void* edx, CTFPlayer* pPlayer)
#else
MAKE_HOOK(CTFWeaponBaseGun_FireProjectile, S::CTFWeaponBaseGun_FireProjectile(), CBaseEntity*,
	void* rcx, CTFPlayer* pPlayer)
#endif
{
#if x86
	reinterpret_cast<CBaseEntity*>(ecx)->m_vecOrigin();
#else
	reinterpret_cast<CBaseEntity*>(rcx)->m_vecOrigin();
#endif

	float flTime = I::GlobalVars->curtime;
	float flAttack = pPlayer->m_flNextAttack();
	SDK::Output("FireProjectile", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str());
	SDK::OutputClient("FireProjectile", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str(), pPlayer);

#if x86
	return CALL_ORIGINAL(ecx, edx, pPlayer);
#else
	return CALL_ORIGINAL(rcx, pPlayer);
#endif
}