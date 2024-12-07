#include "my_boy.h"
#include "curses.h"
#include <my_map.h>

my_boy::my_boy(int spx, int spy) : x(spx), y(spy) 
{
    xl = x;
    yl = y;
}

void my_boy::move_boy(char** map) {

    attron(COLOR_PAIR(7));
    
    if (map[y][x] == ' ') {
        move(y, x);
        printw("0");
    }

    else if (map[y][x] == '.') {
        move(y, x);
        count_of_m++;
        printw("0");
        map[y][x] = ' ';
    }
    else {

        x = xl;
        y = yl;
        move(y, x);
        printw("0");

    }

    xl = x;
    yl = y;
    attroff(COLOR_PAIR(7));
    
}

