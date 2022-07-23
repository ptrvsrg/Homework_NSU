cmake_minimum_required(VERSION 3.23)
project(Homework C)

set(SRC main.c)

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
target_link_libraries(main PUBLIC m)