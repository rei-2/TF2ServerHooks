#include "../SDK/SDK.h"

MAKE_SIGNATURE(CTFWeaponBaseGun_FireProjectile, "server.dll", "48 8B C4 48 89 70 ? 55 57 41 56 48 8D 68 ? 48 81 EC ? ? ? ? 48 8B F2", 0x0);

MAKE_HOOK(CTFWeaponBaseGun_FireProjectile, S::CTFWeaponBaseGun_FireProjectile(), CBaseEntity*,
	void* rcx, CTFPlayer* pPlayer)
{
	float flTime = I::GlobalVars->curtime;
	float flAttack = pPlayer->m_flNextAttack();
	SDK::Output("FireProjectile", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str());
	SDK::OutputClient("FireProjectile", std::format("{}, {}, {}", flTime - flAttack, TIME_TO_TICKS(flAttack - flTime), flTime < flAttack).c_str(), pPlayer);

	return CALL_ORIGINAL(rcx, pPlayer);
}