#define EXILE_PRIVATE
#include <exile/core/pluginManager.hpp>
#include <algorithm>

#define ContaintsKey(map, k)(map.find(k) != map.end())

const exile::Vector<exile::core::PluginId>& exile::core::PluginDepencyManager::GetDependices(PluginId pluginId) const
{
	return dependices.at(pluginId);
}

void exile::core::PluginDepencyManager::RemoveDepency(PluginId depency, PluginId pluginId)
{
	exile::Vector<PluginId>& vec = dependices.at(pluginId);
	vec.erase(std::find(vec.begin(), vec.end(), depency));
}

exile::core::PluginId exile::core::PluginDepencyManager::IsPluginDepencyFree(PluginId pluginId)
{
	if (ContaintsKey(dependices, pluginId))
	{
		return dependices[pluginId].empty();
	}
	else return true;
}

void exile::core::PluginDepencyManager::AddDepency(PluginId depency, PluginId pluginId)
{
	if (!ContaintsKey(dependices, pluginId))
	{
		dependices[pluginId] = { depency };
	}
	else
	{
		dependices[pluginId].push_back(pluginId);
	}
}