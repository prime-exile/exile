#include <exile.window/loader.h>
#include <exile.window/window.h>

template<typename T>
T exLoadSym(const char* sym, exile::core::NativePlugin* plugin)
{
	void* lsym = plugin->GetProcAddress(sym);
	return reinterpret_cast<T>(lsym);
}

#define EX_SYM_CHECKED(target, type, sym, plugin)\
	target  = exLoadSym<type>(sym, plugin);\
	if(target == NULL) return EX_ERROR;


u8 exWindowInit(exile::core::NativePlugin* plugin)
{
	EX_SYM_CHECKED(exWindowCreate, exPFN_WindowCreate, "exWindowCreate", plugin);
	EX_SYM_CHECKED(exWindowClose, exPFN_WindowClose, "exWindowClose", plugin);
	EX_SYM_CHECKED(exWindowShouldClose, exPFN_WindowShouldClose, "exWindowShouldClose", plugin);
	EX_SYM_CHECKED(exWindowUpdate, exPFN_WindowUpdate, "exWindowUpdate", plugin);
	
	return EX_SUCCESS;
}
