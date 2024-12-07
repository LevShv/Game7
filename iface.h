#pragma once
#include "curses.h"
class iface {
public:

    iface();
    void draw(int boy_hp, int count_ofm);
    void game_over();

private:

    int xposofhp = 29;
    int yposofhp = 50;

    void draw_hp_boy(int hp);
    void draw_Count_of_mushrooms(int count_ofm);
    void Bckg();
    
};
