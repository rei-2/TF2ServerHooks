#pragma once
#include "../Feature/Feature.h"
#include <Windows.h>
#include <cstdint>
#include <vector>

class CMemory
{
public:
	std::vector<byte> PatternToByte(const char* szPattern);
	std::vector<int> PatternToInt(const char* szPattern);
	uintptr_t FindSignature(const char* szModule, const char* szPattern);
	PVOID FindInterface(const char* szModule, const char* szObject);


	inline void* GetVFunc(void* instance, size_t index)
	{
		const auto vtable = *static_cast<void***>(instance);
		return vtable[index];
	}

	inline uintptr_t RelToAbs(const uintptr_t address)
	{
#if x86
		return *reinterpret_cast<std::uint32_t*>(address + 0x1) + address + 0x5;
#else
		return *reinterpret_cast<std::uint32_t*>(address + 0x3) + address + 0x7;
#endif
	}

	template <typename T>
	inline T GetModuleExport(const char* szModule, const char* szExport)
	{
		if (auto hModule = GetModuleHandle(szModule))
			return reinterpret_cast<T>(GetProcAddress(hModule, szExport));
		return reinterpret_cast<T>(nullptr);
	}
};

ADD_FEATURE_CUSTOM(CMemory, Memory, U)