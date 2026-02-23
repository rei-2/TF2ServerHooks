#include "../SDK/SDK.h"

#if x86
MAKE_HOOK(CBaseAnimating_DrawServerHitboxes, S::CBaseAnimating_DrawServerHitboxes(), void, __fastcall,
	void* ecx, void* edx, float duration, bool monocolor)
#else
MAKE_HOOK(CBaseAnimating_DrawServerHitboxes, S::CBaseAnimating_DrawServerHitboxes(), void,
	void* rcx, float duration, bool monocolor)
#endif
{
#if x86
	auto pEntity = reinterpret_cast<CBaseAnimating*>(ecx);
#else
	auto pEntity = reinterpret_cast<CBaseAnimating*>(rcx);
#endif
	if (G::DebugTarget && G::DrawBoundingBox && pEntity->IsPlayer())
	{
		Vec3 origin = pEntity->m_vecOrigin();
		Vec3 mins = pEntity->m_vecMins();
		Vec3 maxs = pEntity->m_vecMaxs();
		Vec3 angles = {};
		int r = 255, g = 127, b = 127, a = 0;

		SDK::OutputClient("Box", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", origin.x, origin.y, origin.z, mins.x, mins.y, mins.z, maxs.x, maxs.y, maxs.z, angles.x, angles.y, angles.z, r, g, b, a, G::DrawDuration ? G::DrawDuration : duration).c_str(), G::DebugTarget);
	}

	if (!G::DrawHitboxes)
		return;
	if (G::DrawHeadOnly)
		monocolor = false;

#if x86
	CALL_ORIGINAL(ecx, edx, duration, monocolor);
#else
	CALL_ORIGINAL(rcx, duration, monocolor);
#endif
}