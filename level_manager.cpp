#include "file_tools.h"
#include "iface.h"
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

        boy.where = currentLevelIndex;

        levels.push_back(level_factories[currentLevelIndex]());
        levels.back()->start();
        levels.back()->update();

        if (levels.back()->exit_) {
            if (levels.back()->download == true) {

                currentLevelIndex = levels.back()->number_of_loading;
                download = true;
            }
            stop_level = true;
        }
        else {
            currentLevelIndex++;
        }
        
    }
}

void level_manager::preset()
{

    switch (currentLevelIndex)
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

    if (stop_level) {
        stop_level = false;
        return true;
    }
    return currentLevelIndex >= level_factories.size();
}

void level_manager::reset()
{
    boy = my_boy();
    currentLevelIndex = 0;

}

bool level_manager::load_game()
{
    iface intface;
    file_tools ft;
    std::string path = intface.load_screen();

    if (path == "0")
        return 0;
    try {
        currentLevelIndex = ft.load_boy(boy, path);
    }
    catch (const std::exception& e) {
        return 0;
    }
    return 1;
}
