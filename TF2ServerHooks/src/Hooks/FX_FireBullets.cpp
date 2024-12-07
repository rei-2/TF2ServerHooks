#include "../SDK/SDK.h"

MAKE_SIGNATURE(FX_FireBullets, "server.dll", "48 89 5C 24 ? 4C 89 4C 24 ? 55 56 41 54", 0x0);

MAKE_HOOK(FX_FireBullets, S::FX_FireBullets(), void,
	void* pWpn, int iPlayer, const Vec3& vecOrigin, const Vec3& vecAngles, int iWeapon, int iMode, int iSeed, float flSpread, float flDamage, bool bCritical)
{
	SDK::Output("FX_FireBullets", std::format("{}", iSeed).c_str(), { 255, 0, 0, 255 });

	return CALL_ORIGINAL(pWpn, iPlayer, vecOrigin, vecAngles, iWeapon, iMode, iSeed, flSpread, flDamage, bCritical);
}