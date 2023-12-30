#define EXILE_PRIVATE
#include <exile/ll/ini/iniInstruction.hpp>


exile::ll::IniInstruction::IniInstruction(const exile::ll::Tokenized& sourceToken, IniInstructionId id, const exile::Vector<exile::String>& args)
	:sourceToken(sourceToken), id(id), arguments(args)
{

}

exile::ll::IniInstruction::IniInstruction()
{

}

const exile::ll::IniInstructionId exile::ll::IniInstruction::GetId() const
{
	return id;
}

const exile::Vector<exile::String>& exile::ll::IniInstruction::GetArguments() const
{
	return arguments;
}

const exile::ll::Tokenized& exile::ll::IniInstruction::GetSourceToken() const
{
	return sourceToken;
}