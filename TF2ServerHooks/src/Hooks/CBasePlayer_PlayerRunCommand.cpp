#include "../SDK/SDK.h"

#if x86
MAKE_SIGNATURE(CBasePlayer_PlayerRunCommand, "server.dll", "55 8B EC 56 8B 75 ? 57 8B F9 83 BF ? ? ? ? ? 8D 97", 0x0);
#else
MAKE_SIGNATURE(CBasePlayer_PlayerRunCommand, "server.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 83 B9 ? ? ? ? ? 48 8B DA", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFWeaponBaseGrenadeProj_SetDetonateTimerLength, "server.dll", "55 8B EC 51 F3 0F 10 05 ? ? ? ? 56", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBaseGrenadeProj_SetDetonateTimerLength, "server.dll", "40 53 48 83 EC ? 8B 91 ? ? ? ? 48 8B D9 F3 0F 10 05", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFGrenadePipebombProjectile_PipebombTouch, "server.dll", "53 8B DC 83 EC ? 83 E4 ? 83 C4 ? 55 8B 6B ? 89 6C 24 ? 8B EC 81 EC ? ? ? ? 56 57 8B F9 89 7D ? E8 ? ? ? ? 8B 73", 0x0);
#else
MAKE_SIGNATURE(CTFGrenadePipebombProjectile_PipebombTouch, "server.dll", "40 55 56 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B F2", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CBaseEntity_TakeDamage, "server.dll", "55 8B EC 81 EC ? ? ? ? 53 56 57 8B F9 8B 0D ? ? ? ? 85 C9", 0x0);
#else
MAKE_SIGNATURE(CBaseEntity_TakeDamage, "server.dll", "40 55 53 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B F9", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFGrenadePipebombProjectile_PipebombTouch_TakeDamage_Call, "server.dll", "8B 06 8B CE 8B 80 ? ? ? ? FF D0 84 C0 0F 84 ? ? ? ? 8D 86 ? ? ? ? 6A", 0x0);
#else
MAKE_SIGNATURE(CTFGrenadePipebombProjectile_PipebombTouch_TakeDamage_Call, "server.dll", "48 8B 06 48 8B CE FF 90 ? ? ? ? 84 C0 0F 84 ? ? ? ? BA ? ? ? ? 48 8D 8E", 0x0);
#endif

#if x86
MAKE_SIGNATURE(CTFWeaponBaseGrenadeProj_Explode, "server.dll", "55 8B EC 81 EC ? ? ? ? 53 56 8B F1 57 56", 0x0);
#else
MAKE_SIGNATURE(CTFWeaponBaseGrenadeProj_Explode, "server.dll", "44 89 44 24 ? 55 56 57 48 8D AC 24", 0x0);
#endif

static float s_flCurtime = 0.f;
static float s_flCreation = 0.f;
static float s_flDesync = 0.f;

#if x86
MAKE_HOOK(CBasePlayer_PlayerRunCommand, S::CBasePlayer_PlayerRunCommand(), void, __fastcall,
	void* ecx, void* edx, CUserCmd* ucmd, IMoveHelper* moveHelper)
#else
MAKE_HOOK(CBasePlayer_PlayerRunCommand, S::CBasePlayer_PlayerRunCommand(), void,
	void* rcx, CUserCmd* ucmd, IMoveHelper* moveHelper)
#endif
{
	if (G::DebugInfo)
		s_flCurtime = I::GlobalVars->curtime;

#if x86
	CALL_ORIGINAL(ecx, edx, ucmd, moveHelper);
#else
	CALL_ORIGINAL(rcx, ucmd, moveHelper);
#endif
}

#if x86
MAKE_HOOK(CTFWeaponBaseGrenadeProj_SetDetonateTimerLength, S::CTFWeaponBaseGrenadeProj_SetDetonateTimerLength(), void, __fastcall,
	void* ecx, void* edx, float timer)
#else
MAKE_HOOK(CTFWeaponBaseGrenadeProj_SetDetonateTimerLength, S::CTFWeaponBaseGrenadeProj_SetDetonateTimerLength(), void,
	void* rcx, float timer)
