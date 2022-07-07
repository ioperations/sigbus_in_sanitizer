cmake_minimum_required(VERSION 3.13)
project(leetcode LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
SET(CXX "clang++")

set(CXX_FLAGS     
    -DVALGRIND
    -DCHECK_PTHREAD_RETURN_VALUE
    -D_FILE_OFFSET_BITS=64
    -Wall
    #-Wextra
    -Wconversion
    -Wno-unused-parameter
    -Wold-style-cast
    -Wpointer-arith
    -Wshadow
    -Wwrite-strings
    -march=native
    -MMD
    -DTEST_ADQ
    -fuse-ld=lld
    )

enable_testing()

file(GLOB source_list "*.cc" )

foreach (CXX_SRC ${source_list})
    string(REGEX REPLACE "\\.cc" "" OBJ ${CXX_SRC})
    string(REGEX REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" OBJ ${OBJ})
    set(OBJ_FILES ${OBJ_FILES} ${OBJ})
endforeach ()


set(leetcode  ${OBJ_FILES})


foreach(test1 ${leetcode})
    add_executable("${test1}" ${test1}.cc)
    target_compile_options(${test1} PUBLIC "-DTEST_ADQ")
    target_compile_options(${test1} PUBLIC "-Wall")
    target_compile_options(${test1} PRIVATE "-fsanitize=address")
    target_link_options(${test1} PRIVATE "-fsanitize=address")

    add_test(NAME ${test1} COMMAND ${test1} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()
