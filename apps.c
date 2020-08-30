//
// Created by rhys on 09/08/2020.
//

#include <unistd.h>
#include <string.h>

struct Apps{
    char*** list;
    int num;
    int longest;
};
struct Apps apps;

void free_apps(){
    for(int i=0 ; i<apps.num ; i++){ // iterate over the top char***
        free(apps.list[i]); // free the char** container
    }
    free(apps.list); // free the char*** container
}

const char* mk_command_args(int id, const char* args){
    const char* template = "%s %s > \"$HOME/launcher_logs/%s_log.txt\" 2>&1";

    unsigned long command_size = strlen(template) - 6 + strlen(apps.list[id][0]) + strlen(apps.list[id][1]) + strlen(args); // calculate the size of string needed.
    //The size of all the parts subtracting the size of the formatting characters

    char *command = calloc(command_size, sizeof(char));
    sprintf(command, template, apps.list[id][1], args, apps.list[id][0]); // append to the command to make it silent

    return command;
}

void run_app(int id, const char* args){
    if(id >= 0 && id < apps.num){
        if(fork() == 0) { // fork into new process
            const char *command = mk_command_args(id, args); // make the command

            system(command); //run the command!

            free((void*) command); // free the command memory

            free_apps(); // free the app_array array as we are in a forked process, we need to clean up here as well

            exit(0);

        }

    }
}

#include "parser.c"