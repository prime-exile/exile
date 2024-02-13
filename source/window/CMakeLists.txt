cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.window")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/source/cmake")

if(EXILE_BUILD_DEV)
	add_compile_definitions(EXILE_DEV)
endif()

if(UNIX)
	option(EXILE_WINDOW_USE_LINUX_WAYLAND "include wayland support" OFF)
	option(EXILE_WINDOW_USE_LINUX_X11 "include x11 support" ON)
endif(UNIX)
if(WIN32)

endif(WIN32)

add_library(exile.window SHARED)


if(WIN32)
	target_link_libraries(exile.window PUBLIC dbghelp)
endif(WIN32)

target_link_libraries(exile.window PRIVATE exile.core)

#loader
add_library(exile.window.loader STATIC "loader/source/main.cpp" "loader/source/symbols.cpp")
target_include_directories(exile.window.loader PUBLIC "include/")
target_link_libraries(exile.window.loader PRIVATE exile.core)

if(EXILE_WINDOW_USE_LINUX_WAYLAND)
	add_compile_definitions(EXILE_WINDOW_WAYLAND)
	find_package(WAYLAND 1.10.0 REQUIRED)
	target_link_libraries(exile.window PRIVATE ${WAYLAND_LIBRARIES})
endif(EXILE_WINDOW_USE_LINUX_WAYLAND)

if(EXILE_WINDOW_USE_LINUX_X11)
	find_package(X11 REQUIRED)

	add_compile_definitions(EXILE_WINDOW_X11)
	target_link_libraries(exile.window PRIVATE ${X11_LIBRARIES})

endif()

add_subdirectory("source")
add_subdirectory("loader")
