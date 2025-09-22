#include "SDK.h"

#include <random>

#if x86
MAKE_SIGNATURE(ClientPrint, "server.dll", "55 8B EC 83 EC ? 56 8B 75 ? 85 F6 0F 84 ? ? ? ? 8D 4D", 0x0);
#else
MAKE_SIGNATURE(ClientPrint, "server.dll", "48 85 C9 0F 84 ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24", 0x0);
#endif

void SDK::Output(const char* cFunction, const char* cLog, Color_t tColor,
	int iTo, int iMessageBox,
	const char* sLeft, const char* sRight)
{
	static auto Msg = U::Memory.GetModuleExport<void(*)(const char* pMsgFormat, ...)>("tier0.dll", "Msg");
	if (cLog)
	{
		if (iTo & OUTPUT_CONSOLE)
			Msg("%s%s%s %s\n", sLeft, cFunction, sRight, cLog);
		if (iTo & OUTPUT_DEBUG)
			OutputDebugString(std::format("{}{}{} {}\n", sLeft, cFunction, sRight, cLog).c_str());
		if (iMessageBox != -1)
			MessageBox(nullptr, cLog, cFunction, iMessageBox);
	}
	else
	{
		if (iTo & OUTPUT_CONSOLE)
			Msg("%s\n", cFunction);
		if (iTo & OUTPUT_DEBUG)
			OutputDebugString(std::format("{}\n", cFunction).c_str());
		if (iMessageBox != -1)
			MessageBox(nullptr, "", cFunction, iMessageBox);
	}
}

void SDK::OutputClient(const char* cFunction, const char* cLog,
	CBasePlayer* pPlayer, int iMessageType,
	const char* sLeft, const char* sRight)
{
#if x86
	if (cLog)
		reinterpret_cast<void(__cdecl*)(CBasePlayer*, int, const char*, const char*, const char*, const char*, const char*)>(S::ClientPrint())
		(pPlayer, iMessageType, std::format("{}{}{} {}", sLeft, cFunction, sRight, cLog).c_str(), nullptr, nullptr, nullptr, nullptr);
	else
		reinterpret_cast<void(__cdecl*)(CBasePlayer*, int, const char*, const char*, const char*, const char*, const char*)>(S::ClientPrint())
		(pPlayer, iMessageType, std::format("{}", cFunction).c_str(), nullptr, nullptr, nullptr, nullptr);
#else
	if (cLog)
		S::ClientPrint.Call<void>(pPlayer, iMessageType, std::format("{}{}{} {}", sLeft, cFunction, sRight, cLog).c_str(), nullptr, nullptr, nullptr, nullptr);
	else
		S::ClientPrint.Call<void>(pPlayer, iMessageType, std::format("{}", cFunction).c_str(), nullptr, nullptr, nullptr, nullptr);
#endif
}

std::wstring SDK::ConvertUtf8ToWide(const std::string& source)
{
	int size = MultiByteToWideChar(CP_UTF8, 0, source.data(), -1, nullptr, 0);
	std::wstring result(size, 0);
	MultiByteToWideChar(CP_UTF8, 0, source.data(), -1, result.data(), size);
	return result;
}

std::string SDK::ConvertWideToUTF8(const std::wstring& source)
{
	int size = WideCharToMultiByte(CP_UTF8, 0, source.data(), -1, nullptr, 0, nullptr, nullptr);
	std::string result(size, 0);
	WideCharToMultiByte(CP_UTF8, 0, source.data(), -1, result.data(), size, nullptr, nullptr);
	return result;
}

double SDK::PlatFloatTime()
{
	static auto Plat_FloatTime = U::Memory.GetModuleExport<double(*)()>("tier0.dll", "Plat_FloatTime");
	return Plat_FloatTime();
}

int SDK::StdRandomInt(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(min, max);
	return distr(gen);
}

float SDK::StdRandomFloat(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distr(min, max);
	return distr(gen);
}

int SDK::SeedFileLineHash(int seedvalue, const char* sharedname, int additionalSeed)
{
	CRC32_t retval;

	CRC32_Init(&retval);

	CRC32_ProcessBuffer(&retval, &seedvalue, sizeof(int));
	CRC32_ProcessBuffer(&retval, &additionalSeed, sizeof(int));
	CRC32_ProcessBuffer(&retval, sharedname, int(strlen(sharedname)));

	CRC32_Final(&retval);

	return static_cast<int>(retval);
}

