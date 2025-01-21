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

        if (levels.back()->exit_)
            if (levels.back()->download) {
                off = true;
                number_of_download = levels.back()->number_of_loading;
            }
        else
            off = true;

        currentLevelIndex++;
    }
}

void level_manager::select_level(int level)
{
    currentLevelIndex = level;

    switch (level)
    {
        case 2:

            boy.hp = 8;
            boy.add_to_invent("Желтогрив", '.', 20, COLOR_PAIR(8), 0);
            boy.add_to_invent("Краснолгазик", (char)133, 10, COLOR_PAIR(22), 0);

        break;
            
        case 3:

            boy.hp = 8;
            boy.add_to_invent("Желтогрив", '.', 20, COLOR_PAIR(8), 0);
            boy.add_to_invent("Краснолгазик", (char)133, 10, COLOR_PAIR(22), 0);
            boy.add_to_invent("Ловушка", 'o', 5, COLOR_PAIR(10), 1);

        break;
    }

}

bool level_manager::all_levels_done() {

    if (off) return true;
    return currentLevelIndex >= level_factories.size();
}
