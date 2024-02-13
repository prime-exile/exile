#ifndef _EXILE_WINDOW_H_
#define _EXILE_WINDOW_H_

#include <exile/core/API.h>

typedef struct
{
	void* handle;
	u8 closed;
}exWindow;

typedef u8 (*exPFN_WindowCreate)(exWindow* out, const char* title, u32 weight, u32 height);
typedef u8 (*exPFN_WindowShouldClose)(exWindow* wnd);
typedef u8 (*exPFN_WindowUpdate)(exWindow* wnd);
typedef u8(*exPFN_WindowClose)(exWindow* wnd);

extern exPFN_WindowCreate exWindowCreate;
extern exPFN_WindowClose exWindowClose;
extern exPFN_WindowShouldClose exWindowShouldClose;
extern exPFN_WindowUpdate exWindowUpdate;

//u8 exWindowCreate(exWindow* out, const char* title, u32 weight, u32 height);


#endif