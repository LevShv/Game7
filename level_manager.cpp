#include "file_tools.h"
#include "iface.h"
#include "level_manager.h"
#include "level_start.h"
#include "level_forest.h"
#include "level_back_fforest.h"
#include "level_way_to_village.h"
#include "level_village.h"
#include "level_back_ffvillage.h"
#include "level_save_S.h"
#include "level_final.h"

level_manager::level_manager() {

    level_factories.push_back([this]() { return std::make_unique<level_start>(boy); });
    level_factories.push_back([this]() { return std::make_unique<level_forest>(boy); });
    level_factories.push_back([this]() { return std::make_unique<level_back_fforest>(boy); });
    level_factories.push_back([this]() { return std::make_unique<level_way_to_village>(boy); });
    level_factories.push_back([this]() { return std::make_unique<level_village>(boy); });
    level_factories.push_back([this]() { return std::make_unique<level_back_ffvillage>(boy); });
    level_factories.push_back([this]() { return std::make_unique<level_save_S>(boy); });
    level_factories.push_back([this]() { return std::make_unique<level_final>(boy); });

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
            if (levels.back()->alived == true) {

                /*levels.back()->alived = false;*/
                /*start_next_level();*/

                levels.back().reset();
                return;


            }

            stop_level = true;
            levels.clear();
        }
        else {

            currentLevelIndex++;

            if (currentLevelIndex >= level_factories.size()) {
                levels.clear();
            }
            else {

                levels.back().reset();
            }
               
           
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
            boy.add_to_invent("Ловушка", 'o', 2, COLOR_PAIR(10), 1);

        break;
            
        case 3:

            boy.hp = 8;
            boy.add_to_invent("Исцеление",'&', 2, COLOR_PAIR(47), 1 );
            boy.add_to_invent("Красноглазик", (char)133, 10, COLOR_PAIR(22), 0);
            boy.add_to_invent("Ловушка", 'o', 5, COLOR_PAIR(10), 1);
        break;

        case 4:

            boy.hp = 8;
            boy.add_to_invent("Исцеление",'&', 2, COLOR_PAIR(47), 1 );
            boy.add_to_invent("Красноглазик", (char)133, 3, COLOR_PAIR(22), 0);
            boy.add_to_invent("Ловушка", 'o', 5, COLOR_PAIR(10), 1);
        break;
        case 5:

            boy.hp = 8;
            boy.add_to_invent("Исцеление", '&', 2, COLOR_PAIR(47), 1);
            boy.add_to_invent("Красноглазик", (char)133, 3, COLOR_PAIR(22), 0);
            boy.add_to_invent("Ловушка", 'o', 5, COLOR_PAIR(10), 1);
            boy.add_to_invent("Лук", '}', 1, COLOR_PAIR(47), 1);
            break;
        case 6:

            boy.hp = 8;
            boy.add_to_invent("Исцеление", '&', 2, COLOR_PAIR(47), 1);
            boy.add_to_invent("Красноглазик", (char)133, 3, COLOR_PAIR(22), 0);
            boy.add_to_invent("Ловушка", 'o', 5, COLOR_PAIR(10), 1);
            boy.add_to_invent("Лук", '}', 1, COLOR_PAIR(47), 1);
            break;
        case 7:

            boy.hp = 8;
            boy.add_to_invent("Исцеление", '&', 2, COLOR_PAIR(47), 1);
            boy.add_to_invent("Красноглазик", (char)133, 3, COLOR_PAIR(22), 0);
            boy.add_to_invent("Ловушка", 'o', 5, COLOR_PAIR(10), 1);
            boy.add_to_invent("Лук", '}', 1, COLOR_PAIR(47), 1);
            boy.add_to_invent("Зелье силы", '@', 1, COLOR_PAIR(50), 1);
            boy.x = 27;
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

void level_manager::restart()
{
    level_factories.clear();
}
