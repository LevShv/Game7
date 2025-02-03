#pragma once
#include "level.h"

class level_back_fforest : public Level // явное указание public наследовани€
{
public:

    void start() override;
    void update() override;

    level_back_fforest(my_boy& boy);
    ~level_back_fforest(); 

private:

    bool gotooldman = true;
    bool iwasoldman1 = true;
    bool ireadom1 = true;
    bool gotoborder = false;

    void score_set() override;
    void draw() override;
    void moving() override;
};