#include "my_map.h"
#include <curses.h>


    my_map::my_map() {
        map = new char* [length];
        map_gen();
    }

    void my_map::show_map() {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++) {
                move(i, j);
                printw(map[i, j]);
            }

        }
        /*refresh();*/
    }
    my_map::~my_map() {

        for (int i = 0; i < length; i++)
            delete[] map[i];
        delete[] map;
    }

    void my_map::map_gen() {

        for (int i = 0; i < length; i++) {

            map[i] = new char[width];

            for (int j = 0; j < width; j++) {
                map[i][j] = '#';
            }
        }
    }
