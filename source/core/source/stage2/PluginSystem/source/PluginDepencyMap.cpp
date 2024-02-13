#include <exile/core/pluginManager.hpp>
#include <exile/core/hash.hpp>
#include <exile/core/ulp/ulp.hpp>
#include <inttypes.h> 

#define ContaintsKey(map, k)(map.find(k) != map.end())
#define ContaintsVec(vec, k)(std::find(vec.begin(), vec.end(), k) != vec.end())



void exile::core::PluginDepencyMap::RegisterNames(const exile::Vector<exile::String>& names)
{
	for (const exile::String& name : names)
	{
		u32 hash = exile::hash::fnv1a32(name.c_str());
		this->names[hash] = name;
		dependices[hash] = {};
	}
}

void exile::core::PluginDepencyMap::RegisterDepency(const exile::String& plugin, const exile::String& depency)
{
	u32 hash = exile::hash::fnv1a32(plugin.c_str());
	u32 depencyHash = exile::hash::fnv1a32(depency.c_str());

	dependices[hash].emplace_back(depencyHash);

}

inline bool isAllDependicesLoaded(const exile::Vector<u32>& needed, const exile::Vector<u32>& seq)
{


}

inline void GetAllNotLoadedDeps(const exile::Vector<u32>& needed, const exile::Vector<u32>& seq, exile::Vector<u32>& out)
{

	for (u32 n : needed)
	{
		bool isFindNeeded = false;
		for (u32 s : seq)
		{
			if (s == n)
			{
				isFindNeeded = true;
				break;
			}
		}

		if (!isFindNeeded)
		{
			out.push_back(n);
		}
	}

}

void exile::core::PluginDepencyMap::TryLoadDep(u32 dep)
{

}

void exile::core::PluginDepencyMap::DebugPrintNames()
{
	exile::LogId id = exile::UniversalLoggingProtocol::Get()->GetCoreId();
	for (const exile::UnorderedMapPair<u32, exile::String>& pair : names)
	{
		exile::UniversalLoggingProtocol::Get()->Log(id, exile::LogLevel::Info, "%" PRIu32 " = %s", pair.first, pair.second.c_str());
	}
}

void exile::core::PluginDepencyMap::TranslateSequence(const exile::Vector<u32>& in, exile::Vector<exile::String>& out)
{
	for (u32 i : in)
	{
		out.emplace_back(names[i]);
	}
}

void exile::core::PluginDepencyMap::SortDependices(exile::Vector<u32>& out)
{

	for (exile::UnorderedMapPair<u32, exile::Vector<u32>> depency : dependices)
	{
		if (depency.second.empty())
		{
			out.emplace_back(depency.first);
		}
	}

	exile::Vector<u32> postponed;

	for (exile::UnorderedMapPair<u32, exile::Vector<u32>> depency : dependices)
	{
		if (!depency.second.empty())
		{
			bool isAllDepsLoaded = true;
			for (u32 dep : depency.second)
			{

				if (!ContaintsVec(out, dep))
				{
					isAllDepsLoaded = false;
					break;
				}

			}

			if (isAllDepsLoaded)
			{
				out.emplace_back(depency.first);
			}
			else
			{
				postponed.emplace_back(depency.first);
			}
		}
	}

	for (u32 id : postponed)
	{
		const exile::Vector<u32>& deps = dependices.at(id);
		if (ContaintsVec(out, id))
		{
			continue;
		}

		bool isAllDepsLoaded = true;
		for (u32 dep : deps)
		{
			if (!ContaintsVec(out, dep))
			{
				const exile::Vector<u32>& depDeps = dependices.at(dep);
				exile::Vector<u32> res;
				GetAllNotLoadedDeps(depDeps, out, res);

				if (res.empty())
				{
					out.emplace_back(dep);
				}


				//break;
			}
		}

		if (isAllDepsLoaded)
		{
			out.emplace_back(id);
		}

	}
}
