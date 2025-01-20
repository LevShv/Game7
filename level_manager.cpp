#include "level_manager.h"
#include "level_manager.h"
#include "level_start.h"
#include "level_back_ff.h"

//#include "level_forest.h"
//#include "level_back_ff.h"
//#include "level_way_to_village.h"

level_manager::level_manager() {

    levels.push_back(std::make_unique<level_start>(boy));
   /* levels.push_back(std::make_unique<level_back_ff>(boy,monsters));*/
 /*   levels.push_back(std::make_unique<LevelBackFF>());
    levels.push_back(std::make_unique<LevelWayToVillage>());*/
}

level_manager::~level_manager()
{
    for (monster_type* monster : monsters) {
        delete monster;
    }
}

void level_manager::start_next_level() {

    if (currentLevelIndex < levels.size()) {

        levels[currentLevelIndex]->start();
        levels[currentLevelIndex]->update();
        currentLevelIndex++;
    }
}

bool level_manager::all_levels_done() {
    return currentLevelIndex >= levels.size();
}

void level_manager::monsters_data() {

    monster_type* W = new monster_type(
        "W",
        'W',
        COLOR_PAIR(10),
        COLOR_PAIR(27),
        { {-1, 0}, {1, 0}, {0, -1}, {0, 1},
          {-1,-1}, {-1,1}, {1, -1}, {1, 1}, },
        2,
        1,
        10,
        5);

    monster_type* Y = new monster_type(
        "Y",
        'Y',
        COLOR_PAIR(25),
        COLOR_PAIR(26),
        { /*{-1, 0}, {1, 0}, {0, -1}, {0, 1},*/
          {-1,-1}, {-1,1}, {1, -1}, {1, 1}, },
          1,
          3,
          30,
          5);

    monsters.push_back(W);
    monsters.push_back(Y);

}
