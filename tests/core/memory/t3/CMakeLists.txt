cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project("exile" C CXX)

add_executable(memory_t3 "source/main.cpp" )

add_test(NAME memory_t3_test 
	  COMMAND $<TARGET_FILE:memory_t2>
	)


add_custom_command(
        TARGET memory_t3 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:exile.core>
                $<TARGET_FILE_DIR:memory_t3>)

target_link_libraries(memory_t3 exile.core)