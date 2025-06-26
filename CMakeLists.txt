cmake_minimum_required(VERSION 3.10)
project(DockerPreprocessor VERSION 1.0.0)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ✅ Corrected paths to the libraries
add_subdirectory(lib/logger)
add_subdirectory(lib/config)

# Main application sources
add_executable(${PROJECT_NAME} src/main.c)

# Link libraries to main executable
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    logger
    config_parser
)

# Include library headers
target_include_directories(${PROJECT_NAME}
    PRIVATE
    lib/logger/include
    lib/config/include
)

# Documentation target
add_custom_target(docs
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/docs
    COMMENT "Ensuring docs directory exists"
)

# Install targets
install(TARGETS ${PROJECT_NAME} DESTINATION bin)