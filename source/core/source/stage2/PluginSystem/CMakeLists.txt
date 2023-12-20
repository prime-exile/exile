cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")


set(CPP_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/NativePlugin.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/NativePluginLoader.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/PluginManager.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/DepencyManager.cpp"
)


target_sources(exile.core PRIVATE ${CPP_SOURCES} )