#include "my_boy.h"
#include "curses.h"
#include <my_map.h>

my_boy::my_boy(int spx, int spy) : x(spx), y(spy) 
{
    xl = x;
    yl = y;
}

void my_boy::move_boy(char** map) {

    init_color(257, 46, 139, 87); // фон
    //init_color(258, 206, 240, 199); // деревья
    init_pair(7, COLOR_BLUE, 257);

    attron(COLOR_PAIR(7));
    
    

    if (map[y][x] == ' ') {
        move(y, x);
        printw("0");
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

