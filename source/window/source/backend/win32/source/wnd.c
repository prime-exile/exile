#include <exile/core/API.h>
#include <exile/core/assert.h>
#include <exile.window/shared.h>

#include <Windows.h>
#include <WinUser.h>

const char* exGWindowClassName = "PRIME_EXILE_WINDOW_CLASS";

u32 exGenerateClassName(const char* title, char* out, u32 bufferLen)
{
    u32 classNameLen = strlen(exGWindowClassName);
    u32 titleLen = strlen(title);

    u32 i = 0;

    for (; i < classNameLen && i < bufferLen; i += 1)
    {
        out[i] = exGWindowClassName[i];
    }

    out[i] = '_';
    i += 1;


    for (u32 j = 0; j < titleLen && i < bufferLen; i += 1, j += 1)
    {
        out[i] = title[j];
    }

    out[i] = '\0';

    return i;
 }

static void* GetWindowParam(HWND hwnd, UINT msg, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        void* ptr = ((CREATESTRUCT*)lParam)->lpCreateParams;

        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)ptr);
    }
    else
    {
        return GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    exWindow* wnd = GetWindowParam(hwnd, msg, lParam);

    switch (msg)
    {
    case WM_CLOSE:
        wnd->closed = EX_TRUE;
       //DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_NCCREATE:
        
        break;
    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

EXILE_API_EXPORT u8 exWindowCreate(exWindow* out, const char* title, u32 weight, u32 height, exWindowCreationFlag flags)
{
    WNDCLASSEXA wc;
	HWND hwnd;

    out->closed = EX_FALSE;

    char* className[1024];

    exGenerateClassName(title, className, 1024);

    wc.cbSize = sizeof(WNDCLASSEXA);
	wc.style = NULL;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = className;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    exAssertFR(!RegisterClassExA(&wc), {}, EX_ERROR, "failed to register class %s for window %s", className, title);

    RECT WndUserArea;
    WndUserArea.left = 0;
    WndUserArea.top = 0;
    WndUserArea.right = weight;
    WndUserArea.bottom = height;

    AdjustWindowRect(&WndUserArea, WS_OVERLAPPEDWINDOW, EX_FALSE);

    int ScreenCenterX = (GetSystemMetrics(SM_CXSCREEN) - WndUserArea.right) / 2;
    int ScreenCenterY = (GetSystemMetrics(SM_CYSCREEN) - WndUserArea.bottom) / 2;

    hwnd = CreateWindowExA(NULL, className, title, WS_OVERLAPPEDWINDOW, ScreenCenterX, ScreenCenterY, WndUserArea.right, WndUserArea.bottom, NULL, NULL, wc.hInstance, out);

    exAssertFR(!hwnd, { UnregisterClassA(className, wc.hInstance);
    }, EX_ERROR, "failed to create window %s!", title);
    
    out->handle = hwnd;

    //temp
    ShowWindow(hwnd, EX_TRUE);
    UpdateWindow(hwnd);

    return EX_SUCCESS;
}

EXILE_API_EXPORT u8 exWindowUpdate(exWindow* wnd)
{
    MSG msg;
    u8 res = GetMessageA(&msg, NULL, NULL, NULL) < 0;
    wnd->closed = res;
    TranslateMessage(&msg);
    DispatchMessage(&msg);
    return res;
}

EXILE_API_EXPORT u8 exWindowShouldClose(exWindow* wnd)
{
    return wnd->closed;
}

EXILE_API_EXPORT void exWindowClose(exWindow* wnd)
{
    char* className[1024];
    char* buffer[1024];
    GetWindowTextA(wnd->handle, buffer, 1024);
    exGenerateClassName(buffer, className, 1024);

    DestroyWindow(wnd->handle);
    UnregisterClassA(className, GetModuleHandle(NULL));
}