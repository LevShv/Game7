#include "level_manager.h"
#include "level_manager.h"
#include "level_start.h"

//#include "level_forest.h"
//#include "level_back_ff.h"
//#include "level_way_to_village.h"

level_manager::level_manager() {

    levels.push_back(std::make_unique<level_start>(boy));
    /*levels.push_back(std::make_unique<LevelForest>());
    levels.push_back(std::make_unique<LevelBackFF>());
    levels.push_back(std::make_unique<LevelWayToVillage>());*/
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