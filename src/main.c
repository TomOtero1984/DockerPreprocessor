#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#include "config_parser.h"
//#include "logger.h"

#define MAX_ENV_VARS 128

typedef struct {
    char *key;
    char *value;
} EnvVar;

typedef struct {
    EnvVar vars[MAX_ENV_VARS];
    size_t count;
} EnvMap;

int load_env_file(const char *path, EnvMap *map) {
    FILE *file = fopen(path, "r");
    if (!file) return 0;

    char line[256];
    map->count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (line[0] == '#' || line[0] == '\n') continue;

        char *eq = strchr(line, '=');
        if (!eq) continue;

        *eq = '\0';
        char *key = strtok(line, " \t\r\n");
        char *val = strtok(eq + 1, " \t\r\n");

        if (key && val && map->count < MAX_ENV_VARS) {
            map->vars[map->count].key = strdup(key);
            map->vars[map->count].value = strdup(val);
            map->count++;
        }
    }

    fclose(file);
    return 1;
}


char *replace_vars(const char *line, const EnvMap *envs) {
    static char buffer[1024];
    size_t i = 0;

    while (*line && i < sizeof(buffer) - 1) {
        if (*line == '$' && *(line + 1) == '{') {
            const char *start = line + 2;
            const char *end = strchr(start, '}');
            if (!end) break;

            char key[64] = {0};
            strncpy(key, start, end - start);

            const char *replacement = getenv(key); // fallback to system env
            for (size_t j = 0; j < envs->count; j++) {
                if (strcmp(envs->vars[j].key, key) == 0) {
                    replacement = envs->vars[j].value;
                    break;
                }
            }

            if (replacement) {
                i += snprintf(buffer + i, sizeof(buffer) - i, "%s", replacement);
            }

            line = end + 1;
        } else {
            buffer[i++] = *line++;
        }
    }

    buffer[i] = '\0';
    return buffer;
}


void process_dockerfile(const char *input_path, const char *output_path, const EnvMap *envs) {
    FILE *in = fopen(input_path, "r");
    FILE *out = fopen(output_path, "w");

    if (!in || !out) {
        fprintf(stderr, "Error opening files\n");
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), in)) {
        char *replaced = replace_vars(line, envs);
        fprintf(out, "%s\n", replaced);
    }

    fclose(in);
    fclose(out);
}

/*
void __config() {

    Config *config = config_new();
    if (!config_load(config, "config.ini")) {
        printf("Failed to load configuration\n");
        config_free(config);
        return 1;
    }

    // Use the configuration
    if (config->verbose_logging) {
        printf("Verbose logging is enabled\n");
        printf("Log level: %s\n", config->log_level);
        printf("Log file: %s\n", config->log_file);
    }


    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

   config_free(config);
}
*/


int main(int argc, char* argv[]) {
    EnvMap envs;
    load_env_file(".env", &envs);
    process_dockerfile("Dockerfile.in", "Dockerfile", &envs);
    return 0;
}