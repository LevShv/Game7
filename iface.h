#pragma once
#include "curses.h"
class iface {
public:

    iface();
    iface(bool start);
    void draw(int boy_hp, int count_ofm);
    void game_over();
    void game_win();
    void subs(const char* a, const char* b);
    void score(const char* a);


private:

    int xposofhp = 29;
    int yposofhp = 50;

    void draw_hp_boy(int hp);
    void draw_Count_of_mushrooms(int count_ofm);
    void Bckg();
    
    
};
