#pragma once
#include "Interface.h"

class IUniformRandomStream
{
public:
	virtual void SetSeed(int iSeed) = 0;
	virtual float RandomFloat(float flMinVal = 0.f, float flMaxVal = 1.f) = 0;
	virtual int	RandomInt(int iMinVal, int iMaxVal) = 0;
	virtual float RandomFloatExp(float flMinVal = 0.f, float flMaxVal = 1.f, float flExponent = 1.f) = 0;
};

#if x86
MAKE_INTERFACE_SIGNATURE(IUniformRandomStream, UniformRandomStream, "server.dll", "8B 35 ? ? ? ? 83 EC ? D9 E8", 0x2, 2);
#else
MAKE_INTERFACE_SIGNATURE(IUniformRandomStream, UniformRandomStream, "server.dll", "48 8B 1D ? ? ? ? 41 0F 28 D4", 0x0, 1);
#endif