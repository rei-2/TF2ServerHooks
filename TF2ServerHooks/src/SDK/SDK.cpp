#include "SDK.h"

#include <random>

MAKE_SIGNATURE(ClientPrint, "server.dll", "48 85 C9 0F 84 ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24", 0x0);

void SDK::Output(const char* cFunction, const char* cLog, Color_t cColor, bool bConsole, /*bool bChat,*/ bool bDebug, int bMessageBox)
{
	static auto Msg = U::Memory.GetModuleExport<void(*)(const char* pMsgFormat, ...)>("tier0.dll", "Msg");
	if (cLog)
	{
		if (bConsole)
			Msg("[%s] %s\n", cFunction, cLog);
		//if (bChat)
		//	I::ClientModeShared->m_pChatElement->ChatPrintf(0, std::format("{}[{}]\x1 {}", cColor.ToHex(), cFunction, cLog).c_str());
		if (bDebug)
			OutputDebugString(std::format("[{}] {}\n", cFunction, cLog).c_str());
		if (bMessageBox != -1)
			MessageBox(nullptr, cLog, cFunction, bMessageBox);
	}
	else
	{
		if (bConsole)
			Msg("%s\n", cFunction);
		//if (bChat)
		//	I::ClientModeShared->m_pChatElement->ChatPrintf(0, std::format("{}{}\x1", cColor.ToHex(), cFunction).c_str());
		if (bDebug)
			OutputDebugString(std::format("{}\n", cFunction).c_str());
		if (bMessageBox != -1)
			MessageBox(nullptr, "", cFunction, bMessageBox);
	}
}

void SDK::OutputClient(const char* cFunction, const char* cLog, CBasePlayer* pPlayer, int iMessageType)
{
	if (cLog)
		S::ClientPrint.Call<void>(pPlayer, iMessageType, std::format("[{}] {}", cFunction, cLog).c_str(), nullptr, nullptr, nullptr, nullptr);
	else
		S::ClientPrint.Call<void>(pPlayer, iMessageType, std::format("{}", cFunction).c_str(), nullptr, nullptr, nullptr, nullptr);
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
	static auto fnPlatFloatTime = U::Memory.GetModuleExport<double(*)()>("tier0.dll", "Plat_FloatTime");
	return fnPlatFloatTime();
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
	static auto fnRandomSeed = reinterpret_cast<void(*)(uint32_t)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomSeed"));
	fnRandomSeed(iSeed);
}

int SDK::RandomInt(int iMinVal, int iMaxVal)
{
	static auto fnRandomInt = reinterpret_cast<int(*)(int, int)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomInt"));
	return fnRandomInt(iMinVal, iMaxVal);
}

float SDK::RandomFloat(float flMinVal, float flMaxVal)
{
	static auto fnRandomFloat = reinterpret_cast<float(*)(float, float)>(GetProcAddress(GetModuleHandleA("vstdlib.dll"), "RandomFloat"));
	return fnRandomFloat(flMinVal, flMaxVal);
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