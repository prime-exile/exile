cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

include(ExternalProject)

set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/ExternalProject)

set(EXILE_RUST_LIBS ws2_32 userenv advapi32 ntdll bcrypt CACHE INTERNAL "Rust libs")

function(rust_project RPROJECT_NAME)
    ExternalProject_Add(
        ${RPROJECT_NAME}
        DOWNLOAD_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND cargo build COMMAND cargo build --release --target-dir=${CMAKE_BINARY_DIR}/rust/${RPROJECT_NAME}
        BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${RPROJECT_NAME}"
        INSTALL_COMMAND ""
        LOG_BUILD ON)


    if(WIN32)
        set(${RPROJECT_NAME}_LIB 
        debug "${CMAKE_CURRENT_SOURCE_DIR}/${RPROJECT_NAME}/target/debug/${RPROJECT_NAME}.lib"
        optimized "${CMAKE_CURRENT_SOURCE_DIR}/${RPROJECT_NAME}/target/release/${RPROJECT_NAME}.lib"
        CACHE INTERNAL "${RPROJECT_NAME} library path") 
    elseif(UNIX)
        set(VAR ${RPROJECT_NAME}_LIB       
        debug "${CMAKE_CURRENT_SOURCE_DIR}/${RPROJECT_NAME}/target/debug/lib${RPROJECT_NAME}.a"
        optimized "${CMAKE_CURRENT_SOURCE_DIR}/${RPROJECT_NAME}/target/release/lib${RPROJECT_NAME}.a") 
    endif()

    message("${RPROJECT_NAME}_LIB")
endfunction()


