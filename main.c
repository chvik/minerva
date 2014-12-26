#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "latin.h"

#define PROMPT "?"

void trimstr(char *str, char *outbuffer, size_t buffer_len)
{
    char *start = str;
    char *end;
    size_t trimmed_len;
    size_t out_len;

    while (isspace(*start)) {
        start++;
    }

    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) {
        end--;
    }

    trimmed_len = end - start + 1;
    out_len = trimmed_len < buffer_len ? trimmed_len : buffer_len - 1;
    memcpy(outbuffer, start, out_len);
    outbuffer[out_len] = 0;
}

void process_query(char *word)
{
    lat_res **lres;
    lat_res **hres;
    int i;
    int j;

    lres = latsearch(word);
    if (lres[0]) {
        for (i = 0; lres[i]; ++i) {
            lat_res *r = lres[i];
            printf("%s : %s\n", r->form, r->meaning);
            for (j = 0; r->det[j]; ++j) {
                printf("  %s\n", r->det[j]);
            }
        }
    }
    hres = husearch(word);
    if (hres[0]) {
        for (i = 0; hres[i]; ++i) {
            lat_res *r = hres[i];
            printf("%s %s\n", r->form, r->meaning);
        }
    }
}

int main(int argc, char **argv)
{
    char *input_line;
    size_t input_len;
    char trimmed_line[1024];

    while (1) {
        printf("%s ", PROMPT);
        ssize_t input_size = getline(&input_line, &input_len, stdin);
        if (input_size <= 0) {
            break;
        }
        trimstr(input_line, trimmed_line, sizeof(trimmed_line));

        if (strlen(trimmed_line) == 0) {
            break;
        }

        process_query(trimmed_line);
    }

    return 0;
}

