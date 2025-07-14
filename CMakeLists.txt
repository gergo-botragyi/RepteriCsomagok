cmake_minimum_required(VERSION 3.10.0)
project(airport VERSION 0.1.0 LANGUAGES C CXX)

add_executable(airport belt.cpp bfs.cpp controlcenter.cpp io.cpp junction.cpp list.cpp main.cpp memtrace.cpp package.cpp path.cpp)

target_compile_options(airport PRIVATE -Wall -Werror)
target_compile_definitions(airport PRIVATE MEMTRACE)

set(CPORTA ON)
set(INPTESZT OFF)

if(CPORTA)
    target_compile_definitions(airport PRIVATE CPORTA)
endif()

if(INPTESZT)
    target_compile_definitions(airport PRIVATE INPTESZT)
endif()

if(MAIN)
    target_compile_definitions(airport PRIVATE MAIN)
endif()

include(CTest)
enable_testing()

add_custom_target(run
    COMMAND cmd /c start \"\" cmd /c \"$<TARGET_FILE:airport> & pause\"
    DEPENDS airport
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)