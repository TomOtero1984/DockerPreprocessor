//
// Created by Tom Otero on 6/26/25.
//

#include "config_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256
#define MAX_KEY_LENGTH 64
#define MAX_VALUE_LENGTH 256

Config* config_new(void) {
    Config* config = (Config*)malloc(sizeof(Config));
    if (config != NULL) {
        config_set_defaults(config);
    }
    return config;
}

void config_free(Config* config) {
    if (config != NULL) {
        free(config);
    }
}

void config_set_defaults(Config* config) {
    if (config != NULL) {
        config->verbose_logging = false;
        strncpy(config->log_level, "INFO", sizeof(config->log_level));
        strncpy(config->log_file, "app.log", sizeof(config->log_file));
    }
}

static void trim(char* str) {
    char* start = str;
    char* end = str + strlen(str) - 1;

    while (isspace(*start)) start++;
    while (end > start && isspace(*end)) end--;

    size_t len = end - start +1;
    memmove(str, start, len);
    str[len] = '\0';
}

bool config_load(Config* config, const char* filename) {
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: Cannot open config file %s\n", filename);
        return false;
    }

    char line[MAX_LINE_LENGTH];
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (line[0] == '#' || line[0] == '\n') continue;

        char* equals = strchr(line, '=');
        if (equals != NULL) {
            size_t key_len = equals - line;
            if (key_len >= MAX_KEY_LENGTH) key_len = MAX_KEY_LENGTH - 1;

            strncpy(key, line, key_len);
            key[key_len] = '\0';
            strncpy(value, equals + 1, MAX_VALUE_LENGTH - 1);
            value[MAX_VALUE_LENGTH - 1] = '\0';

            // Remove newline if present
            char* newline = strchr(value, '\n');
            if (newline != NULL) *newline = '\0';

            // Trim whitespace
            trim(key);
            trim(value);

            if (strcmp(key, "verbose_logging") == 0) {
                config->verbose_logging = (strcmp(value, "true") == 0 || strcmp(value, "1") == 0);
            }
            else if (strcmp(key, "log_level") == 0) {
                strncpy(config->log_level, value, sizeof(config->log_level) - 1);
            }
            else if (strcmp(key, "log_file") == 0) {
                strncpy(config->log_file, value, sizeof(config->log_file) - 1);
            }

        }

    }

    fclose(fp);
    return true;
}

// Get string value from config
const char* config_get_string(Config* config, const char* key) {
    if (strcmp(key, "log_level") == 0) return config->log_level;
    if (strcmp(key, "log_file") == 0) return config->log_file;
    return NULL;
}

// Get boolean value from config
bool config_get_bool(Config* config, const char* key) {
    if (strcmp(key, "verbose_logging") == 0) return config->verbose_logging;
    return false;
}
