#include "Core.h"

#include "../SDK/SDK.h"
#include "../BytePatches/BytePatches.h"
#include "../Features/Commands/Commands.h"
#include "../SDK/Events/Events.h"

void CCore::Load()
{
	//while (!U::Memory.FindSignature("client.dll", "48 8B 0D ? ? ? ? 48 8B 10 48 8B 19 48 8B C8 FF 92"))
	//	Sleep(500);
	//Sleep(500);

	U::Signatures.Initialize();
	U::Interfaces.Initialize();
	F::Commands.Initialize();
	U::Hooks.Initialize();
	U::BytePatches.Initialize();
	U::ConVars.Initialize();
	H::Events.Initialize();

	SDK::Output("TF2ServerHooks", "Loaded", { 175, 150, 255, 255 }, true, true);
}

void CCore::Loop()
{
	while (!bUnload)
		Sleep(15);
}

void CCore::Unload()
{
	if (bEarly)
	{
		SDK::Output("TF2ServerHooks", "Cancelled", { 175, 150, 255, 255 }, true, true);
		return;
	}

	G::Unload = true;
	U::Hooks.Unload();
	U::BytePatches.Unload();
	U::ConVars.Unload();
	H::Events.Unload();

	Sleep(250);

	SDK::Output("TF2ServerHooks", "Unloaded", { 175, 150, 255, 255 }, true, true);
}