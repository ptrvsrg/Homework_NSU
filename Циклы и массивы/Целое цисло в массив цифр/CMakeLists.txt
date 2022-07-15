cmake_minimum_required(VERSION 3.5.1)
project(Homework C)

set(SRC main.c)

add_executable(main ${SRC})

target_link_libraries(main m)