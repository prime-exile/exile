#ifndef _EXILE_INI_INTERPRETATOR_HPP_
#define _EXILE_INI_INTERPRETATOR_HPP_

#include <exile/ll/ini/iniInstruction.hpp>

namespace exile
{
	namespace ll
	{

		class EX_API IniInterpretatorSection
		{
			exile::UnorderedMap<exile::String, exile::String> storage;
		public:
			IniInterpretatorSection();

				
			void Add(const exile::String& name, const exile::String value);
			void Mov(const exile::String& name, const exile::String value);
		
			const exile::String& GetValue(const exile::String& name) const;
			const bool Containts(const exile::String& variableName) const;

			void Clear();
		};

		class EX_API IniInterpretator
		{

			exile::UnorderedMap<exile::String, exile::ll::IniInterpretatorSection> sections;
			exile::ll::IniInterpretatorSection currentSection;

			exile::String currentSectionName;
		public:
			IniInterpretator();

			u8 Interpretate(const exile::ll::IniInstruction& instruction);

			void AddSection(const exile::String& name,const exile::ll::IniInterpretatorSection& newSection);
			const exile::ll::IniInterpretatorSection& GetSection(const exile::String& name) const;

			void Complete();
			~IniInterpretator();
		};
	}
}

#endif
