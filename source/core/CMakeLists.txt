cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.core")

if(EXILE_BUILD_DEV)
add_compile_definitions(EXILE_DEV)
endif()

option(EXILE_ULP_LOG_OPTIMIZED_MODE "in this mode formatted log we have 1024 buffer size" OFF)
option(EXILE_ULP_LOG_DYNAMIC_MODE "in this mode formatted log we have 1024 buffer size but if we have bigger message we allocate new buffer" ON)
option(EXILE_ULP_LOG_FULL_DYNAMIC_MODE "in this mode formatted log we allocate new buffer for message" OFF)

if(EXILE_ULP_LOG_OPTIMIZED_MODE)
add_compile_definitions(EXILE_ULP_LOG_OPTIMIZED)
elseif(EXILE_ULP_LOG_DYNAMIC_MODE)
add_compile_definitions(EXILE_ULP_LOG_DYNAMIC)
elseif(EXILE_ULP_LOG_FULL_DYNAMIC_MODE)
add_compile_definitions(EXILE_ULP_LOG_FULL_DYNAMIC)
endif()





add_compile_definitions(EX_VERSION_STRING="exp:0.0.1")

add_library(exile.core SHARED)
add_subdirectory("source")


target_include_directories(exile.core PUBLIC "include/")
target_include_directories(exile.core PRIVATE "private/include/")
set_target_properties(exile.core PROPERTIES NASM_OBJ_FORMAT ${EXILE_NASM_OBJ_FORMAT})

if(WIN32)
target_link_libraries(exile.core PUBLIC dbghelp)
endif(WIN32)