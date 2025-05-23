#include "Hooks.h"

#include "../Assert/Assert.h"

CHook::CHook(std::string sName, void* pInitFunc)
{
	this->m_pInitFunc = pInitFunc;
	U::Hooks.m_mHooks[sName] = this;
}

void CHooks::Initialize()
{
	MH_Initialize();

	for (auto& [_, pHook] : m_mHooks)
		reinterpret_cast<void(__cdecl*)()>(pHook->m_pInitFunc)();

	AssertCustom(MH_EnableHook(MH_ALL_HOOKS) == MH_OK, "MH failed to enable all hooks!");
}

void CHooks::Unload()
{
	AssertCustom(MH_Uninitialize() == MH_OK, "MH failed to unload all hooks!");
}