#include <stdio.h>
#include <stdlib.h>

#include "apps.c"

#include "interface.c"

#define CONF_FILE "launcher.conf" // this is in your home directory, eg /home/john/launcher.conf

int main() {
    char* conf_file = calloc(512, sizeof(char)); // alloc space for the conf file name
    sprintf(conf_file, "%s/%s", getenv("HOME"), CONF_FILE); // put together the conf file and the home directory

    parse_apps(conf_file);
    free(conf_file);

    print_apps();
    //main_window();


    free_apps();
    return 0;
}
