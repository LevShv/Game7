#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "level.h"
#include "my_boy.h"

class level_manager
{
    public:

    level_manager();
    ~level_manager() = default;

    void start_next_level();
    void select_level(int level);
    bool all_levels_done();
    

    int currentLevelIndex = 0;

    my_boy boy;

    int number_of_download;
    bool download;

    private:


    //std::vector<std::unique_ptr<
    std::vector<std::function<std::unique_ptr<Level>()>> level_factories;
    std::vector<std::unique_ptr<Level>> levels;
    
    bool off = false;


    
    
};

