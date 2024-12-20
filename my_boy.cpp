#include "my_boy.h"
#include "curses.h"
#include <my_map.h>
#include "ivent_thing.h"

my_boy::my_boy(int spx, int spy) : x(spx), y(spy) 
{
    xl = x;
    yl = y;
}

void my_boy::move_boy(char** map) {

    if (map[y][x] == ' ' || map[y][x] == '1' || map[y][x] == 'я') {
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

    else if (map[y][x] == '.' || map[y][x] == (char)133) {

        if (map[y][x] == '.') {
            count_of_m++;
            add_to_invent("Желтогрив", '.', 1, COLOR_PAIR(8));
        }
            
        else
        {
            count_of_rm++;
            add_to_invent("Краснолгазик", (char)133 , 1, COLOR_PAIR(22));
        }

        attron(COLOR_PAIR(7));
        move(y, x);
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

void my_boy::boy_reset(int start_pos_x, int start_boy_y)
{
    hp = 10;
    x = start_pos_x;
    y = start_boy_y;
    count_of_m = 0;
    count_of_rm = 0;
}

void my_boy::add_to_invent(std::string name, char icon, int count, int color)
{
    bool founded = false;
    for (ivent_thing var : invent)
    {
        if (var.name == name) {
            var.count++;
            founded = true;
            break;
        }
        
    }

    if (founded == false) {
        /*          ivent_thing var{ name, count };*/
        invent.push_back({ name, icon ,count, color });
    }
}







