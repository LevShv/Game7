#pragma once
#include "level.h"
#include "monsters_family.h"


class level_forest : public Level {

private:

    bool igotall = true;
    bool gotoborder = false;

    void score_set() override;
    void draw() override;
    void moving() override;

public:

    void start() override;
    void update() override;

    level_forest(my_boy& boy);
    ~level_forest() override;

};
