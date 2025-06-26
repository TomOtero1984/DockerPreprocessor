# Skip top-level project() definition if already included from the main project
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    cmake_minimum_required(VERSION 3.10)
    project(logger_lib VERSION 1.0.0 LANGUAGES C)
endif()

add_library(logger STATIC
        src/logger.c
)

target_include_directories(logger PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(TARGETS logger DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)
