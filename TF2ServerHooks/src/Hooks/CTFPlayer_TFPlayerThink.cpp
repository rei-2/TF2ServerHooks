#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CTFPlayer_TFPlayerThink, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 81 EC ? ? ? ? 56 57 8B F9 8B 8F ? ? ? ? 85 C9 74 ? 8B 41", 0x0);
#else
MAKE_SIGNATURE(CTFPlayer_TFPlayerThink, "server.dll", "48 8B C4 48 89 48 ? 55 53 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70", 0x0);
#endif

#if x86
MAKE_HOOK(CTFPlayer_TFPlayerThink, S::CTFPlayer_TFPlayerThink(), void, __fastcall,
	void* ecx, void* edx)
#else
MAKE_HOOK(CTFPlayer_TFPlayerThink, S::CTFPlayer_TFPlayerThink(), void,
	void* rcx)
#endif
{
	if (G::DebugInfo)
	{
		static float flStaticTime = I::GlobalVars->curtime;
		const float flLastTime = flStaticTime;
		const float flCurrTime = flStaticTime = I::GlobalVars->curtime;

		SDK::Output("CTFPlayer_TFPlayerThink", std::format("{} ({})", flCurrTime - flLastTime, flCurrTime).c_str());
	}

#if x86
	return CALL_ORIGINAL(ecx, edx);
#else
	return CALL_ORIGINAL(rcx);
#endif
}