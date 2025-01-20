#include "level_manager.h"
#include "level_manager.h"
#include "level_start.h"
#include "level_forest.h"
#include "level_back_fforest.h"
#include "level_way_to_village.h"

level_manager::level_manager() {

    levels.push_back(std::make_unique<level_start>(boy));
    levels.push_back(std::make_unique<level_forest>(boy));
    levels.push_back(std::make_unique<level_back_fforest>(boy));
    levels.push_back(std::make_unique<level_way_to_village>(boy));
}

level_manager::~level_manager()
{
   /* for (monster_type* monster : monsters) {
        delete monster;
    }*/
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


