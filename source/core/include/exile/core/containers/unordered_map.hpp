#ifndef _EXILE_CORE_UNORDERED_MAP_HPP
#define _EXILE_CORE_UNORDERED_MAP_HPP

#include <exile/core/containers/string.hpp>
#include <unordered_map>
#include <exile/core/containers/allocator.hpp>

namespace exile
{
	template<class Key, class Value, typename hash = std::hash<Key>, typename KeyEq = std::equal_to<Key>, typename Allocator = exile::ExileAllocator<std::pair<Key, Value>>>
	using UnorderedMap = std::unordered_map<Key, Value, hash, KeyEq, Allocator>;

	template<class Key, class Value, typename pair = std::pair<Key, Value>>
	using UnorderedMapPair = pair;
}

#endif