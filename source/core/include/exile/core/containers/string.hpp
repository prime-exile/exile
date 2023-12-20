#ifndef _EXILE_CORE_STRING_HPP_
#define _EXILE_CORE_STRING_HPP_

#include <string>
#include <exile/core/containers/allocator.hpp>

namespace exile
{
	typedef std::basic_string<char, std::char_traits<char>, exile::ExileAllocator<char>> String;

    inline size_t hashString(const exile::String& k)
    {
        size_t hv = 0;
        const char* key = k.data();
        while (*key != '\0')
        {
            hv = *key + (hv << 5) - hv;
            key++;
        }
        return hv;
    }
}

namespace std {
    template<>
    struct hash <exile::String> {
        size_t operator()(const exile::String& cs) const {
            
            return exile::hashString(cs);
            //return std::hash<const char*>()(cs.data());
        }
    };
}

#endif