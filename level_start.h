#pragma once

#include "level.h"

class level_start : public Level {

    private:

        bool gotooldman = true;
        bool iwasoldman1 = true;
        bool ireadom1 = false;
        bool spawn_mushroom = false;
        bool ifindall = true;
        bool iwasoldman2 = false;
        bool iwasoldman2delay = false;
        bool gotoforest = false;

        void score_set() override;
        void draw() override;

    public:

        level_start(my_boy& boy); // Конструктор принимает игрока
        void start() override;
        void update() override;
      


};

