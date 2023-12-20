#ifndef _EXILE_LL_INI_INSTRUCTION_HPP_
#define _EXILE_LL_INI_INSTRUCTION_HPP_

#include <exile/core/API.h>
#include <exile/core/containers/vector.hpp>
#include <exile/ll/lexer.hpp>
#include <exile/core/containers/string.hpp>

namespace exile
{
	namespace ll
	{
		enum class IniInstructionId
		{
			ds, // delare section
			mov, // set variable value
			movv // set copy variable value
		};

		class IniInstruction
		{

			IniInstructionId id;
			exile::Vector<exile::String> arguments;
			exile::ll::Tokenized sourceToken;

		public:
			IniInstruction(const exile::ll::Tokenized& sourceToken, IniInstructionId id, const exile::Vector<exile::String>& args);

			IniInstruction();

			const IniInstructionId GetId() const;
			const exile::Vector<exile::String>& GetArguments() const;
			const exile::ll::Tokenized& GetSourceToken()const;

		};
	}
}

#endif