cmake_minimum_required(VERSION 3.16.3)
project(Homework C)

if(NOT DEFINED TARGET)
    set(TARGET main)
endif()

file(GLOB SRC "*.c")

add_executable(${TARGET} ${SRC})

if(WIN32)
    target_compile_options(${TARGET} PUBLIC
        /W4
        /WX
    )
else()
    target_compile_options(${TARGET} PUBLIC
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