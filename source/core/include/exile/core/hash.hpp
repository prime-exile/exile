#ifndef _EXILE_CORE_HASH_HPP_
#define _EXILE_CORE_HASH_HPP_

#include <exile/core/API.h>

namespace exile
{
    namespace hash
    {
        constexpr u32 sdbm(const char* str)
        {
            u32 hash = 0;
            for(u32 i = 0; str[i] != 0; i += 1)
            {
                hash = (hash << 6) + (hash << 16) - hash + static_cast<unsigned char>(str[i]);
            }

            return hash;
        }

        constexpr u32 djb2(const char* str)
        {
            u32 hash = 5381;
            for(u32 i = 0; str[i] != 0; i += 1)
            {
                hash = ((hash << 5) + hash) + static_cast<unsigned char>(str[i]);
            }

            return hash;
        }

        constexpr u32 fnv1a32(const char* str)
        {
            u32 hash = 2166136261U;
            for(u32 i = 0; str[i] != 0; i+= 1)
            {
                hash = 16777619U * (hash ^ static_cast<unsigned char>(str[i]));
            }

            return hash;
        }


        constexpr u64 fnv1a64(const char* str)
        {
            u64 hash = 14695981039346656037ULL;
            for(u32 i = 0; str[i] != 0; i+= 1)
            {
                hash = 1099511628211ULL * (hash ^ static_cast<unsigned char>(str[i]));
            }

            return hash;
        }
    } 
}

#endif