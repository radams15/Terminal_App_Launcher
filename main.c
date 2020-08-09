#include <stdio.h>
#include <stdlib.h>

#include "apps.c"

#include "interface.c"

#define CONF_FILE "launcher.conf" // this is in your home directory, eg /home/john/launcher.conf

int main() {
    char* conf_file = calloc(512, sizeof(char));
    sprintf(conf_file, "%s/%s", getenv("HOME"), CONF_FILE);

    printf("File: %s", conf_file);

    apps = parse_apps(conf_file);
    main_window();

    free(conf_file);
    free_conf(apps);

    return 0;
}
