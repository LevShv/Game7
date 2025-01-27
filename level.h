#pragma once

#include "monsters_family.h"
#include "my_boy.h"
#include <vector>
#include "my_map.h"
#include "iface.h"
#include <curses.h>

class Level {
protected:

    int width = 120;
    int length = 28;
    int start_pos_x = 59; 
    int start_pos_y = 21; 
    int subtimming = 10; // задержка вывода sub
    int game_iter; //  передать

    int nscore = 0; 
    int sci = 0; // счетчик итераций 


    my_boy& boy;
    my_map map; 
    iface intface; 
    std::vector<monster_type*>* monsters;

    virtual void score_set() = 0; // 
    virtual void draw() = 0;
    //virtual void 
    int make_move(char** map);
    void pause();
    void save_check();


public:

    Level(my_boy& boy, int map_type);
    virtual ~Level() = default;

    virtual void start() = 0; // Чисто виртуальная функция для запуска уровня
    virtual void update() = 0; // Чисто виртуальная функция для обновления уровня

    bool exit_ = false;
    bool download = false;
    int number_of_loading;

};
