cmake_minimum_required(VERSION 3.10)
project(UPMEM-MLP C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SRC_FILES src/host/*.c)
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/host/mlp.c")
file(GLOB TEST_FILES tests/*.c)

execute_process(
    COMMAND dpu-pkg-config --cflags dpu
    OUTPUT_VARIABLE DPU_C_FLAGS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND dpu-pkg-config --libs dpu
    OUTPUT_VARIABLE DPU_LIBS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

enable_testing()

add_custom_target(build_dpu_program ALL
    COMMAND dpu-upmem-dpurte-clang
            -I${CMAKE_SOURCE_DIR}/include
            -o ${CMAKE_BINARY_DIR}/dpu_program
            ${CMAKE_SOURCE_DIR}/src/dpu/dpu_program.c
)

add_compile_definitions(
    # NUM_DPU=1     Important: This macro override was commented because it does not apply to the dpu-upmem-dpurte-clang execution above; and therefore causes mismatch between
    #               dpu_program.c and the rest. So this file should avoid modifying dimensions set through macros in aforementioned header files.
    DPU_BINARY_PATH=\"./dpu_program\"
)

foreach(TEST_SRC ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_SRC} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_SRC} ${SRC_FILES})
    target_include_directories(${TEST_NAME} PRIVATE include)
    target_compile_options(${TEST_NAME} PRIVATE ${DPU_C_FLAGS})
    target_link_libraries(${TEST_NAME} PRIVATE m ${DPU_LIBS})

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()