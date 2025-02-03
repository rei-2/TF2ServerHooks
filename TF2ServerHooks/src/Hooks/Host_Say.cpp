#include "../SDK/SDK.h"

MAKE_SIGNATURE(Host_Say, "server.dll", "44 88 44 24 ? 48 89 4C 24", 0x0);

MAKE_HOOK(Host_Say, S::Host_Say(), void,
	edict_t* pEdict, const CCommand& args, bool teamonly)
{
	if (args.ArgC())
	{
		SDK::Output("Host_Say", std::format("{}, {}", args.ArgS(), args.ArgC()).c_str(), {}, true, true);
	}
	return CALL_ORIGINAL(pEdict, args, teamonly);
}

MAKE_SIGNATURE(CheckChatText, "server.dll", "48 89 54 24 ? 48 89 4C 24 ? 41 54 41 55", 0x0);

MAKE_HOOK(CheckChatText, S::CheckChatText(), char*,
	CBasePlayer* pPlayer, char* text)
{
	SDK::Output("CheckChatText 1", text, {}, true, true);
	auto pReturn = CALL_ORIGINAL(pPlayer, text);
	SDK::Output("CheckChatText 2", pReturn, {}, true, true);
	return pReturn;
}

MAKE_SIGNATURE(UTIL_LogPrintf, "server.dll", "48 8B C4 48 89 48 ? 48 89 50", 0x0);

MAKE_HOOK(UTIL_LogPrintf, S::UTIL_LogPrintf(), void,
	const char* fmt, ...)
{
	va_list marker;
	char buffer[4096];
	va_start(marker, fmt);
	vsnprintf_s(buffer, sizeof(buffer), fmt, marker);
	va_end(marker);

	if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n')
		buffer[strlen(buffer) - 1] = 0;
	char* msg = buffer;
	if (!msg || !msg[0])
		return;

	SDK::Output("UTIL_LogPrintf", msg, {}, true, true);

	CALL_ORIGINAL("%s", msg);
}