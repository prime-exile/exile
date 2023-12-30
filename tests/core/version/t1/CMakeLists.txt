cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile" C CXX)

add_compile_definitions(EX_VERSION_STRING="exp:0.0.1")
add_executable(vers_t1 "source/main.c" )

add_test(NAME vers_t1_test 
	  COMMAND $<TARGET_FILE:vers_t1>
	)

add_custom_command(
        TARGET vers_t1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exile.core>
                $<TARGET_FILE_DIR:vers_t1>)

target_link_libraries(vers_t1 exile.core)

