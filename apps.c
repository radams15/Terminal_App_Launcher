//
// Created by rhys on 09/08/2020.
//

#include <unistd.h>
#include <string.h>

#define COMMAND_SIZ 512

char*** apps;
int num_apps;
int longest_name;


void free_apps(){
    for(int i=0 ; i<num_apps ; i++){ // iterate over the top char***
        /*for(int x=0 ; num_apps ; x++){ // iterate over the char**
            free(apps[i][x]); // free the char*
        }*/
        free(apps[i]); // free the char** container
    }
    free(apps); // free the char*** container
}

const char* mk_command_args(int id, const char* args){
    const char* template = "mkdir -p \"$HOME/launcher_logs\" ; %s %s > \"$HOME/launcher_logs/%s_log.txt\" 2>&1";
    unsigned long command_size = strlen(template)-4 + strlen(apps[id][0]) + strlen(apps[id][1]) + strlen(args);
    char *command = calloc(command_size, sizeof(char));
    sprintf(command, template, apps[id][1], args, apps[id][0]); // append to the command to make it silent

    return command;
}

void run_app(int id, const char* args){
    if(id >= 0 && id < num_apps){
        if(fork() == 0) { // fork into new process
            const char *command = mk_command_args(id, args);

            system(command); //run the command!

            free((void*) command); // free the command char*

            free_apps(); // free the apps array as we are in a forked process, we need to clean up here as well

            exit(0);

        }

    }
}

#include "parser.c"