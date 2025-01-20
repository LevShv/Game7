#pragma once

#include <vector>
#include <memory>
#include "level.h"
#include "my_boy.h"

class level_manager
{
    public:

    level_manager();
    ~level_manager();

    void start_next_level();
    bool all_levels_done();

    my_boy boy;
    std::vector<monster_type*> monsters;

    private:

        std::vector<std::unique_ptr<Level>> levels;
        int currentLevelIndex = 0;
        void monsters_data();

    
    
};

