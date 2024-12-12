
#include <curses.h>
#include <my_map.h>
#include <my_boy.h>
#include <monster.h>
#include <scary_monster.h>
#include <monsters_family.h>
#include "iface.h"

void colors_pairs() {

    init_color(8, 900, 100, 100); // серый нижний bar
    init_color(257, 46, 139, 87); //  темно-зеленый цвет фона



    init_pair(1, COLOR_RED, COLOR_RED); // полоска здоровья
    init_pair(2, COLOR_BLACK, 8); // цвет "Boy"
    init_pair(3, COLOR_BLACK, 8); // цвет "Грибы"

    init_pair(4, 7, 257); // темно-зеленый цвет фона
    init_pair(5, COLOR_RED, 257); // пара для фона

    init_pair(6, COLOR_BLACK, COLOR_BLACK); // черный для опустевшего здоровья
    init_pair(7, COLOR_BLUE, 257); // "0"
    init_pair(8, COLOR_YELLOW, 257);// грибы

    init_pair(10, COLOR_RED, 257);
    
    
}

int main()
{

    int width = 120;
    int length = 28;

    int start_pos_x = 2;
    int start_pos_y = 2;

    int game_iter = 0;

    initscr();
    curs_set(0);
    noecho();
    start_color();
    colors_pairs();

    my_map map(width, length);
    map.show_map();

    iface intface;

    my_boy boy(start_pos_x, start_pos_y);

    monsters_family* badboys = new monsters_family(map.forest);

    while (true) {
        if (boy.hp == 0) {
            intface.game_over();
            getch();
            return 0;
        }
        if (boy.count_of_m == 20) {
            intface.game_win();
            getch();
            return 0;
        }
        switch (getch()) {
        case 'w':
            if (0 < boy.y) {
                boy.y--;
                badboys->find(boy.x, boy.y);
            }
            break;
        case 's':
            if (boy.y < length - 1) {
                boy.y++;
                badboys->find(boy.x, boy.y);
            }
            break;
        case 'a':
            if (boy.x > 0) {
                boy.x--;
                badboys->find(boy.x, boy.y);
            }
            break;
        case 'd':
            if (boy.x < width - 1) {
                boy.x++;
                badboys->find(boy.x, boy.y);
            }
            break;
        case 'q':
            break;

        }
        if (game_iter % 100 == 0)
            badboys->give_some_boys_rand();

        clear();

        map.show_map();
        boy.move_boy(map.forest);

        boy.hp -= badboys->monsters_move();
        intface.draw(boy.hp, boy.count_of_m);
        game_iter++;
        
    }

    getch();
    endwin();
    delete badboys;

}