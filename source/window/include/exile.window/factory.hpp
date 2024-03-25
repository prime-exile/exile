#ifndef _EXILE_WINDOW_FACTORY_HPP_
#define _EXILE_WINDOW_FACTORY_HPP_


#include <exile/core/API.h>

namespace exile
{
	namespace window
	{
		class IWindow;

		struct WindowCreationContext
		{
			u8 Win32DisableDecoration;
			u8 X11DisableDecoration;
		};

		class IWindowFactory
		{
		public:

			virtual exile::window::IWindow* CreateWindow(const char* title, const u32 height, const u32 width, WindowCreationContext* ctx) = 0;


		};
	}
}

#endif