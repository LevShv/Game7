#pragma once

#include "my_map.h"
#include "my_boy.h"
#include "iface.h"
#include "monsters_family.h"
#include <vector>

class Level {
protected:

    int width = 120;
    int length = 28;
    int start_pos_x = 59; //
    int start_pos_y = 21; //
    int subtimming = 10; // задержка вывода sub
    int game_iter; //  передать

    int nscore = 0; // номер цели
    int sci = 0; // счетчик итераций 

    my_boy& boy; // передать
    my_map map; // передать арг
    iface intface; 
    std::vector<monster_type*>* monsters;

    virtual void score_set() = 0; // 
    virtual void draw() = 0;
    //virtual void 
    int make_move(char** map);


public:

    Level(my_boy& boy, int map_type);
    virtual ~Level() = default;

    virtual void start() = 0; // Чисто виртуальная функция для запуска уровня
    virtual void update() = 0; // Чисто виртуальная функция для обновления уровня

};
