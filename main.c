#include <stdio.h>
#include <stdlib.h>

#include "apps.c"
#include "interface.c"

#define CONF_FILE "launcher.conf" // this is in your home directory, eg /home/john/launcher.conf

const char* concat_args(int argc, char** argv){
    unsigned long args_size = 0;
    for(int i=0 ; i<argc ; i++){ // count total length of args
        args_size += strlen(argv[i]);
    }

    char* out = (char*) calloc(args_size+argc, sizeof(char));
    for(int i=0 ; i<argc ; i++){
        strcat(out, argv[i]); // add arg to str
        strcat(out, " "); // add space
    }

    out[args_size+argc-1] = 0; // remove last char
    return out;
}

int main(int argc, char** argv) {
    char* conf_file = calloc(512, sizeof(char)); // alloc space for the conf file name
    sprintf(conf_file, "%s/%s", getenv("HOME"), CONF_FILE); // put together the conf file and the home directory

    init_file(conf_file, NULL); // init file if none exists with no content
    parse_apps(conf_file);

    if(argc > 1){ // if there are command line args
        char* to_launch = argv[1];
        for(int i=0 ; i<num_apps ; i++){ // iterate through the apps to check if any of the names are equal to the input (both lowercased)
            if(strcmp(to_lower(apps[i][0]), to_lower(to_launch)) == 0) {
                const char* args;
                if(argc > 2){ // if more args than just the name
                    args = concat_args(argc-2, &argv[2]); // collect the args together
                }else{
                    args = ""; // otherwise no args
                }

                run_app(i, args); // run the app in the seperate thread

                if(argc > 2){ // if memory is allocated
                    free((void*) args); // free it
                }
            }
        }
    }else{
        if(num_apps > 0){
            main_window(); // if no args, launch the curses TUI
        }else{
            printf("Please Add Programs To The File [%s]\n", conf_file);
        }
    }


    free(conf_file); // free up memory from the conf file
    free_apps(); // free the apps array

    return 0;
}
