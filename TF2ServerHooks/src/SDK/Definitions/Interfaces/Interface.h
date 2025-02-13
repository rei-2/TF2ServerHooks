#pragma once
#include "../../../Utils/Interfaces/Interfaces.h"
#include "../../../Utils/Signatures/Signatures.h"

#if x86
MAKE_SIGNATURE(CAttributeManager_AttribHookFloat, "server.dll", "55 8B EC 83 EC ? 8B 0D ? ? ? ? 53 56 57 33 FF 33 DB 89 7D ? 89 5D ? 8B 41 ? 85 C0 74 ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 68 ? ? ? ? 6A ? 68 ? ? ? ? 53 53 53 53 8D 4D ? 51 50 8B 40 ? FF D0 8B 5D ? 83 C4 ? 8B 7D ? 8B 0D ? ? ? ? 8B 71 ? 8B 0D ? ? ? ? 89 75 ? 8B 81 ? ? ? ? 89 45 ? 85 C0 74 ? 6A ? 6A ? 68 ? ? ? ? 6A ? 68 ? ? ? ? FF 15 ? ? ? ? 8B 0D ? ? ? ? 8B 45 ? 85 C0 74 ? 80 38 ? 74 ? 8B 55 ? 85 D2 74 ? 8B 92 ? ? ? ? 89 55 ? 85 D2 74 ? 80 7D ? ? 50 74 ? 8D 45 ? 50 E8 ? ? ? ? EB ? 8D 45 ? 50 E8 ? ? ? ? 8B 4D ? 83 C4 ? 8B 30 8B 01 FF 10 FF 75 ? D9 45", 0x0);
#else
MAKE_SIGNATURE(CAttributeManager_AttribHookFloat, "server.dll", "4C 8B DC 49 89 5B ? 49 89 6B ? 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 48 8B 3D", 0x0);
#endif

class IBaseInterface
{
public:
	virtual	~IBaseInterface() {}
};

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);

namespace SDK
{
	inline float AttribHookValue(float value, const char* name, void* econent, void* buffer = 0, bool isGlobalConstString = true)
	{
#if x86
		return reinterpret_cast<float(__cdecl*)(float, const char*, void*, void*, bool)>(S::CAttributeManager_AttribHookFloat())(value, name, econent, buffer, isGlobalConstString);
#else
		return S::CAttributeManager_AttribHookFloat.Call<float>(value, name, econent, buffer, isGlobalConstString);
#endif
	}
}