//
// Created by rhys on 29/08/2020.
//

#include <gtk/gtk.h>

#define NAME "org.rhys.launcher"
#define WINDOW_NAME "Launcher"

#define TABLE_ROWS 2

#define DEFAULT_SIZE 200, 200

void button_callback(GtkWidget *widget, gpointer data){
    int id = GPOINTER_TO_INT(data);
    run_app(id, "");
}

void add_apps(GtkWidget* window){
    GtkWidget* grid = gtk_grid_new(); // create a new GtkGrid

    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE); // make the buttons fill all the space
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    int app_id=0;
    for(unsigned int cols=0 ; cols < num_apps ; cols++){
        for(unsigned int rows=0 ; rows < TABLE_ROWS ; rows++) {
            if(app_id < num_apps) { // don't want to go over the amount of app_array we have, as it is possible if the number of app_array is not divisible by TABLE_ROWS
                GtkWidget *button = gtk_button_new_with_label(app_array[app_id][0]);
                g_signal_connect(button, "clicked", G_CALLBACK(button_callback), GINT_TO_POINTER(app_id)); // set the callback, passing the app_id id

                gtk_grid_attach(GTK_GRID(grid), button, rows, cols, 1, 1); // add the button to the grid, at (rows, cols), at size (1,1)

                app_id++; // increment the app_id id
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