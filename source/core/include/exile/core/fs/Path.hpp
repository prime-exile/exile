#ifndef _EXILE_CORE_PATH_HPP_
#define _EXILE_CORE_PATH_HPP_

#include <exile/core/containers/string.hpp>

#if defined(EXILE_UNIX)
#include <sys/stat.h>
#endif


namespace exile
{
	namespace core
	{
		enum class PathType
		{
			None, 
			Dir,
			File
		};

		class EX_API Path
		{
#if defined(EXILE_UNIX)
			mutable struct stat info;
#endif
			exile::String path;
		public:

			Path();
			Path(const char* path);
			Path(const exile::String& path);

			Path& operator=(const Path& other);
			Path& operator=(const exile::String& other);

			const char* CStr() const;
			const exile::String& Str() const;

			const PathType GetType() const;

			u8 exists()const;

			exile::core::Path& operator==(exile::core::Path& other) = delete;

			virtual ~Path()
			{
			}

		};
	}
}

#endif