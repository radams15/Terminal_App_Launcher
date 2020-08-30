//
// Created by rhys on 09/08/2020.
//

#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#define DELIMITER ":"
#define MAX_FILE_LEN 64

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

    if(strlen(out[0]) > apps.longest){
        apps.longest = (int) strlen(out[0]); // keep the largest display name so that the curses display can be just long enough
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
    char*** large_list = calloc(MAX_FILE_LEN, sizeof(char**)); // allocate a large array array, for at least MAX_LINES lines of config file.

    FILE * fp;

    char * line = NULL;
    size_t len = 0; // length of data
    ssize_t read; // length of data, -1 if no data (fail to read, e.g if file read finished)

    fp = fopen(file, "r");
    if (fp == NULL) { // file does not exist
        exit(1); // fail
    }

    apps.num = 0;

    for(int i=0 ; i < MAX_FILE_LEN ; i++){
        read = getline(&line, &len, fp); // read the line
        if(read == -1) { // no more data to read
            break; // end the iteration
        }
        if(line[0] == '\n' || line[0] == '#') { // if line empty or just commented, ignore the line
            continue;
        }

        if (line[read - 1] == '\n') {
            line[read - 1] = 0; // remove newline
        }

        large_list[apps.num] = parse_line(line); // parse the line and assign to the array
        apps.num++;
    }



    if(line){
        free(line); // free the array
    }

    apps.list = calloc(apps.num, sizeof(char**)); // allocate an appropriately sized array

    for(int i=0 ; i<apps.num ; i++){
        apps.list[i] = large_list[i]; // assign each of the actual apps to the new array
    }

    free(large_list); // free the large array

    fclose(fp);

    return apps;
}