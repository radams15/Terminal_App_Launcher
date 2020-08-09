//
// Created by rhys on 09/08/2020.
//

#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define STR_SIZ 128

int __count_file_lines(const char* file){
    FILE *fp;
    int count = 0;
    int chr;

    fp = fopen(file, "r");

    if (fp == NULL){
        return -1;
    }

    for (chr = getc(fp); chr != EOF; chr = getc(fp)) {
        if (chr == '\n') {
            count++;
        }
    }

    fclose(fp);
    return count;
}

void free_conf(char*** array){
    for(int i=0 ; i<num_apps ; i++){
        for(int x=0 ; x<sizeof(array[i])/sizeof(char*) ; x++){
            free(array[i][x]);
        }
        free(array[i]);
    }
    free(array);
}

char** parse_line(char* line){
    char** out = calloc(2, sizeof(char*));
    out[0] = calloc(STR_SIZ, sizeof(char)); // temporary
    out[1] = calloc(STR_SIZ, sizeof(char));

    char* tok;
    tok = strtok(line, " "); // get name
    strcpy(out[0], tok);

    tok = strtok(NULL, ""); // get rest of string, command with extra args
    strcpy(out[1], tok);

    return out;
}

char*** parse_apps(const char* file){
    num_apps = __count_file_lines(file);
    char*** out = calloc(num_apps, sizeof(char**));

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(file, "r");
    if (fp == NULL) {
        return NULL;
    }

    for(int i=0 ; i < num_apps ; i++){
        read = getline(&line, &len, fp);
        if(line[read-1] == '\n') {
            line[read - 1] = 0; // remove newline
        }
        out[i] = parse_line(line);
    }

    if(line){
        free(line);
    }

    fclose(fp);

    return out;
}