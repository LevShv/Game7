#pragma once
#include <vector>
#include <string>

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

    std::vector<invent_thing> invent;

    my_boy(int spx, int spy);
    my_boy();
    
    void move_boy(char** map);
    void boy_reset(int start_pos_x, int start_boy_y);
    void add_to_invent(std::string name, char icon, int count, int color, bool usage);
    void remove_thing(std::string name);
    void do_something(int num, char** map);

    void save();
  
   
private:

    int xl = 0;
    int yl = 0;

    void print_me(int color);
};

