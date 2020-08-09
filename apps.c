//
// Created by rhys on 09/08/2020.
//

#include <unistd.h>

char*** apps;
int num_apps;

#define COMMAND_SIZ 512

#include "parser.c"

void print_apps(){
    for(int i=0 ; i<num_apps ; i++){
        printf("%i: ", i);
        printf("%s => %s\n", apps[i][0], apps[i][1]);
    }
}

void free_apps(){
    free_conf(apps);
}

void run_app(int id){
    if(id >= 0 && id < num_apps){
        if(fork() == 0) {
            char *command = calloc(COMMAND_SIZ, sizeof(char));

            sprintf(command, "%s > /dev/null 2>&1", apps[id][1]); // append to the command to make it silent

            system(command);

            free(command);

            free_apps();

            exit(0);

        }

    }
}