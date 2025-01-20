#pragma once
#include <vector>
#include <scary_monster.h>

class monsters_family
{
public:

    //std::vector<monster_type*> monsters;
    //monsters_family(char** give_me_map);
   /* monsters_family(char** give_me_map);*/
    monsters_family(char** give_me_map, monster_type* first_type);
    monsters_family(char** give_me_map, int mType);
    ~monsters_family();

    void give_some_boys_rand(monster_type* type);
    void give_some_boys_rand(monster_type* type, int start_row, int end_row, int start_col, int end_col);
    
    std::vector<std::vector<int>> wma;

    void find(int x, int y);
    int monsters_move(bool stop);



private:
    
   /* std::vector<>*/
    char monster;
    char** map;
    

    std::vector<scary_monster>* Monsters = new std::vector<scary_monster>();
    std::vector<monster_type*> types;

    void create_two_boys(monster_type* type);
    void monsters_data();

    void random_point(int* rx, int* ry);
    
};