//
// Created by Tom Otero on 6/26/25.
//

#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <stdbool.h>

typedef struct {
    bool verbose_logging;
    char log_level[32];
    char log_file[256];
}Config;

Config* config_new(void);
void config_free(Config* config);
bool config_load(Config* config, const char* filename);
const char* config_get_string(Config* config, const char* key);
bool config_get_bool(Config* config, const char* key);
void config_set_defaults(Config* config);


#endif //CONFIG_PARSER_H
