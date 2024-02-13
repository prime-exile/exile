cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

option(EXILE_CME_DUMP_DISABLE "disable all $report information" OFF)
option(EXILE_VARIABLE_STORAGE_DISABLE "disable variable storage" OFF)

if(EXILE_CME_DUMP_DISABLE)
	add_compile_definitions(EXILE_DISABLE_CME_DUMP)
	message("[exile]: CME dump disabled!")
endif()

if(EXILE_VARIABLE_STORAGE_DISABLE)
	add_compile_definitions(EXILE_DISABLE_VAR_STORAGE)
	message("[exile]: variable storage disabled!")
endif()
