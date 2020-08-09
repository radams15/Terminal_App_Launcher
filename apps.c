//
// Created by rhys on 09/08/2020.
//

char*** apps;
int num_apps;

#include "parser.c"

void print_apps(){
    for(int i=0 ; i<num_apps ; i++){
        printf("%i: ", i);
        printf("%s => %s\n", apps[i][0], apps[i][1]);
    }
}

void run_app(int id){
    if(id >= 0 && id < num_apps){
        char* command = calloc(256, sizeof(char));

        sprintf(command, "%s &> /dev/null", apps[id][1]);

        //printf("%s\n", command);
        system(command);

        free(command);

    }
}