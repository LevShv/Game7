#include "my_map.h"
#include <curses.h>
#include <my_map.h>
#include <random>



    my_map::my_map(int width_of_map, int length_of_map) : width(width_of_map), length(length_of_map){
        forest = new char* [length];
        map_gen();
    }

    void my_map::show_map(){
        for (int i = 0; i < length; i++) {
                mvprintw(i,0,forest[i]);
        }
    }
    my_map::~my_map() {
        
        for (int i = 0; i < length; i++)
            delete[] forest[i];
        delete[] forest;
    }

    void my_map::map_gen() {

        for (int i = 0; i < length; i++) {

            forest[i] = new char[width];

            for (int j = 0; j < width; j++) {
                forest[i][j] = ' ';
            }
        }

        std::random_device rd;  // Используется для получения начального значения (seed)
        std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)

        std::uniform_int_distribution<> disx(1, width - 1); // Равномерное распределение от 0 до 
        std::uniform_int_distribution<> disy(1, length - 1);

        for (int i = 0; i < 100; ++i) {
            int rx = disx(gen);
            int ry = disy(gen);
            forest[ry][rx] = 'T';
        }
    }
