cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile" C CXX)

add_executable(memory_t1 "source/main.c" )

add_test(NAME memory_t1_test 
	  COMMAND $<TARGET_FILE:memory_t1>
	)


add_custom_command(
        TARGET memory_t1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exile.core>
                $<TARGET_FILE_DIR:memory_t1>)

target_link_libraries(memory_t1 exile.core)