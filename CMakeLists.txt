cmake_minimum_required(VERSION 3.5.1)
project(lab_test C)

FILE(GLOB_RECURSE FILES CMakeLists.txt)

math(EXPR NUM "1")

include(CTest)
enable_testing()

foreach(file ${FILES})
    string(REPLACE "/CMakeLists.txt" "" dir ${file})
    message(STATUS "Adding ${dir}")
    if (NOT (${dir} STREQUAL ${CMAKE_HOME_DIRECTORY}))
        set(TARGET "main${NUM}")
        math(EXPR NUM "${NUM} + 1")
        add_subdirectory(${dir})
    endif()
endforeach()