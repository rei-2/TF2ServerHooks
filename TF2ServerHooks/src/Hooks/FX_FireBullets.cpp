#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(FX_FireBullets, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 81 EC ? ? ? ? 56 8B 73 ? 57 56 E8", 0x0);
#else
MAKE_SIGNATURE(FX_FireBullets, "server.dll", "48 89 5C 24 ? 4C 89 4C 24 ? 55 56 41 54", 0x0);
#endif

#if x86
MAKE_HOOK(FX_FireBullets, S::FX_FireBullets(), void, __cdecl,
	void* pWpn, int iPlayer, const Vec3& vecOrigin, const Vec3& vecAngles, int iWeapon, int iMode, int iSeed, float flSpread, float flDamage, bool bCritical)
#else
MAKE_HOOK(FX_FireBullets, S::FX_FireBullets(), void,
	void* pWpn, int iPlayer, const Vec3& vecOrigin, const Vec3& vecAngles, int iWeapon, int iMode, int iSeed, float flSpread, float flDamage, bool bCritical)
#endif
{
	if (G::DebugInfo)
	{
		G::DebugTarget = reinterpret_cast<CTFPlayer*>(I::GlobalEntityList->GetEntInfoPtrByIndex(iPlayer)->m_pEntity);

		SDK::Output("FX_FireBullets", std::format("{}, {}", iSeed, flSpread).c_str(), { 255, 0, 0, 255 });
		SDK::OutputClient("FX_FireBullets", std::format("{}, {}", iSeed, flSpread).c_str(), G::DebugTarget);
	}

	return CALL_ORIGINAL(pWpn, iPlayer, vecOrigin, vecAngles, iWeapon, iMode, iSeed, flSpread, flDamage, bCritical);
}