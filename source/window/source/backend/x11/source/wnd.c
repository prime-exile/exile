#include <exile/core/API.h>
#include <exile/core/assert.h>
#include <exile.window/shared.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

Display* display = NULL;

Atom wmDeleteWindow;

EXILE_API_EXPORT u8 exWindowCreate(exWindow* out, const char* title, u32 weight, u32 height, exWindowCreationFlag flags)
{
	if (display == NULL)
	{
		display = XOpenDisplay(NULL);
		exAssertR(display == NULL, {}, EX_ERROR, "failed to open x11 display");
	}

	unsigned long bgcolor;
	int myDepth;

	int ourScreen = DefaultScreen(display);
	bgcolor = WhitePixel(display, ourScreen);     /* Белый цвет экрана         */
	myDepth = DefaultDepth(display, ourScreen);   /* Глубина цветности экрана  */
	Visual* myVisual = DefaultVisual(display, ourScreen); /* Визуальные характеристики */

	XSetWindowAttributes myAttr;
	myAttr.background_pixel = bgcolor;

	Window root = XDefaultRootWindow(display);
	exAssertR(None == root, {}, EX_ERROR, "no root window found");
	Window window = XCreateWindow(display, root, 0, 0, weight, height, 0, myDepth, InputOutput, myVisual, CWBackPixel, &myAttr);
	//Window window = XCreateSimpleWindow(display, root, 0, 0, 800, 600, 0, 0, 0xffffffff);
	exAssertR(None == window, {}, EX_ERROR, "failed to create window");

	XMapWindow(display, window);

	wmDeleteWindow = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, window, &wmDeleteWindow, 1);

	XChangeProperty(display, window, XInternAtom(display, "USER_DATA", False), 0, 8, PropModeReplace, out, sizeof(exWindow*));

	out->handle = window;
	out->closed = 0;
}

EXILE_API_EXPORT u8 exWindowUpdate(exWindow* wnd)
{
	XEvent event;
	XNextEvent(display, &event);

	switch (event.type)
	{
	case ClientMessage:
		if (event.xclient.data.l[0] == wmDeleteWindow) {
			event.xclient.window;
			wnd->closed = EX_TRUE;
		}
		break;
	}
}

EXILE_API_EXPORT u8 exWindowShouldClose(exWindow* wnd)
{
	return wnd->closed;
}

EXILE_API_EXPORT void exWindowClose(exWindow* wnd)
{
	XDestroyWindow(display, wnd->handle);
	XEvent event;
	XNextEvent(display, &event);
}