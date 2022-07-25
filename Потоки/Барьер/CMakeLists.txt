cmake_minimum_required(VERSION 3.5.1)
cmake_minimum_required(VERSION 3.16.3)
project(Homework C)

set(SRC main.c)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(main ${SRC})

if(WIN32)
    target_compile_options(main PUBLIC
        /W4
        /WX
    )
else()
    target_compile_options(main PUBLIC
        -Werror
        -Wall
        -Wextra
        -Waddress
        -Warray-bounds
        -Wbuiltin-macro-redefined
        -Wswitch
        -Wunreachable-code
        -pedantic
        -pedantic-errors
        -g
        -O1
    )
endif()