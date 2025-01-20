#pragma once
#include "level.h"
//#include "monster_type.h"
#include "monsters_family.h"
#include "vector"

class level_back_ff : public Level {

private:

    monsters_family* badboys = new monsters_family(map.forest, monsters[0]);

    bool igotall = true;
    bool gotoborder = false;

    void score_set() override;
    void draw() override;

public:

    //level_back_ff(my_boy& boy, ); // Конструктор принимает игрока
    void start() override;
    void update() override;



};
