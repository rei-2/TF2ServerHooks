#pragma once
#include "Definitions/Definitions.h"
#include "Definitions/Main/CUserCmd.h"
#include "../Utils/Signatures/Signatures.h"
#include "../Utils/Memory/Memory.h"

class CBasePlayer;

MAKE_SIGNATURE(RandomSeed, "server.dll", "0F 45 05 ? ? ? ? 0F B6 C0", 0x0);

namespace G
{
	inline bool Unload = false;
	inline CBasePlayer* DebugTarget = nullptr;
	inline double PlatFloatTimeAdd = 0.0;
	inline bool DebugVisuals = false;
	inline bool DebugInfo = false;
	inline bool TickInfo = false;
	inline bool CritInfo = false;
	inline bool ServerHitboxes = false;
	inline int ServerHitboxesRate = 4;
	inline bool NoBoxAngles = false;
	inline bool DrawHitboxes = true;
	inline bool DrawBoundingBox = false;
	inline bool DrawHeadOnly = false;
	inline float DrawDuration = 0.f;

	inline int* RandomSeed()
	{
		static auto pRandomSeed = reinterpret_cast<int*>(U::Memory.RelToAbs(S::RandomSeed()));
		return pRandomSeed;
	}
};