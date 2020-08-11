#include <stdio.h>
#include <stdlib.h>

#include "apps.c"
#include "interface.c"

#define CONF_FILE "launcher.conf" // this is in your home directory, eg /home/john/launcher.conf

int main(int argc, char** argv) {
    char* conf_file = calloc(512, sizeof(char)); // alloc space for the conf file name
    sprintf(conf_file, "%s/%s", getenv("HOME"), CONF_FILE); // put together the conf file and the home directory

    parse_apps(conf_file);
    free(conf_file); // free up memory from the conf file

    if(argc > 1){ // if there are command line args
        char* to_launch = argv[1];
        for(int i=0 ; i<num_apps ; i++){ // iterate through the apps to check if any of the names are equal to the input (both lowercased)
            if(strcmp(to_lower(apps[i][0]), to_lower(to_launch)) == 0) {
                run_app(i);
            }
        }
    }else{
        main_window(); // if no args, launch the curses TUI
    }


    free_apps(); // free the apps array
    return 0;
}
