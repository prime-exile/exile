#define EXILE_PRIVATE

#include <exile/core/cme/commandExecutionEngine.hpp>
#include <exile/core/hash.hpp>
#include <exile/core/containers/sstream.hpp>

#define ContaintsKey(map, k)(map.find(k) != map.end())

static __forceinline void SplitString(const exile::String& str, exile::Vector<exile::String>& splitted, char s)
{
	exile::Stringstream ss(str);
	exile::String tmp;
	for (char i; ss >> i; )
	{
		tmp += i;
		if (ss.peek() == s)
		{
			ss.ignore();
			splitted.push_back(tmp);
			tmp.clear();
		}
	}

	if (!tmp.empty())
	{
		splitted.push_back(tmp);
	}
}

i64 exile::cme::CommandExecutionEngine::RegisterCommand(const exile::String& name, exile::cme::ICommand* command)
{
	u32 nameHash = exile::hash::fnv1a32(name.c_str());
	exAssertFR(ContaintsKey(commands, nameHash), {}, -1, "failed to register command %s, command with this name already exists", name.c_str());
	
	commands[nameHash] = command;
	return nameHash;
}

void exile::cme::CommandExecutionEngine::UnregisterCommand(u32 hash)
{
	commands.erase(hash);
}

void exile::cme::CommandExecutionEngine::UnregisterCommand(const exile::String& name)
{
	u32 nameHash = exile::hash::fnv1a32(name.c_str());
	commands.erase(nameHash);
}

u8 exile::cme::CommandExecutionEngine::CommandExists(const exile::String& name)
{
	u32 nameHash = exile::hash::fnv1a32(name.c_str());
	return ContaintsKey(commands, nameHash);
}

u8 exile::cme::CommandExecutionEngine::Execute(u32 hash, const exile::Vector<exile::String> args)
{
	if (!ContaintsKey(commands, hash)) return EX_ERROR;
	exile::cme::ICommand* targetCommand = commands[hash];
	return targetCommand->Execute(args);
}

u8 exile::cme::CommandExecutionEngine::Execute(const exile::String& command)
{
	exile::Vector<exile::String> splittedCommand;
	SplitString(command, splittedCommand, ' ');

	exAssertFR((splittedCommand.size() < 1), {}, EX_ERROR, "failed to execute command: %s - command are empty!", command.c_str());

	const exile::String& commandName = splittedCommand[0];
	exile::Vector<exile::String> args(splittedCommand.begin() + 1, splittedCommand.end());

	u32 hash = exile::hash::fnv1a32(commandName.c_str());
	exAssertFR(!ContaintsKey(commands, hash), {}, EX_ERROR, "failed to execute command %s", commandName.c_str());
	
	return Execute(commandName, args);
}

u8 exile::cme::CommandExecutionEngine::Execute(const exile::String& commandName, const exile::Vector<exile::String> args)
{
	u32 hash = exile::hash::fnv1a32(commandName.c_str());
	exAssertFR(!ContaintsKey(commands, hash), {}, EX_ERROR, "failed to execute command %s", commandName.c_str());
	exile::cme::ICommand* targetCommand = commands[hash];
	return targetCommand->Execute(args);
}