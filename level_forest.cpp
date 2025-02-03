#include "level_forest.h"

level_forest::level_forest(my_boy& boy) : Level(boy, 2) {

    start_pos_x = 0;
    start_pos_y = 10;


}

level_forest::~level_forest()
{


    delete badboys;
}

void level_forest::start()
{
    Level::start();
   
    boy.x = 0;

    clear();
    
    map.show_map();
    intface.draw(boy.hp, 0, boy.invent);
    badboys = new monsters_family(map.forest, 0);
    nscore = 1;
}

void level_forest::update()
{
    while (!exit_) {

        if (boy.count_of_m == 20 && notification(igotall,
            "Все грибы собраны, возращаемся к старцу",
            "",
            2, gotoborder)) {
        }

        if (game_iter % 100 == 0) {
            badboys->give_some_boys_rand(0);
        }

        if (boy.hp <= 0) {
            dead();
            continue;
            clear();
        }

        if (gotoborder == true && boy.x == 0 && boy.y > 10 && boy.y < 20)
            break;

        moving();
        draw();

    }
}

void level_forest::score_set()
{
    switch (nscore)
    {
    case 1:
        intface.score("Соберите 20 желтогривов");
        break;

    case 2:
        intface.score("Возращайтесь на базу");
        break;

    default:
        break;
    }
}

void level_forest::draw()
{
   
    clear();

    map.show_map();
    boy.move_boy(map.forest);

    if (move)
        boy.hp -= badboys->monsters_move(false);
    else
        badboys->monsters_move(true);

    intface.draw(boy.hp, boy.count_of_m, boy.invent);
    score_set();
}

void level_forest::moving()
{
    move = make_move(map.forest);
    if (move) { ////////.............
        game_iter++;
        badboys->find(boy.x, boy.y);
    }
    else {
        sci--;

    }
}
