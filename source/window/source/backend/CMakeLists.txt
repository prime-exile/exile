cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.window")

if(UNIX)
	if(EXILE_WINDOW_USE_LINUX_WAYLAND)
		message("[exile]: using wayland")
		add_subdirectory("wayland")
	endif(EXILE_WINDOW_USE_LINUX_WAYLAND)

	if(EXILE_WINDOW_USE_LINUX_X11)
		message("[exile]: using x11")
		add_subdirectory("x11")
	endif(EXILE_WINDOW_USE_LINUX_X11)
endif(UNIX)

if(WIN32)
	add_subdirectory("win32")
endif(WIN32)