#endif
{
#if x86
	CALL_ORIGINAL(ecx, edx, timer);
#else
	CALL_ORIGINAL(rcx, timer);
#endif

	if (!G::DebugInfo)
	{
		s_flCreation = I::GlobalVars->curtime;
#if x86
		float flDetonateTime = *reinterpret_cast<float*>(uintptr_t(ecx) + 1332);
#else
		float flDetonateTime = *reinterpret_cast<float*>(uintptr_t(rcx) + 1688);
#endif
		float flDuration = flDetonateTime - I::GlobalVars->curtime;
		s_flDesync = I::GlobalVars->curtime - s_flCurtime;
		SDK::Output("CTFWeaponBaseGrenadeProj_SetDetonateTimerLength", std::format("{} ({}, {} ({}{}) -> {})", ceilf(flDuration / 0.195f) * 0.195f + s_flDesync, flDuration, I::GlobalVars->curtime, s_flDesync < 0 ? "" : "+", s_flDesync, flDetonateTime).c_str(), { 0, 0, 255 });
	}
}

/*
#if x86
MAKE_HOOK(CTFGrenadePipebombProjectile_PipebombTouch, S::CTFGrenadePipebombProjectile_PipebombTouch(), void, __fastcall,
	void* ecx, void* edx, CBaseEntity* pOther)
#else
MAKE_HOOK(CTFGrenadePipebombProjectile_PipebombTouch, S::CTFGrenadePipebombProjectile_PipebombTouch(), void,
	void* rcx, CBaseEntity* pOther)
#endif
{
#if x86
	CALL_ORIGINAL(ecx, edx, pOther);
#else
	CALL_ORIGINAL(rcx, pOther);
#endif

	if (G::DebugInfo)
		SDK::Output("CTFGrenadePipebombProjectile_PipebombTouch", std::format("{} ({})", I::GlobalVars->curtime - s_flCreation, I::GlobalVars->curtime).c_str(), { 0, 255, 0 });
}
*/

#if x86
MAKE_HOOK(CBaseEntity_TakeDamage, S::CBaseEntity_TakeDamage(), void, __fastcall,
	void* ecx, void* edx, void* inputInfo)
#else
MAKE_HOOK(CBaseEntity_TakeDamage, S::CBaseEntity_TakeDamage(), void,
	void* rcx, void* inputInfo)
#endif
{
#if x86
	CALL_ORIGINAL(ecx, edx, inputInfo);
#else
	CALL_ORIGINAL(rcx, inputInfo);
#endif

	if (G::DebugInfo)
	{
		const auto dwRetAddr = uintptr_t(_ReturnAddress());
		const auto dwDesired = S::CTFGrenadePipebombProjectile_PipebombTouch_TakeDamage_Call();
		if (dwRetAddr == dwDesired)
			SDK::Output("CBaseEntity_TakeDamage", std::format("{} ({})", I::GlobalVars->curtime - s_flCreation + s_flDesync, I::GlobalVars->curtime).c_str(), { 0, 255, 0 });
	}
}

#if x86
MAKE_HOOK(CTFWeaponBaseGrenadeProj_Explode, S::CTFWeaponBaseGrenadeProj_Explode(), void, __fastcall,
	void* ecx, void* edx, trace_t* pTrace, int bitsDamageType)
#else
MAKE_HOOK(CTFWeaponBaseGrenadeProj_Explode, S::CTFWeaponBaseGrenadeProj_Explode(), void,
	void* rcx, trace_t* pTrace, int bitsDamageType)
#endif
{
#if x86
	CALL_ORIGINAL(ecx, edx, pTrace, bitsDamageType);
#else
	CALL_ORIGINAL(rcx, pTrace, bitsDamageType);
#endif

	if (G::DebugInfo)
		SDK::Output("CTFWeaponBaseGrenadeProj_Explode", std::format("{} ({})", I::GlobalVars->curtime - s_flCreation + s_flDesync, I::GlobalVars->curtime).c_str(), { 255, 0, 0 });
}