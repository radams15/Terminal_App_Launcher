#include <stdio.h>

#include "apps.c"

#include "interface.c"

#define CONF_FILE "../launcher.conf"

int main() {
    apps = parse_apps(CONF_FILE);
    main_window();
    free_conf(apps);

    return 0;
}
