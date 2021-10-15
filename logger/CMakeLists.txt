cmake_minimum_required(VERSION 3.20)
project(logger)

set(CMAKE_CXX_STANDARD 14)

set(LOGGER_SOURCE_FILES
        src/Logger.cpp
        )

add_library(logging STATIC
        ${LOGGER_SOURCE_FILES}
        )

target_include_directories(logging PUBLIC
        inc)

