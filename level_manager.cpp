#include "level_manager.h"
#include "level_start.h"
#include "level_forest.h"
#include "level_back_fforest.h"
#include "level_way_to_village.h"

level_manager::level_manager() {

    level_factories.push_back([this]() { return std::make_unique<level_start>(boy); });
    level_factories.push_back([this]() { return std::make_unique<level_forest>(boy); });
    level_factories.push_back([this]() { return std::make_unique<level_back_fforest>(boy); });
    level_factories.push_back([this]() { return std::make_unique<level_way_to_village>(boy); });
}

void level_manager::start_next_level() {

    if (currentLevelIndex < level_factories.size()) {

        levels.push_back(level_factories[currentLevelIndex]());
        levels.back()->start();
        levels.back()->update();
        currentLevelIndex++;
    }
}

void level_manager::chose_level(int level)
{

}


bool level_manager::all_levels_done() {
    return currentLevelIndex >= level_factories.size();
}
