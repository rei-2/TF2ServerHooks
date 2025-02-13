#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(NDebugOverlay_BoxAngles, "server.dll", "55 8B EC 8B 0D ? ? ? ? 85 C9 74 ? D9 45 ? 8B 01 51 D9 1C 24 FF 75 ? FF 75 ? FF 75 ? FF 75 ? FF 75", 0x0);
#else
MAKE_SIGNATURE(NDebugOverlay_BoxAngles, "server.dll", "48 83 EC ? 4C 8B D9 48 8B 0D ? ? ? ? 48 85 C9 74 ? 8B 84 24 ? ? ? ? F3 0F 10 84 24 ? ? ? ? 4C 8B 11 F3 0F 11 44 24 ? 89 44 24 ? 8B 84 24 ? ? ? ? 89 44 24 ? 8B 84 24 ? ? ? ? 89 44 24 ? 8B 84 24 ? ? ? ? 89 44 24 ? 4C 89 4C 24", 0x0);
#endif

#if x86
MAKE_HOOK(NDebugOverlay_BoxAngles, S::NDebugOverlay_BoxAngles(), void, __cdecl,
	const Vector& origin, const Vector& mins, const Vector& maxs, const QAngle& angles, int r, int g, int b, int a, float duration)
#else
MAKE_HOOK(NDebugOverlay_BoxAngles, S::NDebugOverlay_BoxAngles(), void,
	const Vector& origin, const Vector& mins, const Vector& maxs, const QAngle& angles, int r, int g, int b, int a, float duration)
#endif
{
	SDK::OutputClient("BoxAngles", std::format("{} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {}", origin.x, origin.y, origin.z, mins.x, mins.y, mins.z, maxs.x, maxs.y, maxs.z, angles.x, angles.y, angles.z, r, g, b, a, duration).c_str(), G::DebugTarget);
	CALL_ORIGINAL(origin, mins, maxs, angles, r, g, b, a, duration);
}