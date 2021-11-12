# Copyright (c) Prevail Verifier contributors.
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.10)
project(ebpf_verifier)

find_package(Boost REQUIRED)
set(CMAKE_CXX_STANDARD 17)

include_directories(./external)
include_directories(./external/ELFIO)
include_directories(./external/etl/include)
include_directories(./src)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

file(GLOB LIB_SRC
        "./src/*.cpp"
        "./src/crab/*.cpp"
        "./src/crab_utils/*.cpp"
        "./src/linux/gpl/*.cpp"
        "./src/linux/linux_platform.cpp"
        )

file(GLOB ALL_TEST
        "./src/test/test.cpp"
        "./src/test/test_loop.cpp"
        "./src/test/test_marshal.cpp"
        "./src/test/test_termination.cpp"
        "./src/test/test_verify.cpp"
        "./src/test/test_wto.cpp"
        )

set(COMMON_FLAGS -Wall -Wfatal-errors -DSIZEOF_VOID_P=8 -DSIZEOF_LONG=8)
set(RELEASE_FLAGS -O2 -flto -ffat-lto-objects)
set(DEBUG_FLAGS -O0 -g3 -fno-omit-frame-pointer)
set(SANITIZE_FLAGS -fsanitize=address -O1 -fno-omit-frame-pointer)
add_compile_definitions(ETL_NO_STL)

add_library(ebpfverifier ${LIB_SRC})

add_executable(check src/main/check.cpp src/main/linux_verifier.cpp)
add_executable(tests ${ALL_TEST})


target_compile_options(ebpfverifier PRIVATE ${COMMON_FLAGS})
# target_compile_options(ebpfverifier PRIVATE ${COMMON_FLAGS} -nostdinc -nostdlib)
target_compile_options(ebpfverifier PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>")
target_compile_options(ebpfverifier PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>")
target_compile_options(ebpfverifier PUBLIC "$<$<CONFIG:SANITIZE>:${SANITIZE_FLAGS}>")

set_property(TARGET ebpfverifier PROPERTY VS_PACKAGE_REFERENCES "Boost_1.75.5")

target_compile_options(check PRIVATE ${COMMON_FLAGS})
target_compile_options(check PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>")
target_compile_options(check PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>")
target_compile_options(check PUBLIC "$<$<CONFIG:SANITIZE>:${SANITIZE_FLAGS}>")
target_link_libraries(check PRIVATE ebpfverifier)

target_compile_options(tests PRIVATE ${COMMON_FLAGS})
target_compile_options(tests PUBLIC "$<$<CONFIG:DEBUG>:${DEBUG_FLAGS}>")
target_compile_options(tests PUBLIC "$<$<CONFIG:RELEASE>:${RELEASE_FLAGS}>")
target_compile_options(tests PUBLIC "$<$<CONFIG:SANITIZE>:${SANITIZE_FLAGS}>")
target_link_libraries(tests PRIVATE ebpfverifier)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(tests PRIVATE Threads::Threads)
target_compile_options(ebpfverifier PRIVATE ${COMMON_FLAGS})

install(TARGETS check DESTINATION bin)
install(TARGETS tests DESTINATION bin)
