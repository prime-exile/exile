cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

set(C_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exLoadCriticalConfiguration.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exFreeCriticalConfiguration.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exSetupCriticalDefaultConfiguration.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exSetupCriticalConfigurationFromModule.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/exSetupCriticalConfiguration.c"
)

target_sources(exile.core PRIVATE ${C_SOURCES})