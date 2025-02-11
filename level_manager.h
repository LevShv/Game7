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
    void preset();
    bool all_levels_done();
    void reset();
    bool load_game();
    void restart();

    int currentLevelIndex = 0;

    my_boy boy;

    int number_of_download;
    bool download;
    

    private:


    bool stop_level = false;
    std::vector<std::function<std::unique_ptr<Level>()>> level_factories;
    std::vector<std::unique_ptr<Level>> levels;
    
  


    
    
};

