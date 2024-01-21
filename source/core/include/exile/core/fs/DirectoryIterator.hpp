#ifndef _EXILE_CORE_DIRECTORY_ITERATOR_HPP_
#define _EXILE_CORE_DIRECTORY_ITERATOR_HPP_

#include <exile/core/fs/Path.hpp>

#if defined(EXILE_WIN)
#include <Windows.h>
#elif defined(EXILE_UNIX)
#include <dirent.h>
#endif


namespace exile
{
	namespace core
	{
		class EX_API DirectoryIterator
		{
		private:

#if defined(EXILE_WIN)
			HANDLE findHandle;
			WIN32_FIND_DATA findFileData;
#elif defined(EXILE_UNIX)
			DIR* directory;
			struct dirent* entry;
#endif
			exile::core::Path currentPath;
			bool finished;

		public:

			DirectoryIterator(const exile::String& path);
			DirectoryIterator(const exile::core::Path& path);

			DirectoryIterator(const DirectoryIterator&) = delete;

			bool IsFinished() const;

			DirectoryIterator& operator++();
			const exile::String GetCurrentName() const;

			bool IsDirectory() const;

			exile::core::DirectoryIterator& operator=(exile::core::DirectoryIterator& other) = delete;
			exile::core::DirectoryIterator& operator==(exile::core::DirectoryIterator& other) = delete;

			~DirectoryIterator();

		};
	}
}

#endif