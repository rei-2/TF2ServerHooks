#include "Commands.h"

#include "../../Core/Core.h"
#include <utility>
#include <boost/algorithm/string/replace.hpp>

bool CCommands::Run(const char* sCmd, std::deque<const char*>& vArgs)
{
	std::string sLower = sCmd;
	std::transform(sLower.begin(), sLower.end(), sLower.begin(), ::tolower);

	auto uHash = FNV1A::Hash32(sLower.c_str());
	if (!m_mCommands.contains(uHash))
		return false;

	m_mCommands[uHash](vArgs);
	return true;
}

void CCommands::Register(const char* sName, CommandCallback fCallback)
{
	m_mCommands[FNV1A::Hash32(sName)] = std::move(fCallback);
}

void CCommands::Initialize()
{
	Register("setcvar", [](const std::deque<const char*>& vArgs)
		{
			if (vArgs.size() < 2)
			{
				SDK::Output("Usage:\n\tsetcvar <cvar> <value>");
				return;
			}

			const char* sCVar = vArgs[0];
			auto pCVar = I::CVar->FindVar(sCVar);
			if (!pCVar)
			{
				SDK::Output(std::format("Could not find {}", sCVar).c_str());
				return;
			}

			std::string sValue = "";
			for (int i = 1; i < vArgs.size(); i++)
				sValue += std::format("{} ", vArgs[i]);
			sValue.pop_back();
			boost::replace_all(sValue, "\"", "");

			pCVar->SetValue(sValue.c_str());
			SDK::Output(std::format("Set {} to {}", sCVar, sValue).c_str());
		});

	Register("getcvar", [](const std::deque<const char*>& vArgs)
		{
			if (vArgs.size() != 1)
			{
				SDK::Output("Usage:\n\tgetcvar <cvar>");
				return;
			}

			const char* sCVar = vArgs[0];
			auto pCVar = I::CVar->FindVar(sCVar);
			if (!pCVar)
			{
				SDK::Output(std::format("Could not find {}", sCVar).c_str());
				return;
			}

			SDK::Output(std::format("Value of {} is {}", sCVar, pCVar->GetString()).c_str());
		});

	Register("platfloattime", [](const std::deque<const char*>& args)
		{
			if (args.size() != 1)
			{
				SDK::Output("Usage:\n\tplatfloattime <double>");
				return;
			}

			try
			{
				G::PlatFloatTimeAdd = std::stod(args[0]);
				SDK::Output(std::format("Set G::PlatFloatTimeAdd to {}", G::PlatFloatTimeAdd).c_str());
			}
			catch (...) 
			{
				SDK::Output("Failed to set G::PlatFloatTimeAdd");
			}
		});

	Register("debugvisuals", [](const std::deque<const char*>& args)
		{
			G::DebugVisuals = !G::DebugVisuals;
			SDK::Output(std::format("Set G::DebugVisuals to {}", G::DebugVisuals).c_str());
		});

	Register("debuginfo", [](const std::deque<const char*>& args)
		{
			G::DebugInfo = !G::DebugInfo;
			SDK::Output(std::format("Set G::DebugInfo to {}", G::DebugInfo).c_str());
		});

	Register("tickinfo", [](const std::deque<const char*>& args)
		{
			G::TickInfo = !G::TickInfo;
			SDK::Output(std::format("Set G::TickInfo to {}", G::TickInfo).c_str());
		});

	Register("critinfo", [](const std::deque<const char*>& args)
		{
			G::CritInfo = !G::CritInfo;
			SDK::Output(std::format("Set G::CritInfo to {}", G::CritInfo).c_str());
		});

	Register("serverhitboxes", [](const std::deque<const char*>& args)
		{
			G::ServerHitboxes = !G::ServerHitboxes;
			SDK::Output(std::format("Set G::ServerHitboxes to {}", G::ServerHitboxes).c_str());
		});

	Register("serverhitboxesrate", [](const std::deque<const char*>& args)
		{
			if (args.size() != 1)
			{
				SDK::Output("Usage:\n\tserverhitboxesrate <int>");
				return;
			}

			try
			{
				G::ServerHitboxesRate = std::stoi(args[0]);
				SDK::Output(std::format("Set G::ServerHitboxesRate to {}", G::ServerHitboxesRate).c_str());
			}
			catch (...)
			{
				SDK::Output("Failed to set G::ServerHitboxesRate");
			}
		});

	Register("drawhitboxes", [](const std::deque<const char*>& args)
		{
			G::DrawHitboxes = !G::DrawHitboxes;
			SDK::Output(std::format("Set G::DrawHitboxes to {}", G::DrawHitboxes).c_str());
		});

	Register("drawboundingbox", [](const std::deque<const char*>& args)
		{
			G::DrawBoundingBox = !G::DrawBoundingBox;
			SDK::Output(std::format("Set G::DrawBoundingBox to {}", G::DrawBoundingBox).c_str());
		});

	Register("drawheadonly", [](const std::deque<const char*>& args)
		{
			G::DrawHeadOnly = !G::DrawHeadOnly;
			SDK::Output(std::format("Set G::DrawHeadOnly to {}", G::DrawHeadOnly).c_str());
		});

	Register("drawduration", [](const std::deque<const char*>& args)
		{
			if (args.size() != 1)
			{
				SDK::Output("Usage:\n\tdrawduration <float> (0 to disable override)");
				return;
			}

			try
			{
				G::DrawDuration = std::stof(args[0]);
				SDK::Output(std::format("Set G::DrawDuration to {}", G::DrawDuration).c_str());
			}
			catch (...)
			{
				SDK::Output("Failed to set G::DrawDuration");
			}
		});

	Register("unload", [](const std::deque<const char*>& args)
		{
			U::Core.m_bUnload = true;
		});
}