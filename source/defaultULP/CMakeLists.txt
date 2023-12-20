cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile.defaultULP")

set(CPP_SOURCES "source/main.cpp" "source/stdout/stdoutLogHandler.cpp")

if(WIN32)
list(APPEND CPP_SOURCES  "source/vsoutput/vsoutputLogHandler.cpp")
endif()


add_library(exileDefaultULP SHARED ${CPP_SOURCES})

if(WIN32)
option(EXILE_DEFAULT_ULP_VS_OUTPUT "enable vs output" OFF)
endif()

option(EXILE_DEFAULT_ULP_STDOUT "enable stdout output" OFF)

if(EXILE_DEFAULT_ULP_VS_OUTPUT)
add_compile_definitions(EXILE_DULP_VS_OUTPUT)
endif(EXILE_DEFAULT_ULP_VS_OUTPUT)

if(EXILE_DEFAULT_ULP_STDOUT)
add_compile_definitions(EXILE_DULP_STDOUT)
endif(EXILE_DEFAULT_ULP_STDOUT)

target_link_libraries(exileDefaultULP PRIVATE exile.core)