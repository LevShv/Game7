#pragma once
#include <vector>
#include <string>
#include <curses.h>

struct invent_thing
{
    std::string name;
    char icon;
    int count;
    int color;
    bool usage;

};

class my_boy {

public:

    int x;
    int y;

    int hp = 10;
    int where = 0;
    int count_of_m = 0;
    int count_of_rm = 0;

    bool loaded_boy = false;
    bool need_to_setup = false;

    std::vector<invent_thing> invent;

    my_boy(int spx, int spy);
    my_boy();
    
    void move_boy(char** map);
    void boy_reset(int start_pos_x, int start_boy_y);
    void add_to_invent(std::string name, char icon, int count, int color, bool usage);
    void add_to_invent(invent_thing thing);
    bool set_thing_count(std::string name, int count);
    int get_thing_count(std::string name);
    void check_invent_for_null(int num);
    void save();
 
   
private:

    int xl = 0;
    int yl = 0;

    void print_me(int color);
    void shoot_arrow();
};

