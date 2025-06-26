# CMake Guide for DockerPreprocessor

## Project Structure

```
DockerPreprocessor/
├── CMakeLists.txt         # Main CMake configuration
├── src/                   # Source files
├── include/              # Header files
├── docs/                 # Documentation
└── build/                # Build output
```

## Basic CMake Commands

### Project Configuration
```cmake
cmake_minimum_required(VERSION 3.10)
project(DockerPreprocessor VERSION 1.0.0)
```

### Output Directories
```cmake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
```

### Debug/Release Configuration
```cmake
# Set Debug/Release specific paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
```

## File Operations

### Working with Files
```cmake
# Create directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/config)

# Copy file
file(COPY ${CMAKE_SOURCE_DIR}/config/default.ini 
     DESTINATION ${CMAKE_BINARY_DIR}/config)

# Write content to file
file(WRITE ${CMAKE_BINARY_DIR}/config/version.txt "${PROJECT_VERSION}")

# Read file content
file(READ "input.txt" FILE_CONTENT)

# Find files matching pattern
file(GLOB CONFIG_FILES "config/*.ini")
```

### Configure Files
```cmake
configure_file(
    "${PROJECT_SOURCE_DIR}/config/config.template.ini"
    "${CMAKE_BINARY_DIR}/config/config.ini"
    @ONLY
)
```

## Custom Commands and Targets

### Custom Commands
```cmake
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/config/config.ini
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/config/config.template.ini
            ${CMAKE_BINARY_DIR}/config/config.ini
    DEPENDS ${CMAKE_SOURCE_DIR}/config/config.template.ini
)
```

### Custom Targets
```cmake
add_custom_target(generate_config
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/config
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
```

### Execute Process
```cmake
execute_process(
    COMMAND git rev-parse --short HEAD
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
```

## Building the Project

### Command Line Build
```bash
# Create and enter build directory
mkdir build && cd build

# Configure project
cmake ..

# Build project
cmake --build .

# Specify build type
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Clean build
make clean
```

### Important Variables
- `CMAKE_SOURCE_DIR`: Root of the source tree
- `CMAKE_BINARY_DIR`: Root of the build tree
- `PROJECT_NAME`: Name of the current project
- `CMAKE_BUILD_TYPE`: Build type (Debug/Release)
- `PROJECT_VERSION`: Project version number

## Tips and Best Practices

1. Always use out-of-source builds (build in separate directory)
2. Set default build type if none specified
3. Use consistent directory structure
4. Use version numbering
5. Document CMake configuration changes

## Troubleshooting

### Common Issues

1. **CMake can't find files**
   - Use absolute paths with CMake variables
   - Double-check file paths relative to CMakeLists.txt

2. **Build type not set**
   ```cmake
   if(NOT CMAKE_BUILD_TYPE)
       set(CMAKE_BUILD_TYPE Release)
   endif()
   ```

3. **Library linking issues**
   ```cmake
   target_link_libraries(${PROJECT_NAME} PRIVATE required_lib)
   ```

### Debugging CMake

1. Print variables:
   ```cmake
   message(STATUS "Variable value: ${VARIABLE_NAME}")
   ```

2. Enable verbose output:
   ```bash
   make VERBOSE=1
   ```

## Additional Resources

- [Official CMake Documentation](https://cmake.org/documentation/)
- [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- [Modern CMake Practices](https://cliutils.gitlab.io/modern-cmake/)
