//
// Created by rhys on 09/08/2020.
//

#include <unistd.h>

#define COMMAND_SIZ 512

char*** apps;
int num_apps;
int longest_name;


void free_apps(){
    for(int i=0 ; i<num_apps ; i++){ // iterate over the top char***
        for(int x=0 ; x<sizeof(apps[i])/sizeof(char*) ; x++){ // iterate over the char**
            free(apps[i][x]); // free the char*
        }
        free(apps[i]); // free the char** container
    }
    free(apps); // free the char*** container
}

void run_app(int id){
    if(id >= 0 && id < num_apps){
        if(fork() == 0) { // fork into new process
            char *command = calloc(COMMAND_SIZ, sizeof(char));
            sprintf(command, "mkdir -p \"$HOME/launcher_logs\" ; %s > \"$HOME/launcher_logs/%s_log.txt\" 2>&1", apps[id][1], apps[id][0]); // append to the command to make it silent
            //printf("%s\n", command);

            system(command); //run the command!

            free(command); // free the command char*

            free_apps(); // free the apps array as we are in a forked process, we need to clean up here as well

            exit(0);

        }

    }
}

#include "parser.c"