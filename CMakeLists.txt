cmake_minimum_required(VERSION 3.10)
project(UPMEM-MLP C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SRC_FILES src/*.c)
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/mlp.c")
file(GLOB TEST_FILES tests/*.c)

enable_testing()

foreach(TEST_SRC ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_SRC} ${SRC_FILES})
    target_include_directories(${TEST_NAME} PRIVATE include)
    target_link_libraries(${TEST_NAME} m)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()