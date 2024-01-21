#ifndef _EXILE_CORE_FILE_HPP_
#define _EXILE_CORE_FILE_HPP_

#include <exile/core/containers/vector.hpp>
#include <exile/core/fs/Path.hpp>

namespace exile
{
	namespace core
	{
		class EX_API File
		{
		private:

			FILE* handle;
			
		public:

			File();

			File(const File&) = delete;

			u8 Open(const exile::core::Path& path, const char* mode);
			u8 Open(const exile::String& path, const char* mode);

			i64 GetSize();
			i64 Write(const char* fmt, ...);
			i64 Write(const char* buffer, u64 elementSize, u64  elementsCount);
			i64 Read(char* buffer, u64 elementSize, u64  elementsCount);
			i64 Read(exile::String& buffer, u64 bytesToRead);

			i32 Close();

			FILE* GetRawHandle();

			exile::core::File& operator=(exile::core::File& other) = delete;
			exile::core::File& operator==(exile::core::File& other) = delete;

			~File();

		};
	}
}

#endif