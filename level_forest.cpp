#include "level_forest.h"

level_forest::level_forest(my_boy& boy) : Level(boy, 2) {}

level_forest::~level_forest()
{
    delete badboys;
}

void level_forest::start()
{
    clear();
    boy.x = 1;
    map.show_map();
    intface.draw(10, 0, boy.invent);
    badboys = new monsters_family(map.forest, 0);
}

void level_forest::update()
{
    while (!exit_) {

        if (boy.hp == 0) {
            intface.game_over();
            getch();
            break;
        }

        if (boy.count_of_m == 20 && igotall == true) {
            intface.subs("Все грибы собраны, возращаемся к старцу",
                "");
            nscore = 2;
            sci++;
            gotoborder = true;
            if (sci >= subtimming * nscore)
                igotall = false;

        }

        if (game_iter % 100 == 0) {
            badboys->give_some_boys_rand(0);
        }

        if (gotoborder == true && boy.x == 0 && boy.y > 10 && boy.y < 20)
            break;

        score_set();
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
    

    bool move = make_move(map.forest);
    if (move) { ////////.............
        game_iter++;
        badboys->find(boy.x, boy.y);
    }
    else {
        sci--;

    }

    clear();

    map.show_map();
    boy.move_boy(map.forest);

    if (move)
        boy.hp -= badboys->monsters_move(0);
    else
        badboys->monsters_move(1);

    intface.draw(boy.hp, boy.count_of_m, boy.invent);
}
