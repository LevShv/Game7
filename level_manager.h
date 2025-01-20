#pragma once

#include <vector>
#include <memory>
#include "level.h"
#include "my_boy.h"

class level_manager
{
    private:

        std::vector<std::unique_ptr<Level>> levels;
        int currentLevelIndex = 0;

    public:

        level_manager();
        void start_next_level();
        bool all_levels_done();
        my_boy boy;

    
};

