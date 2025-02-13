#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(DataTable_Warning, "engine.dll", "55 8B EC B8 ? ? ? ? E8 ? ? ? ? 8D 45 ? 50 FF 75 ? 8D 85 ? ? ? ? 68 ? ? ? ? 50 E8 ? ? ? ? 8D 85 ? ? ? ? 50 68 ? ? ? ? FF 15", 0x0);
#else
MAKE_SIGNATURE(DataTable_Warning, "engine.dll", "48 89 4C 24 ? 48 89 54 24 ? 4C 89 44 24 ? 4C 89 4C 24 ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 4C 8B C1 4C 8D 8C 24 ? ? ? ? 48 8D 4C 24 ? 8D 50", 0x0);
#endif

#if x86
MAKE_HOOK(DataTable_Warning, S::DataTable_Warning(), void, __cdecl,
	const char* pInMessage, ...)
#else
MAKE_HOOK(DataTable_Warning, S::DataTable_Warning(), void,
	const char* pInMessage, ...)
#endif
{
	// dont send datatable warnings
}