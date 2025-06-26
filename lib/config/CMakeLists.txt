# Skip top-level project() definition if already included from the main project
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    cmake_minimum_required(VERSION 3.10)
    project(config_lib VERSION 1.0.0 LANGUAGES C)
endif()

add_library(config_parser STATIC
    src/config_parser.c
)

target_include_directories(config_parser PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

install(TARGETS config_parser DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)