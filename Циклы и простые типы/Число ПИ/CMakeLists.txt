cmake_minimum_required(VERSION 3.23)
project(Homework C)

set(SRC main.c)

add_executable(main ${SRC})

target_compile_options(main PRIVATE
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
            -fno-omit-frame-pointer
            -fsanitize=address
            -fsanitize=leak
            -fsanitize=undefined)
target_link_libraries(main PUBLIC -fuse-ld=gold)
target_link_libraries(main PUBLIC -fsanitize=undefined)
target_link_libraries(main PUBLIC -lasan -fuse-ld=gold)
target_link_libraries(main m)