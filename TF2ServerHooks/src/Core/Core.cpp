#include "Core.h"

#include "../SDK/SDK.h"
#include "../BytePatches/BytePatches.h"
#include "../Features/Commands/Commands.h"
#include "../SDK/Events/Events.h"
#include <Psapi.h>
#include <filesystem>

static inline std::string GetProcessName(DWORD dwProcessID)
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessID);
	if (!hProcess)
		return "";

	char buffer[MAX_PATH];
	if (!GetModuleBaseName(hProcess, nullptr, buffer, sizeof(buffer) / sizeof(char)))
	{
		CloseHandle(hProcess);
		return "";
	}

	CloseHandle(hProcess);
	return buffer;
}

void CCore::AppendFailText(const char* sMessage)
{
	m_ssFailStream << std::format("{}\n", sMessage);
	OutputDebugStringA(std::format("{}\n", sMessage).c_str());
}

void CCore::LogFailText()
{
	m_ssFailStream << "\nBuilt @ " __DATE__ ", " __TIME__ ", " __CONFIGURATION__ "\n";
	m_ssFailStream << "Ctrl + C to copy. \n";
	try
	{
		std::ofstream file;
		file.open(std::filesystem::current_path().string() + "\\fail_log.txt", std::ios_base::app);
		file << m_ssFailStream.str() + "\n\n\n";
		file.close();
		m_ssFailStream << "Logged to fail_log.txt. ";
	}
	catch (...) {}

	SDK::Output("Failed to load", m_ssFailStream.str().c_str(), {}, OUTPUT_DEBUG, MB_OK | MB_ICONERROR);
}

void CCore::Load()
{
#if x86
	if (m_bUnload = m_bFailed = FNV1A::Hash32(GetProcessName(GetCurrentProcessId()).c_str()) != FNV1A::Hash32Const("srcds.exe"))
#else
	if (m_bUnload = m_bFailed = FNV1A::Hash32(GetProcessName(GetCurrentProcessId()).c_str()) != FNV1A::Hash32Const("srcds_win64.exe"))
#endif
	{
		AppendFailText("Invalid process");
		return;
	}

	if (m_bUnload = m_bFailed = !U::Signatures.Initialize() || !U::Interfaces.Initialize())
		return;
	if (m_bUnload = m_bFailed2 = !U::Hooks.Initialize() || !U::BytePatches.Initialize() || !H::Events.Initialize())
		return;
	F::Commands.Initialize();

	SDK::Output("TF2ServerHooks", "Loaded", { 175, 150, 255 }, OUTPUT_CONSOLE | OUTPUT_DEBUG);
}

void CCore::Loop()
{
	while (!m_bUnload)
		Sleep(15);
}

void CCore::Unload()
{
	if (m_bFailed)
	{
		LogFailText();
		return;
	}

	G::Unload = true;
	m_bFailed2 = !U::Hooks.Unload() || m_bFailed2;
	U::BytePatches.Unload();
	H::Events.Unload();

	Sleep(250);
	U::ConVars.Restore();

	if (m_bFailed2)
	{
		LogFailText();
		return;
	}

	SDK::Output("TF2ServerHooks", "Unloaded", { 175, 150, 255 }, OUTPUT_CONSOLE | OUTPUT_DEBUG);
}