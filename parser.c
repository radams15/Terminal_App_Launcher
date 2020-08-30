//
// Created by rhys on 09/08/2020.
//

#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define STR_SIZ 512
#define DELIMITER ":"

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

    char* tok;
    tok = strtok(line, DELIMITER); // get name
    out[0] = calloc(strlen(tok), sizeof(char));
    strcpy(out[0], tok);

    tok = strtok(NULL, ""); // get rest of string, command with extra args
    out[1] = calloc(strlen(tok), sizeof(char));
    strcpy(out[1], tok);

    if(strlen(out[0]) > longest_name){
        longest_name = (int) strlen(out[0]); // keep the largest display name so that the curses display can be just long enough
    }

    return out;
}

void init_file(const char* path, const char* def){
    system("mkdir -p \"$HOME/launcher_logs\""); // make the logs directory
    if(!file_exists(path)){ // if file does not exist
        FILE* fp; // make the file
        fp = fopen(path, "w");
        if(def != NULL){ // if there is a default content set
            fprintf(fp, "%s\n", def); // write the default data
        }
        fclose(fp);
    }
}


struct Apps parse_apps(const char* file){
    num_apps = __count_file_lines(file); // count the lines in the file
    app_array = calloc(num_apps, sizeof(char**)); // allocate the app_array array for all the file lines

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(file, "r");
    if (fp == NULL) { // file does not exist
        return; // fail
    }

    for(int i=0 ; i < num_apps ; i++){
        read = getline(&line, &len, fp); // read the line
        if(line[read-1] == '\n') {
            line[read - 1] = 0; // remove newline
        }
        app_array[i] = parse_line(line); // parse the line and assign to the array
    }

    if(line){
        free(line); // free the array
    }

    fclose(fp);
}