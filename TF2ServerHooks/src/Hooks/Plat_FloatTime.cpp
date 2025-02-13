#include "../SDK/SDK.h"

#if x86
MAKE_HOOK(Plat_FloatTime, U::Memory.GetModuleExport<uintptr_t>("tier0.dll", "Plat_FloatTime"), double, __cdecl,
	)
#else
MAKE_HOOK(Plat_FloatTime, U::Memory.GetModuleExport<uintptr_t>("tier0.dll", "Plat_FloatTime"), double,
	)
#endif
{
	return CALL_ORIGINAL() + G::PlatFloatTimeAdd;
}