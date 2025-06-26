//
// Created by Tom Otero on 6/26/25.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

// Log levels
typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
} LogLevel;

// Logger configuration
typedef struct {
    LogLevel level;         // Minimum log level to display
    FILE* output;           // Output file (stdout, stderr, or custom file)
    int use_colors;         // Whether to use ANSI colors in output
    int show_timestamp;     // Whether to include timestamps
} LoggerConfig;

// Initialize the logger with default configuration
void logger_init(void);

// Configure the logger with custom settings
void logger_configure(LoggerConfig config);

// Log functions for different levels
void log_debug(const char* format, ...);
void log_info(const char* format, ...);
void log_warn(const char* format, ...);
void log_error(const char* format, ...);
void log_fatal(const char* format, ...);

// Set the minimum log level
void logger_set_level(LogLevel level);

// Set output destination
void logger_set_output(FILE* output);

// Enable/disable colors
void logger_use_colors(int use_colors);

// Enable/disable timestamps
void logger_show_timestamp(int show_timestamp);

// Clean up logger resources
void logger_cleanup(void);

#endif //LOGGER_H
