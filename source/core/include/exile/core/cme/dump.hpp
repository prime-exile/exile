#ifndef _EXILE_CORE_ASSERT_CME_HPP_
#define _EXILE_CORE_ASSERT_CME_HPP_

#include <exile/core/API.h>
#include <exile/core/thread/thread.h>
#include <exile/core/memory.h>

#if defined(EXILE_WIN)
#include<Windows.h>
#include<DbgHelp.h>
#include <stdio.h>
#elif defined(EXILE_UNIX)
#include <errno.h>
#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

//#include <cxxabi.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <execinfo.h>
#endif

static __forceinline exile::String GetLastErrorAsString()
{
#if defined(EXILE_WIN)
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string(); //No error message has been recorded
}

    LPSTR messageBuffer = nullptr;

    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

    exile::String message(messageBuffer, size);

    LocalFree(messageBuffer);

#elif defined(EXILE_UNIX)
    exile::String message(strerror(errno));
#endif
    return message;
}

#endif