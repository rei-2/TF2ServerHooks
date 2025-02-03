#pragma once
#include "Definitions/Definitions.h"
#include "Definitions/Main/CUserCmd.h"
#include "../Utils/Signatures/Signatures.h"
#include "../Utils/Memory/Memory.h"

MAKE_SIGNATURE(RandomSeed, "server.dll", "0F 45 05 ? ? ? ? 0F B6 C0", 0x0);

namespace G
{
	inline bool Unload = false;
	inline double PlatFloatTimeAdd = 0.0;

	inline int* RandomSeed()
	{
		static auto dest = U::Memory.RelToAbs(S::RandomSeed());
		return reinterpret_cast<int*>(dest);
	}
};