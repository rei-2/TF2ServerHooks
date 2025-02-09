#include "Commands.h"

#include "../../Core/Core.h"
#include <utility>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/join.hpp>

bool CCommands::Run(const std::string& cmd, std::deque<std::string>& args)
{
	auto uHash = FNV1A::Hash32(cmd.c_str());
	if (!CommandMap.contains(uHash))
		return false;

	CommandMap[uHash](args);
	return true;
}

void CCommands::Register(const std::string& name, CommandCallback callback)
{
	CommandMap[FNV1A::Hash32(name.c_str())] = std::move(callback);
}

void CCommands::Initialize()
{
	Register("setcvar", [](const std::deque<std::string>& args)
		{
			if (args.size() < 2)
			{
				SDK::Output("Usage:\n\tsetcvar <cvar> <value>");
				return;
			}

			const auto foundCVar = I::CVar->FindVar(args[0].c_str());
			const std::string cvarName = args[0];
			if (!foundCVar)
			{
				SDK::Output(std::format("Could not find {}", cvarName).c_str());
				return;
			}

			auto vArgs = args; vArgs.pop_front();
			std::string newValue = boost::algorithm::join(vArgs, " ");
			boost::replace_all(newValue, "\"", "");
			foundCVar->SetValue(newValue.c_str());
			SDK::Output(std::format("Set {} to {}", cvarName, newValue).c_str());
		});

	Register("getcvar", [](const std::deque<std::string>& args)
		{
			if (args.size() != 1)
			{
				SDK::Output("Usage:\n\tgetcvar <cvar>");
				return;
			}

			const auto foundCVar = I::CVar->FindVar(args[0].c_str());
			const std::string cvarName = args[0];
			if (!foundCVar)
			{
				SDK::Output(std::format("Could not find {}", cvarName).c_str());
				return;
			}

			SDK::Output(std::format("Value of {} is {}", cvarName, foundCVar->GetString()).c_str());
		});

	Register("platfloattime", [](const std::deque<std::string>& args)
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

	Register("debugvisuals", [](const std::deque<std::string>& args)
		{
			G::DebugVisuals = !G::DebugVisuals;
			SDK::Output(std::format("Set G::DebugVisuals to {}", G::DebugVisuals).c_str());
		});

	Register("serverhitboxes", [](const std::deque<std::string>& args)
		{
			G::ServerHitboxes = !G::ServerHitboxes;
			SDK::Output(std::format("Set G::ServerHitboxes to {}", G::ServerHitboxes).c_str());
		});

	Register("serverhitboxesrate", [](const std::deque<std::string>& args)
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

	Register("unload", [](const std::deque<std::string>& args)
		{
			U::Core.bUnload = true;
		});
}