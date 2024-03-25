cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

option(EXILE_FORGE_MAIN "use forge entry main" ON)


if(EXILE_FORGE_MAIN)
add_compile_definitions(EXILE_FORGE_MAIN)

endif(EXILE_FORGE_MAIN)