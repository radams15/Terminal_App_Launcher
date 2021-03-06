#include <stdio.h>
#include <stdlib.h>

#include "apps.c"
#include "TUI.c"
#include "GUI.c"

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
    char* home = getenv("HOME");
    char* conf_file = calloc(strlen(home)+strlen(CONF_FILE)+1, sizeof(char)); // alloc space for the conf file name (size of strings plus 1 for the '/')
    sprintf(conf_file, "%s/%s", home, CONF_FILE); // put together the conf file and the home directory

    init_file(conf_file, NULL); // init file if none exists with no content
    parse_apps(conf_file);

    if(argc > 1){ // if there are command line args
        char* arg_1 = argv[1];

        if(strcmp(arg_1, "apps") == 0){
            for(int i=0 ; i<apps.num ; i++){
                printf("%s\n", apps.list[i][0]);
            }
        }else {
            if (strcmp(to_lower(arg_1), "gui") == 0) { // wants a gtk gui
                gui_main();
            }else {
                int found = FALSE;
                for (int i = 0; i < apps.num; i++) { // iterate through the app_array to check if any of the names are equal to the input (both lowercased)
                    if (strcmp(to_lower(apps.list[i][0]), to_lower(arg_1)) == 0) {
                        const char *args;
                        if (argc > 2) { // if more args than just the name
                            args = concat_args(argc - 2, &argv[2]); // collect the args together
                        } else {
                            args = ""; // otherwise no args
                        }

                        run_app(i, args); // run the app in the seperate thread

                        if (argc > 2) { // if memory is allocated
                            free((void *) args); // free it
                        }

                        found = TRUE;
                    }
                }
                if (!found) {
                    printf("No App Named %s\n", arg_1);
                }
            }
        }
    }else{ // no args
        if(apps.num > 0){
            tui_main(); // has app_array, run TUI
        }else{
            printf("Please Add Programs To The File [%s]\n", conf_file); // tell the user there are no app_array, and where to put them
        }
    }


    free(conf_file); // free up memory from the conf file
    free_apps(); // free the app_array array

    return 0;
}
