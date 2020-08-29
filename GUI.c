//
// Created by rhys on 29/08/2020.
//

#include <gtk/gtk.h>

#define NAME "org.rhys.launcher"
#define WINDOW_NAME "Launcher"

#define DEFAULT_SIZE 200, 200

void button_callback(GtkWidget *widget, gpointer data){
    int id = GPOINTER_TO_INT(data);
    run_app(id, "");
}

void add_apps(GtkWidget* window){
    GtkWidget* button_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL); // create a button box
    gtk_container_add (GTK_CONTAINER (window), button_box);

    for(unsigned int i=0 ; i<num_apps ; i++){
        GtkWidget* button = gtk_button_new_with_label(apps[i][0]);
        g_signal_connect(button, "clicked", G_CALLBACK (button_callback), GINT_TO_POINTER(i)); // set the callback, passing the app id
        gtk_container_add(GTK_CONTAINER(button_box), button); // add it to the window
    }
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