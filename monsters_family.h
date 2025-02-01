#pragma once
#include <vector>
#include <scary_monster.h>

class monsters_family
{
public:

    //std::vector<monster_type*> monsters;
    //monsters_family(char** give_me_map);
   /* monsters_family(char** give_me_map);*/

    monsters_family(char** give_me_map, int mType);
    monsters_family();
    ~monsters_family();

    void give_some_boys_rand(int type);
    void give_some_boys_rand(int type, int start_row, int end_row, int start_col, int end_col);
    void give_some_boys_rand(bool reverse, int type, int start_row, int end_row, int start_col, int end_col);
    void find(int x, int y);

    int monsters_move(bool stop);
    void make_map_with_monsters(char** map_with_monsters);

    void kill_monster(int y, int x);


private:
    
   /* std::vector<>*/
    char monster;
    char** map;
    

    std::vector<scary_monster> Monsters;
    std::vector<monster_type*> variations;

    void create_two_boys(int type);
    void monsters_data();

    void random_point(int* rx, int* ry);
    
};