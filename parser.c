//
// Created by rhys on 09/08/2020.
//

#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define STR_SIZ 512
#define DELIMITER ";"

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

int file_exists(const char* path){
    struct stat buffer;
    return stat (path, &buffer) == 0;
}

char* to_lower(char* s) {
    for(char *p=s; *p; p++) *p=tolower(*p);
    return s;
}

char** parse_line(char* line){
    char** out = calloc(2, sizeof(char*));
    out[0] = calloc(STR_SIZ, sizeof(char));
    out[1] = calloc(STR_SIZ, sizeof(char));

    char* tok;
    tok = strtok(line, DELIMITER); // get name
    strcpy(out[0], tok);

    tok = strtok(NULL, ""); // get rest of string, command with extra args
    strcpy(out[1], tok);

    if(strlen(out[0]) > longest_name){
        longest_name = strlen(out[0]);
    }

    return out;
}

void init_file(const char* path, const char* def){
    system("mkdir -p \"$HOME/launcher_logs\"");
    if(!file_exists(path)){
        FILE* fp;
        fp = fopen(path, "w");
        if(def != NULL){
            fprintf(fp, "%s\n", def);
        }
        fclose(fp);
    }
}


void parse_apps(const char* file){
    num_apps = __count_file_lines(file);
    apps = calloc(num_apps, sizeof(char**));

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(file, "r");
    if (fp == NULL) {
        return;
    }

    for(int i=0 ; i < num_apps ; i++){
        read = getline(&line, &len, fp);
        if(line[read-1] == '\n') {
            line[read - 1] = 0; // remove newline
        }
        apps[i] = parse_line(line);
    }

    if(line){
        free(line);
    }

    fclose(fp);
}