#define EXILE_PRIVATE
#include <exile/ll/ini/iniInterpretator.hpp>
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

void exile::ll::IniInterpretator::AddSection(const exile::String& name, const exile::ll::IniInterpretatorSection& newSection)
{
	sections[name] = newSection;
}

const exile::ll::IniInterpretatorSection& exile::ll::IniInterpretator::GetSection(const exile::String& name) const
{
	return sections.at(name);
}

const u8 exile::ll::IniInterpretator::Containts(const exile::String& name) const
{
	return ContaintsKey(sections, name);
}

void exile::ll::IniInterpretator::Complete()
{
	sections.insert(exile::UnorderedMapPair<exile::String, exile::ll::IniInterpretatorSection>(currentSectionName, currentSection));
}

u8 exile::ll::IniInterpretator::Interpretate(const exile::ll::IniInstruction& instruction)
{

	switch (instruction.GetId())
	{
	case exile::ll::IniInstructionId::ds:
		sections.insert(exile::UnorderedMapPair<exile::String, exile::ll::IniInterpretatorSection>(currentSectionName, currentSection));
		currentSectionName = instruction.GetArguments()[0];
		break;
	case exile::ll::IniInstructionId::mov:
		currentSection.Mov(instruction.GetArguments()[0], instruction.GetArguments()[1]);
		break;
	case exile::ll::IniInstructionId::movv:
	{
		exile::Vector<exile::String> variableFullName;
		SplitString(instruction.GetArguments()[1], variableFullName, '.');
		if (currentSectionName == variableFullName[0])
		{
			if (currentSection.Containts(variableFullName[1]))
			{
				currentSection.Mov(instruction.GetArguments()[0], currentSection.GetValue(variableFullName[1]));
			}
			else
			{
				exAssertFR(!ContaintsKey(sections, currentSectionName), {}, EX_ERROR, "ini section not found: %s", currentSectionName)
				const exile::ll::IniInterpretatorSection& sec = sections.at(currentSectionName);
				currentSection.Mov(instruction.GetArguments()[0], sec.GetValue(variableFullName[1]));
			}
		}
		else
		{
			exile::String name = variableFullName[0];

			exAssertFR(!ContaintsKey(sections, name), {}, EX_ERROR, "ini section not found: %s", name)

			if (ContaintsKey(sections, name))
			{
				const exile::ll::IniInterpretatorSection& sec = sections.at(name);
				currentSection.Mov(instruction.GetArguments()[0], sec.GetValue(variableFullName[1]));
			}
		}
		//currentSection.insert(exile::UnorderedMapPair<exile::String, exile::String>(instruction.GetArguments()[0], sections[variableFullName[0]][variableFullName[1]]));

		//Bsections[currentSectionName] = currentSection;
		break;
	}
	}

	return EX_SUCCESS;

}

exile::ll::IniInterpretator::IniInterpretator()
{
	currentSectionName = "none";
}

exile::ll::IniInterpretator::~IniInterpretator()
{

}

exile::ll::IniInterpretatorSection::IniInterpretatorSection()
	:storage({})
{

}

const bool exile::ll::IniInterpretatorSection::Containts(const exile::String& variableName) const
{
	return true;
}

void exile::ll::IniInterpretatorSection::Mov(const exile::String& name, const exile::String value)
{
	storage[name] = value;
}


void exile::ll::IniInterpretatorSection::Add(const exile::String& name, const exile::String value)
{
	storage.insert(exile::UnorderedMapPair<exile::String, exile::String>(name, value));
}

const exile::String& exile::ll::IniInterpretatorSection::GetValue(const exile::String& name)const
{
	return storage.at(name);
}

void exile::ll::IniInterpretatorSection::Clear()
{
	storage.clear();
}