int SDK::SharedRandomInt(unsigned iseed, const char* sharedname, int iMinVal, int iMaxVal, int additionalSeed)
{
	const int seed = SeedFileLineHash(iseed, sharedname, additionalSeed);
	I::UniformRandomStream->SetSeed(seed);
	return I::UniformRandomStream->RandomInt(iMinVal, iMaxVal);
}

void SDK::RandomSeed(int iSeed)
{
	static auto RandomSeed = reinterpret_cast<void(*)(uint32_t)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed"));
	RandomSeed(iSeed);
}

int SDK::RandomInt(int iMinVal, int iMaxVal)
{
	static auto RandomInt = reinterpret_cast<int(*)(int, int)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomInt"));
	return RandomInt(iMinVal, iMaxVal);
}

float SDK::RandomFloat(float flMinVal, float flMaxVal)
{
	static auto RandomFloat = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));
	return RandomFloat(flMinVal, flMaxVal);
}

int SDK::HandleToIDX(unsigned int pHandle)
{
	return pHandle & 0xFFF;
}

void SDK::Trace(const Vec3& vecStart, const Vec3& vecEnd, unsigned int nMask, ITraceFilter* pFilter, CGameTrace* pTrace)
{
	Ray_t ray;
	ray.Init(vecStart, vecEnd);
	I::EngineTrace->TraceRay(ray, nMask, pFilter, pTrace);

#ifdef DEBUG_TRACES
	if (Vars::Debug::VisualizeTraces.Value)
		G::LineStorage.push_back({ { vecStart, Vars::Debug::VisualizeTraceHits.Value ? pTrace->endpos : vecEnd }, I::GlobalVars->curtime + 0.015f, {}, bool(GetAsyncKeyState(VK_MENU) & 0x8000) });
#endif
}

void SDK::TraceHull(const Vec3& vecStart, const Vec3& vecEnd, const Vec3& vecHullMin, const Vec3& vecHullMax, unsigned int nMask, ITraceFilter* pFilter, CGameTrace* pTrace)
{
	Ray_t ray;
	ray.Init(vecStart, vecEnd, vecHullMin, vecHullMax);
	I::EngineTrace->TraceRay(ray, nMask, pFilter, pTrace);

#ifdef DEBUG_TRACES
	if (Vars::Debug::VisualizeTraces.Value)
	{
		G::LineStorage.push_back({ { vecStart, Vars::Debug::VisualizeTraceHits.Value ? pTrace->endpos : vecEnd }, I::GlobalVars->curtime + 0.015f, {}, bool(GetAsyncKeyState(VK_MENU) & 0x8000) });
		if (!(vecHullMax - vecHullMin).IsZero())
		{
			G::BoxStorage.push_back({ vecStart, vecHullMin, vecHullMax, {}, I::GlobalVars->curtime + 0.015f, {}, { 0, 0, 0, 0 }, bool(GetAsyncKeyState(VK_MENU) & 0x8000) });
			G::BoxStorage.push_back({ Vars::Debug::VisualizeTraceHits.Value ? pTrace->endpos : vecEnd, vecHullMin, vecHullMax, {}, I::GlobalVars->curtime + 0.015f, {}, { 0, 0, 0, 0 }, bool(GetAsyncKeyState(VK_MENU) & 0x8000) });
		}
	}
#endif
}

bool SDK::VisPos(CBaseEntity* pSkip, const CBaseEntity* pEntity, const Vec3& from, const Vec3& to, unsigned int nMask)
{
	CGameTrace trace = {};
	CTraceFilterHitscan filter = {}; filter.pSkip = pSkip;
	Trace(from, to, nMask, &filter, &trace);
	if (trace.DidHit())
		return trace.m_pEnt && trace.m_pEnt == pEntity;
	return true;
}
bool SDK::VisPosProjectile(CBaseEntity* pSkip, const CBaseEntity* pEntity, const Vec3& from, const Vec3& to, unsigned int nMask)
{
	CGameTrace trace = {};
	CTraceFilterProjectile filter = {}; filter.pSkip = pSkip;
	Trace(from, to, nMask, &filter, &trace);
	if (trace.DidHit())
		return trace.m_pEnt && trace.m_pEnt == pEntity;
	return true;
}
bool SDK::VisPosWorld(CBaseEntity* pSkip, const CBaseEntity* pEntity, const Vec3& from, const Vec3& to, unsigned int nMask)
{
	CGameTrace trace = {};
	CTraceFilterWorldAndPropsOnly filter = {}; filter.pSkip = pSkip;
	Trace(from, to, nMask, &filter, &trace);
	if (trace.DidHit())
		return trace.m_pEnt && trace.m_pEnt == pEntity;
	return true;
}