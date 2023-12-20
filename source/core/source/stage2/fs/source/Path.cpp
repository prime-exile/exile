#define EXILE_PRIVATE
#include<exile/core/fs/Path.hpp>

exile::core::Path::Path()
	:path("")
{

}
exile::core::Path::Path(const char* path)
	:path(path)
{

}
exile::core::Path::Path(const exile::String& path)
	:path(path)
{
}

exile::core::Path& exile::core::Path::operator=(const Path& other)
{
	path = other.path; 
	return *this;
}

exile::core::Path& exile::core::Path::operator=(const exile::String& other)
{
	path = other;
	return *this;
}

const char* exile::core::Path::CStr() const
{
	return path.c_str();
}

const exile::String& exile::core::Path::Str() const
{
	return path;
}

const exile::core::PathType exile::core::Path::GetType() const
{
#if defined(EXILE_UNIX)
	int result = stat(path.data(), &info);

	if (result != 0)
	{
		return PathType::None;
	}

	if (S_ISREG(info.st_mode))
	{
		return PathType::File;
	}
	else if (S_ISDIR(info.st_mode))
	{
		return PathType::Dir;
	}
	else
	{
		return PathType::None;
	}
#elif defined(EXILE_WIN)
	DWORD result = GetFileAttributes(path.c_str());
	if (result == INVALID_FILE_ATTRIBUTES)
	{
		return PathType::None;
	}
	else if (result & FILE_ATTRIBUTE_DIRECTORY)
	{
		return PathType::Dir;
	}
	else
	{
		return PathType::File;
	}
#endif
}

u8 exile::core::Path::exists()const
{
#if defined(EXILE_WIN)
	DWORD result = GetFileAttributes(path.c_str());
	return (result != INVALID_FILE_ATTRIBUTES);
#elif defined(EXILE_UNIX)
	int result = stat(path.data(), &info);
	return result == 0 || S_ISREG(info.st_mode);
#endif
}
