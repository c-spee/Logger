cmake_minimum_required(VERSION 3.20)
project(logger)

include(/home/cspirido/parasoft_eclipse/cpptest/integration/cmake/cpptest-project.cmake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-pthread")

set(LOGGER_SOURCE_FILES
        src/Logger.cpp
        inc/IOutput.h
        inc/ConsoleOutput.h
        inc/FileOutput.h
        inc/NetworkOutput.h
        )

add_library(logging STATIC
        ${LOGGER_SOURCE_FILES}
        )

target_include_directories(logging PUBLIC
        inc)

cpptest_add_executable(cpptest_logging
        CPPTEST_COMPILER_ID gcc_9-64
        SOURCES ${LOGGER_SOURCE_FILES})

target_include_directories(cpptest_logging PUBLIC
        inc)

