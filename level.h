#pragma once

#include <curses.h>
#include <vector>
#include "monsters_family.h"
#include "my_boy.h"
#include "my_map.h"
#include "iface.h"
#include "Audio.h"


class Level {
protected:

    int width = 120;
    int length = 28;
    int start_pos_x = 59; 
    int start_pos_y = 21; 
    int subtimming = 30; // задержка вывода sub
    int game_iter; //  передать

    int nscore = 0; 
    int sci = 0; // счетчик итераций 

    bool move;
  

    sound sounds/* = new sound()*/;
    my_boy& boy;
    static std::shared_ptr<my_boy> auto_saved;
    my_map map; 
    iface intface; 
    std::vector<monster_type*>* monsters;

    track* Background;
    track* River;

    virtual void score_set() = 0; // 
    virtual void draw() = 0;
    virtual void moving() = 0;
    //virtual void 
    int make_move(char** map);
    void pause();
    void save_check();
    void dead();
    bool notification(bool &flag, const char* row1, const char* row2, int score, bool &nextbool);
    bool notification(bool& flag, const char* row1, const char* row2, int score);

    void buy(std::string for_sale, invent_thing need, int price);


public:

    
    Level(my_boy& boy, int map_type);
    void Level_setup();
    virtual ~Level();

    virtual void start(); // Чисто виртуальная функция для запуска уровня
    virtual void update() = 0; // Чисто виртуальная функция для обновления уровня

    bool exit_ = false;
    bool download = false;
    bool alived = false;
    int number_of_loading;

};
