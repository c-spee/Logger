cmake_minimum_required(VERSION 3.20)
project(logger)

include(FetchContent)

set(CMAKE_CXX_STANDARD 14)

if (TARGET_TYPE STREQUAL "target")
    add_subdirectory(logger)
    add_executable(log
            main.cpp
            )
    target_link_libraries(log logging)

elseif(TARGET_TYPE STREQUAL "test")
    add_subdirectory(logger)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
    )

    FetchContent_Declare(googlebenchmark
            GIT_REPOSITORY https://github.com/google/benchmark.git
            GIT_TAG master) # need master for benchmark::benchmark

    FetchContent_MakeAvailable(
            googletest
            googlebenchmark
    )


#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O3")

#set(CMAKE_BUILD_TYPE Release)

    add_executable(
            BM_Logger
            ${PROJECT_SOURCE_DIR}/benchmark/bm_main.cpp
    )

    target_link_libraries(
            BM_Logger
            benchmark
            logging
    )

    add_executable(
            UT_Logger
            ${PROJECT_SOURCE_DIR}/test/logger_test.cpp
    )

    target_link_libraries(
            UT_Logger
            gtest_main
            logging
    )

endif()