#include "my_boy.h"
#include "curses.h"
#include <my_map.h>

my_boy::my_boy(int spx, int spy) : x(spx), y(spy) 
{
    xl = x;
    yl = y;
}

void my_boy::move_boy(char** map) {


    
    if (map[y][x] == ' ' || map[y][x] == '1' || map[y][x] == 'ÿ') {
        if (map[y][x] == ' ') {
            attron(COLOR_PAIR(7));
            move(y, x);
            printw("0");
            attroff(COLOR_PAIR(7));
        }
        else if (map[y][x] == '1'){
            attron(COLOR_PAIR(16));
            move(y, x);
            printw("0");
            attroff(COLOR_PAIR(16));
        }
        else {
            attron(COLOR_PAIR(18));
            move(y, x);
            printw("0");
            attroff(COLOR_PAIR(18));
        }
    }

    else if (map[y][x] == '.') {

        attron(COLOR_PAIR(7));
        move(y, x);
        count_of_m++;
        printw("0");
        map[y][x] = ' ';
        attroff(COLOR_PAIR(7));
    }
    else {

        x = xl;
        y = yl;
        
        if (map[y][x] == ' ') {
            attron(COLOR_PAIR(7));
            move(y, x);
            printw("0");
            attroff(COLOR_PAIR(7));
        }
        else {
            attron(COLOR_PAIR(16));
            move(y, x);
            printw("0");
            attroff(COLOR_PAIR(16));
        }

    }

    xl = x;
    yl = y;
   
    
}

