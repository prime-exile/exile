#define EXILE_PRIVATE

#include<exile/core/cme/commandExecutionEngine.hpp>
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

u8 exile::cme::CommandExecutionEngine::RegisterCommand(const exile::String& name, exile::cme::ICommand* command)
{
	EX_s1AssertFR(ContaintsKey(commands, name), {}, EX_ERROR, "failed to register command %s, command with this name already exists", name.c_str());
	
	commands[name] = command;
	return EX_SUCCESS;
}

void exile::cme::CommandExecutionEngine::UnregisterCommand(const exile::String& name)
{
	commands.erase(name);
}

u8 exile::cme::CommandExecutionEngine::CommandExists(const exile::String& name)
{
	return ContaintsKey(commands, name);
}

u8 exile::cme::CommandExecutionEngine::Execute(const exile::String& command)
{
	exile::Vector<exile::String> splittedCommand;
	SplitString(command, splittedCommand, ' ');

	EX_s1AssertFR((splittedCommand.size() < 1), {}, EX_ERROR, "failed to execute command: %s - command are empty!", command.c_str());

	const exile::String& commandName = splittedCommand[0];
	exile::Vector<exile::String> args(splittedCommand.begin() + 1, splittedCommand.end());

	return Execute(commandName, args);
}

u8 exile::cme::CommandExecutionEngine::Execute(const exile::String& commandName, const exile::Vector<exile::String> args)
{
	EX_s1AssertFR(!ContaintsKey(commands, commandName), {}, EX_ERROR, "failed to execute command %s", commandName.c_str());

	exile::cme::ICommand* targetCommand = commands[commandName];
	return targetCommand->Execute(args);
}