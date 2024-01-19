cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

set(C_SOURCES 
	"${CMAKE_CURRENT_SOURCE_DIR}/source/thread/exThreadCreate.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/thread/exThreadDestroy.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/thread/exThreadCancel.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/thread/exThreadGetCurrentId.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/thread/exThreadSleep.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/thread/exThreadActive.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/thread/exThreadJoin.c"

	"${CMAKE_CURRENT_SOURCE_DIR}/source/mutex/exMutexCreate.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/mutex/exMutexDestroy.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/mutex/exMutexLock.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/source/mutex/exMutexUnlock.c"

)

target_sources(exile.core PRIVATE ${C_SOURCES})
