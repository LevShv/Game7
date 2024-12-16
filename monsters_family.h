#pragma once
#include <vector>
#include <scary_monster.h>

class monsters_family
{
public:

    monsters_family(char** give_me_map);
    ~monsters_family();
    
    std::vector<std::vector<int>> wma;

    void find(int x, int y);
    int monsters_move(bool stop);
    void give_some_boys_rand();

private:

    char** map;
    std::vector<scary_monster>* Monsters = new std::vector<scary_monster>();

    void create_two_boys();
    
};