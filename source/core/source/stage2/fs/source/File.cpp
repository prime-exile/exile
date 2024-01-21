#define EXILE_PRIVATE
#include <exile/core/fs/File.hpp>

#include <stdarg.h>

exile::core::File::File()
	:handle(NULL)
{

}

u8 exile::core::File::Open(const exile::core::Path& path, const char* mode)
{
	if (handle != NULL)
	{
		Close();
	}


	handle = fopen(path.CStr(), mode);

	if (handle == NULL)
	{
		return EX_ERROR;
	}

	return EX_SUCCESS;
}

u8 exile::core::File::Open(const exile::String& path, const char* mode)
{
	if (handle != NULL)
	{
		Close();
	}


	handle = fopen(path.c_str(), mode);

	if (handle == NULL)
	{
		return EX_ERROR;
	}

	return EX_SUCCESS;
}

i64 exile::core::File::GetSize()
{
	if (handle == NULL)
	{
		return 0;
	}

	fseek(handle, 0L, SEEK_END);

	u64 fileSize = ftell(handle);

	fseek(handle, 0L, SEEK_SET);
	return fileSize;
}

i64 exile::core::File::Write(const char* fmt, ...)
{
	va_list	args;
	va_start(args, fmt);

	int res = fprintf(handle, fmt, args);

	va_end(args);
	return res > 0;
}

i64 exile::core::File::Write(const char* buffer, u64 elementSize, u64  elementsCount)
{
	return fwrite(buffer, elementSize, elementsCount, handle);
}

i64 exile::core::File::Read(char* buffer, u64 elementSize, u64  elementsCount)
{
	return fread(buffer, elementSize, elementsCount, handle);
}

i64 exile::core::File::Read(exile::String& buffer, u64 bytesToRead) 
{
	exile::Vector<char> c(bytesToRead + 1);
	exMemset(c.data(), 0, bytesToRead + 1);
	i64 bytes = fread(c.data(), sizeof(char), bytesToRead, handle);
	buffer = c.data();
	return bytes;
}

i32 exile::core::File::Close()
{
	i32 r = fclose(handle);
	handle = NULL;
	return r;
}

FILE* exile::core::File::GetRawHandle()
{
	return handle;
}

exile::core::File::~File()
{
	if (handle != NULL)
	{ 
		Close();
	}
}