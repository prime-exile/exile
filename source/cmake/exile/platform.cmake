cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(EXILE_ARCH "x86_64" CACHE STRING "Architecture")

if(EXILE_ARCH STREQUAL "x86_64")
    add_compile_definitions(EXILE_ARCH_X86_64)
    message("[exile]: EXILE_ARCH = ${EXILE_ARCH} using nasm")
    include("exile/nasm")
    if(WIN32)
        include("exile/platforms/win64")
    elseif(UNIX)
        include("exile/platforms/unix")
    else()
        message(SEND_ERROR "[exile]: unsupported platform!") 
    endif()
elseif(EXILE_ARCH STREQUAL "x86")
    add_compile_definitions(EXILE_ARCH_X86)
    message("[exile]: EXILE_ARCH = ${EXILE_ARCH} using nasm")
    include("nasm")
    if(WIN32)
        include("exile/platforms/win32")
    elseif(UNIX)
        include("exile/platforms/unix")
    else()
        message(SEND_ERROR "[exile]: unsupported platform!") 
    endif()
elseif(EXILE_ARCH STREQUAL "ARM64")
    add_compile_definitions(EXILE_ARCH_ARM64)
    message("[exile]: EXILE_ARCH = ${EXILE_ARCH} using gnu arm toolchain")
    include("exile/gas")
    if(UNIX)
        include("exile/platforms/unix")
    else()
        message(SEND_ERROR "[exile]: unsupported platform!") 
    endif()
endif()

include ("exile/configuration")