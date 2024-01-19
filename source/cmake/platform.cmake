cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(EXILE_ARCH "x86_64" CACHE STRING "Architecture")

if(EXILE_ARCH STREQUAL "x86_64")
    add_compile_definitions(EXILE_ARCH_X86_64)
    message("[exile]: EXILE_ARCH = ${EXILE_ARCH} using nasm")
    include("${CMAKE_SOURCE_DIR}/source/cmake/nasm.cmake")
    if(WIN32)
        include("${CMAKE_SOURCE_DIR}/source/cmake/platforms/win64.cmake")
    elseif(UNIX)
        include("${CMAKE_SOURCE_DIR}/source/cmake/platforms/unix.cmake")
    else()
        message(SEND_ERROR "[exile]: unsupported platform!") 
    endif()
elseif(EXILE_ARCH STREQUAL "x86")
    add_compile_definitions(EXILE_ARCH_X86)
    message("[exile]: EXILE_ARCH = ${EXILE_ARCH} using nasm")
    include("${CMAKE_SOURCE_DIR}/source/cmake/nasm.cmake")
    if(WIN32)
        include("${CMAKE_SOURCE_DIR}/source/cmake/platforms/win32.cmake")
    elseif(UNIX)
        include("${CMAKE_SOURCE_DIR}/source/cmake/platforms/unix.cmake")
    else()
        message(SEND_ERROR "[exile]: unsupported platform!") 
    endif()
elseif(EXILE_ARCH STREQUAL "ARM64")
    add_compile_definitions(EXILE_ARCH_ARM64)
    message("[exile]: EXILE_ARCH = ${EXILE_ARCH} using gnu arm toolchain")
    include("${CMAKE_SOURCE_DIR}/source/cmake/gas.cmake")
    if(UNIX)
        include("${CMAKE_SOURCE_DIR}/source/cmake/platforms/unix.cmake")
    else()
        message(SEND_ERROR "[exile]: unsupported platform!") 
    endif()
endif()

