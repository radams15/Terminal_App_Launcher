//
// Created by rhys on 09/08/2020.
//

#include <ncurses.h>

#define KEY_ESC 27

#define BOX_BORDER 1

void tui_main(){
    WINDOW *w;
    int app_id;
    int key;

    initscr(); // initialise the ncurses screen

    w = newwin(num_apps+2, longest_name+3, BOX_BORDER, BOX_BORDER); // make the box with the same height as app_array and the same width as the largest app
    box(w, 0, 0); // make w a bordered box

    for(app_id=0 ; app_id < num_apps ; app_id++){
        if(app_id == 0){
            wattron(w, A_STANDOUT); // highlight the first app
        }else{
            wattroff(w, A_STANDOUT); // disable highlighting
        }
        mvwprintw(w, app_id + 1, 2, "%s", app_array[app_id][0]); // write the app name
    }
    app_id=0;

    noecho();
    keypad(w, TRUE);
    curs_set(0);

    while((key = wgetch(w)) != KEY_ESC){ // keep getting keyboard chars until it is the Escape Key

        mvwprintw(w, app_id + 1, 2, "%s", app_array[app_id][0] );

        switch(key) {
            case KEY_UP:
                app_id--;
                app_id = app_id < 0 ? num_apps - 1 : app_id; // increment app_id but don't go over the highest index
                break;

            case KEY_DOWN:
                app_id++;
                app_id = app_id >= num_apps ? 0 : app_id; // decrement app_id but don't go under 0
                break;

            case 10:
                run_app(app_id, ""); // run app app_id with no args

            default: break;
        }

        wattron(w, A_STANDOUT); // turn on highlighting
        mvwprintw(w, app_id + 1, 2, "%s", app_array[app_id][0]); // move to app_id and write the app name again as highlighted
        wattroff(w, A_STANDOUT); // turn off highlighting
    }

    delwin(w);
    endwin();
}