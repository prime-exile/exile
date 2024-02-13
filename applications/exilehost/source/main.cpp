#include <exception>
#include <exile/core/critical.hpp>
#include <exile/core/instance.hpp>
#include <exile/core/cme/panic.hpp>
#include <exile/core/assertNew.h>

#include <iostream>

//#if defined(EXILE_WIN)
//#include<Windows.h>
//#include<dbghelp.h>



//void printStackTrace() {
//    // Initialize symbol handling
//    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS);
//    HANDLE process = GetCurrentProcess();
//    SymInitialize(process, nullptr, TRUE);
//
//    // Capture context
//    CONTEXT context;
//    RtlCaptureContext(&context);
//
//    // Initialize stack frame for walking
//    STACKFRAME64 stackFrame = {};
//    DWORD machineType = IMAGE_FILE_MACHINE_I386;
//
//#ifdef _M_X64
//    machineType = IMAGE_FILE_MACHINE_AMD64;
//#endif
//
//    stackFrame.AddrPC.Offset = context.Rip;
//    stackFrame.AddrPC.Mode = AddrModeFlat;
//    stackFrame.AddrFrame.Offset = context.Rbp;
//    stackFrame.AddrFrame.Mode = AddrModeFlat;
//    stackFrame.AddrStack.Offset = context.Rsp;
//    stackFrame.AddrStack.Mode = AddrModeFlat;
//
//    // Walk the stack
//    const int maxFrames = 32;
//    for (int frameNum = 0; frameNum < maxFrames; ++frameNum) {
//        BOOL result = StackWalk64(
//            machineType,
//            process,
//            GetCurrentThread(),
//            &stackFrame,
//            &context,
//            nullptr,
//            SymFunctionTableAccess64,
//            SymGetModuleBase64,
//            nullptr
//        );
//
//        if (!result || stackFrame.AddrFrame.Offset == 0) {
//            break;
//        }
//
//        // Get function name and offset
//        char symbolBuffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
//        PSYMBOL_INFO symbol = (PSYMBOL_INFO)symbolBuffer;
//        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
//        symbol->MaxNameLen = MAX_SYM_NAME;
//
//        DWORD64 displacement = 0;
//        if (SymFromAddr(process, stackFrame.AddrPC.Offset, &displacement, symbol)) {
//            std::cout << "[" << frameNum << "] " << symbol->Name << " + " << displacement << std::endl;
//        }
//        else {
//            std::cout << "[" << frameNum << "] <unknown function>" << std::endl;
//        }
//    }
//
//    // Cleanup symbol handling
//    SymCleanup(process);
//}
//
//#elif defined(EXILE_UNIX)
//#include <errno.h>
//#include <execinfo.h>
//#include <stdio.h>
//#include <stdlib.h>
//
//#include <cxxabi.h>
//#include <dlfcn.h>
//#include <stdlib.h>
//#include <execinfo.h>
//
//
//void printStackTrace() {
//	void* stackTrace[10];
//	int stackSize = backtrace(stackTrace, 10);
//	char** stackSymbols = backtrace_symbols(stackTrace, stackSize);
//
//
//	if (stackSymbols == nullptr) {
//		perror("backtrace_symbols");
//		exit(EXIT_FAILURE);
//	}
//
//	for (int i = 0; i < stackSize; ++i) {
//		printf("%s\n", stackSymbols[i]);
//	}
//
//	free(stackSymbols);
//}
//
//
//#endif


/*
 * exception report for CME:
 * 1 - win32(GetLastError), unix(errno)
 * 2 - if exception -> desc
 *
 */

void PrintVersion(const exVersion* version)
{
    char buffer[1024];
    u32 len = exVersionStr(version, 1024, buffer);
    if (len >= 1024)
    {
        char* dBuffer = exile::memory::AllocRaw<char>(len + 1);
        exVersionStr(version, len, dBuffer);
        puts(dBuffer);
        puts("\n");
        exile::memory::Free(dBuffer);
    }

    puts(buffer);

}

void test()
{
}

int main()
{
	try 
	{
        exSetupCriticalDefaultConfiguration();
        exPanic("hi");

        puts(EX_BUILD_DATETIME);
        
		exile::core::Engine& engine = exGEngine;
        exile::cme::InstallPanicHandler();
        
        engine.GetPluginManager().LoadPlugin("exDefaultULP");

        exile::UniversalLoggingProtocol::Get()->Log(exile::UniversalLoggingProtocol::Get()->GetCoreId(), exile::LogLevel::Info, "hi");
        
        exAssertF(true, { puts("2"); }, "hel;lo %s", "sam");

        test();
        
        exile::core::IPlugin* plugin = engine.GetPluginManager().GetPluginByName("exDefaultULP");
        PrintVersion(&plugin->GetVersion());

        exile::UniversalLoggingProtocol::Get()->Log(exile::UniversalLoggingProtocol::Get()->GetCoreId(), exile::LogLevel::Info, "starting loading");

		engine.GetPluginManager().UnloadPlugins();
	} 
    catch (const std::out_of_range& ofr)
    {
    }
	catch (const std::exception& ex)
	{
#if defined(EXILE_WIN)
		std::cout << "GetLastError:" << GetLastError() << ":" << ex.what() << std::endl;
#elif defined(EXILE_UNIX)
		std::cout << "errno:" << errno << ":" << ex.what() << std::endl;

#endif
	} 
	return 0;
}
