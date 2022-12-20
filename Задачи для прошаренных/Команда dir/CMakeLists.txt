cmake_minimum_required(VERSION 3.16.3)
project(Homework C)

file(GLOB SRC "*.c")

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

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
	target_link_libraries(main PUBLIC ${MATH_LIBRARY})
endif()