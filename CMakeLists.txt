cmake_minimum_required(VERSION 3.5.1)
project(lab_test C)

FILE(GLOB_RECURSE FILES CMakeLists.txt)

math(EXPR NUM "1")

include(CTest)
enable_testing()

foreach(file ${FILES})
    string(REPLACE "/CMakeLists.txt" "" full_dir ${file})
    string(REPLACE "${CMAKE_HOME_DIRECTORY}" "." dir ${full_dir})
    message(STATUS "Adding subdirectory ${dir}")
    if (NOT (${dir} STREQUAL "."))
        set(TARGET "main${NUM}")
        math(EXPR NUM "${NUM} + 1")
        add_subdirectory(${dir})
    endif()
endforeach()