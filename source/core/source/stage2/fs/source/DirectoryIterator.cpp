#define EXILE_PRIVATE
#include <exile/core/fs/DirectoryIterator.hpp>

exile::core::DirectoryIterator::DirectoryIterator(const exile::String& path) : 
	finished(false),currentPath(path)
{
#if defined(EXILE_WIN)
	findHandle = FindFirstFileA((path + "\\*").c_str(), &findFileData);
	if (findHandle == INVALID_HANDLE_VALUE)
		finished = true;
#elif defined(EXILE_UNIX)
	directory = opendir(path.c_str());
	if (directory != NULL)
	{
		entry = readdir(directory);
	}
	else entry = NULL;
#endif
}

exile::core::DirectoryIterator::DirectoryIterator(const exile::core::Path& path)
:finished(false), currentPath(path)
{
#if defined(EXILE_WIN)
	findHandle = FindFirstFileA((path.Str() + "\\*").c_str(), &findFileData);
	if (findHandle == INVALID_HANDLE_VALUE)
		finished = true;
#elif defined(EXILE_UNIX)
	directory = opendir(path.CStr());
	if (directory != NULL)
	{
		entry = readdir(directory);
	}
	else entry = NULL;
#endif
}

bool exile::core::DirectoryIterator::IsFinished() const
{
#if defined(EXILE_WIN)
	return finished;
#elif defined(EXILE_UNIX)
	return  entry == NULL;
#endif
}

exile::core::DirectoryIterator& exile::core::DirectoryIterator::operator++()
{
#if defined(EXILE_WIN)
	if (!FindNextFileA(findHandle, &findFileData))
	{
		finished = true;
	}
#elif defined(EXILE_UNIX)
	if (directory != NULL)
	{
		entry = readdir(directory);
	}
	else entry = NULL;
#endif
	return *this;
}

const exile::String exile::core::DirectoryIterator::GetCurrentName() const
{
#if defined(EXILE_WIN)
	return findFileData.cFileName;
#elif defined(EXILE_UNIX)
	return  entry->d_name;
#endif
}

bool exile::core::DirectoryIterator::IsDirectory() const
{
#if defined(EXILE_WIN)
	return (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
#elif defined(EXILE_UNIX)
	return  entry != NULL ? entry->d_type == DT_DIR : false;
#endif
}

exile::core::DirectoryIterator::~DirectoryIterator()
{
#if defined(EXILE_WIN)
	if (findHandle != INVALID_HANDLE_VALUE)
	{
		FindClose(findHandle);
	}
#elif defined(EXILE_UNIX)
	if (directory != NULL)
	{
		closedir(directory);
	}
#endif
}
