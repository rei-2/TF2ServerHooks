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

		SDK::Output("Core", "U::Signatures.Initialize();", {}, false, true);
	U::Signatures.Initialize();
		SDK::Output("Core", "U::Interfaces.Initialize();", {}, false, true);
	U::Interfaces.Initialize();
		SDK::Output("Core", "F::Commands.Initialize();", {}, false, true);
	F::Commands.Initialize();
		SDK::Output("Core", "U::Hooks.Initialize();", {}, false, true);
	U::Hooks.Initialize();
		SDK::Output("Core", "U::BytePatches.Initialize();", {}, false, true);
	U::BytePatches.Initialize();
		SDK::Output("Core", "H::Events.Initialize();", {}, false, true);
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
		SDK::Output("Core", "U::Hooks.Unload();", {}, false, true);
	U::Hooks.Unload();
		SDK::Output("Core", "U::BytePatches.Unload();", {}, false, true);
	U::BytePatches.Unload();
		SDK::Output("Core", "H::Events.Unload();", {}, false, true);
	H::Events.Unload();

	Sleep(250);

	SDK::Output("TF2ServerHooks", "Unloaded", { 175, 150, 255, 255 }, true, true);
}