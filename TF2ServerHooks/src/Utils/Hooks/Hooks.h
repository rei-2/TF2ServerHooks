#pragma once
#include "../Feature/Feature.h"
#include <MinHook/MinHook.h>
#include <unordered_map>
#include <string>

class CHook
{
public:
	void* m_pOriginal = nullptr;
	void* m_pInitFunc = nullptr;

public:
	CHook(std::string sName, void* pInitFunc);

	inline void Create(void* pSrc, void* pDst)
	{
		MH_CreateHook(pSrc, pDst, &m_pOriginal);
	}

	template <typename T>
	inline T As() const
	{
		return reinterpret_cast<T>(m_pOriginal);
	}

	template <typename T, typename... Args>
	inline T Call(Args... args) const
	{
		return reinterpret_cast<T(__fastcall*)(Args...)>(m_pOriginal)(args...);
	}
};

#if x86
#define MAKE_HOOK(name, address, type, convention, ...) namespace Hooks \
{\
	namespace name\
	{\
		void Init(); \
		inline CHook Hook(#name, Init); \
		using FN = type(convention*)(__VA_ARGS__); \
		type convention Func(__VA_ARGS__); \
	}\
} \
void Hooks::name::Init() { Hook.Create(reinterpret_cast<void*>(address), Func); } \
type convention Hooks::name::Func(__VA_ARGS__)
#else
#define MAKE_HOOK(name, address, type, ...) namespace Hooks \
{\
	namespace name\
	{\
		void Init(); \
		inline CHook Hook(#name, Init); \
		using FN = type(__fastcall*)(__VA_ARGS__); \
		type __fastcall Func(__VA_ARGS__); \
	}\
} \
void Hooks::name::Init() { Hook.Create(reinterpret_cast<void*>(address), Func); } \
type __fastcall Hooks::name::Func(__VA_ARGS__)
#endif

class CHooks
{
public:
	std::unordered_map<std::string, CHook*> m_mHooks = {};

public:
	void Initialize();
	void Unload();
};

ADD_FEATURE_CUSTOM(CHooks, Hooks, U);

#define CALL_ORIGINAL Hook.As<FN>()