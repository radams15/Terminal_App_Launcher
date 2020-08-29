//
// Created by rhys on 29/08/2020.
//

#include <gtk/gtk.h>
#include <math.h>

#define NAME "org.rhys.launcher"
#define WINDOW_NAME "Launcher"

#define TABLE_ROWS 2

#define DEFAULT_SIZE 200, 200

void button_callback(GtkWidget *widget, gpointer data){
    int id = GPOINTER_TO_INT(data);
    run_app(id, "");
}

void add_apps(GtkWidget* window){
    int cols = ceil((double)num_apps / (double)TABLE_ROWS);

    GtkWidget* grid = gtk_grid_new();

    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    int app=0;
    for(unsigned int i=0 ; i<num_apps ; i++){
        for(unsigned int j=0 ; j < TABLE_ROWS ; j++) {
            if(app < num_apps) {
                GtkWidget *button = gtk_button_new_with_label(apps[app][0]);
                g_signal_connect(button, "clicked", G_CALLBACK(button_callback), GINT_TO_POINTER(app)); // set the callback, passing the app id

                gtk_grid_attach(GTK_GRID(grid), button, j, i, 1, 1);

                printf("Adding %d to (%d, %d)\n", app, i, j);

                app++;
            }
        }
    }

    gtk_container_add(GTK_CONTAINER(window), grid);
}

void gui_activate(GtkApplication* app, gpointer user_data){
    GtkWidget* window = gtk_application_window_new (app); // init window

    gtk_window_set_title (GTK_WINDOW(window), WINDOW_NAME);
    gtk_window_set_default_size(GTK_WINDOW(window), DEFAULT_SIZE); // set default height

    add_apps(window); // add the app buttons

    gtk_widget_show_all(window); // show window
}

int gui_main(){
    GtkApplication *app = gtk_application_new(NAME, G_APPLICATION_FLAGS_NONE); // create the window

    g_signal_connect(app, "activate", G_CALLBACK (gui_activate), NULL); // when activated, fill the window contents

    int status = g_application_run(G_APPLICATION(app), 0, NULL); // run the app with no args, collect status

    g_object_unref(app);

    return status;
}