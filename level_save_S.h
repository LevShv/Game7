#pragma once

#include "level.h"

class level_save_S : public Level // явное указание public наследовани€
{
public:

    void start() override;
    void update() override;

    level_save_S(my_boy& boy);
    ~level_save_S() override = default;

private:

    bool gotooldman = true;
    bool gotoborder = false;
    bool talkwithS = false;
    bool ikillall = false;
    bool iwasoldman= false;
    bool ireadom1 = false;

    int count_of_monsters = 5;
  


    void score_set() override;
    void draw() override;
    void moving() override;


};

