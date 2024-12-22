#pragma once
#include <vector>
#include <string>
#include <ivent_thing.h>


class my_boy {

public:

    int x;
    int y;

    int hp = 10;
    int count_of_m = 0;
    int count_of_rm = 0;

    my_boy(int spx, int spy);
    
    void move_boy(char** map);
    void boy_reset(int start_pos_x, int start_boy_y);
    void add_to_invent(std::string name, char icon, int count, int color);


    std::vector<ivent_thing> invent;

    
   
private:

    int xl;
    int yl;
};

