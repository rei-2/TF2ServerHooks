#include "BytePatches.h"

BytePatch::BytePatch(const char* sModule, const char* sSignature, int iOffset, const char* sPatch)
{
	m_sModule = sModule;
	m_sSignature = sSignature;
	m_iOffset = iOffset;

	auto vPatch = U::Memory.PatternToByte(sPatch);
	m_vPatch = vPatch;
	m_iSize = vPatch.size();
	m_vOriginal.resize(m_iSize);
}

void BytePatch::Write(std::vector<byte>& bytes)
{
	DWORD flNewProtect, flOldProtect;
	VirtualProtect(m_pAddress, m_iSize, PAGE_EXECUTE_READWRITE, &flNewProtect);
	memcpy(m_pAddress, bytes.data(), m_iSize);
	VirtualProtect(m_pAddress, m_iSize, flNewProtect, &flOldProtect);
}

void BytePatch::Initialize()
{
	if (m_bIsPatched)
		return;

	m_pAddress = LPVOID(U::Memory.FindSignature(m_sModule, m_sSignature));
	if (!m_pAddress)
	{
		OutputDebugStringA(std::format("BytePatch::Initialize() failed to initialize:\n  {}\n  {}\n", m_sModule, m_sSignature).c_str());
		return;
	}

	m_pAddress = LPVOID(uintptr_t(m_pAddress) + m_iOffset);

	DWORD flNewProtect, flOldProtect;
	VirtualProtect(m_pAddress, m_iSize, PAGE_EXECUTE_READWRITE, &flNewProtect);
	memcpy(m_vOriginal.data(), m_pAddress, m_iSize);
	VirtualProtect(m_pAddress, m_iSize, flNewProtect, &flOldProtect);

	Write(m_vPatch);
	m_bIsPatched = true;
}

void BytePatch::Unload()
{
	if (!m_bIsPatched)
		return;

	Write(m_vOriginal);
	m_bIsPatched = false;
}



void CBytePatches::Initialize()
{
#if x86
	m_vPatches = {};
#else
	m_vPatches = {
		//BytePatch("server.dll", "75 ? 44 38 A7 ? ? ? ? 75 ? 41 3B DD", 0x0, "EB") // speedhack
	};
#endif

	for (auto& patch : m_vPatches)
		patch.Initialize();
}

void CBytePatches::Unload()
{
	for (auto& patch : m_vPatches)
		patch.Unload();
}