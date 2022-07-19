cmake_minimum_required(VERSION 3.5.1)
project(Homework C)

set(SRC main.c)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

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