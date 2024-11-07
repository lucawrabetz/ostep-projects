#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAGENTA     "\033[35m"
#define RESET   "\033[0m"

size_t BUF_SIZE = 500;

void grep_line(char* line, char* str) {
    size_t n = strlen(line);
    size_t m = strlen(str);
    if (n < m) {
        return;
    }

    size_t format_n = 2*n;
    char formatted[format_n];
    char* next = line;
    size_t written = 0;
    for (int j = 0; j < n-m; ++j) {
        if (strncmp(line+j, str, m) == 0) {
            size_t previous_n = line + j - next;
            strlcat(formatted + written, next, sizeof(formatted));
            written += previous_n;

            size_t color_n = strlen(MAGENTA);
            strlcat(formatted + written, MAGENTA, sizeof(formatted));
            written += color_n;

            strlcat(formatted + written, line, sizeof(formatted));
            written += m;

            size_t reset_n = strlen(RESET);
            strlcat(formatted + written, RESET, sizeof(formatted));
            written += reset_n;
        }
    }

    if (written > 0) {
        if (written < n) {
            strlcat(formatted + written, line + n - written, n - written);
        }
        printf("%s", formatted);
    }

    return;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("wgrep: searchterm [file ...]");
        exit(1);
    }

    char* buffer = (char *) malloc(BUF_SIZE * sizeof(char));
    size_t capacity = BUF_SIZE;

    char* searchterm = argv[1];

    for (int i = 2; i < argc; ++i) {
        FILE* f = fopen(argv[i], "r");
        if (f == NULL) {
            char* errorstring;
            asprintf(&errorstring, "%s: cannot open file %s.", argv[0], argv[i]);
            printf("%s", errorstring);
            exit(1);
        }
        while (getline(&buffer, &capacity, f) > 0) {
            grep_line(buffer, searchterm);
        }
    }

    free(buffer);
    exit(0);
}
