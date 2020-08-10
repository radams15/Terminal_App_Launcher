//
// Created by rhys on 09/08/2020.
//

#include <ncurses.h>

#define KEY_ESC 27

#define BOX_BORDER 1

void main_window(){
    WINDOW *w;
    int i;
    int ch;

    initscr();

    w = newwin(num_apps+2, longest_name+3, BOX_BORDER, BOX_BORDER);
    box(w, 0, 0);

    for(i=0 ; i<num_apps ; i++){
        if(i==0){
            wattron(w, A_STANDOUT);
        }else{
            wattroff(w, A_STANDOUT);
        }
        mvwprintw(w, i+1, 2, "%s", apps[i][0]);
    }
    i=0;

    noecho();
    keypad(w, TRUE);
    curs_set(0);

    while(( ch = wgetch(w)) != KEY_ESC){

        mvwprintw( w, i+1, 2, "%s", apps[i][0] );

        switch( ch ) {
            case KEY_UP:
                i--;
                i = i<0 ? num_apps-1 : i;
                break;

            case KEY_DOWN:
                i++;
                i = i>=num_apps ? 0 : i;
                break;

            case 10:
                run_app(i);

            default: break;
        }

        wattron(w, A_STANDOUT);
        mvwprintw( w, i+1, 2, "%s", apps[i][0]);
        wattroff(w, A_STANDOUT);
    }

    delwin(w);
    endwin();
}