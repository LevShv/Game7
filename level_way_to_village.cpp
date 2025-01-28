#include "level_way_to_village.h"

level_way_to_village::level_way_to_village(my_boy& boy) : Level(boy,3) {}

level_way_to_village::~level_way_to_village()
{
    delete badboys;
}

void level_way_to_village::start()
{
    boy.y = 27;


    map.show_map();
    boy.move_boy(map.forest);
    intface.draw(boy.hp, 0, boy.invent);

    badboys = new monsters_family(map.forest, 0);
    badboys->give_some_boys_rand(1);

    for (int i = 0; i < count_of_three_monsters; i++) {

        badboys->give_some_boys_rand(0, 20, 29, 0, 100);
        badboys->give_some_boys_rand(0, 20, 29, 0, 100);
        badboys->give_some_boys_rand(1, 20, 29, 0, 100);
    }

    badboys->monsters_move(1);
}

void level_way_to_village::update()
{
    while (!exit_) {

        if (gotovil == true) {
            nscore = 1;
        }

        if (boy.x > 65 && boy.x < 80 && boy.y == 0) {
            break;
        }
        moving();
       
        draw();
    }
}

void level_way_to_village::score_set()
{
    switch (nscore)
    {


    case 1:
        intface.score("ќтправл€йтесь в деревню");
        break;

    case 2:
        intface.score("ќтправл€йтесь в деревню");
        break;

    default:
        break;
    }
}

void level_way_to_village::draw()
{
    

    clear();

    map.show_map();
    boy.move_boy(map.forest);

    if (move)
        boy.hp -= badboys->monsters_move(0);
    else
        badboys->monsters_move(1);

    intface.draw(boy.hp, boy.count_of_m, boy.invent);
    game_iter++;
    score_set();
}

void level_way_to_village::moving()
{
    bool move = make_move(map.forest);

    if (move) { ////////.............
        game_iter++;
        badboys->find(boy.x, boy.y);
    }
    else {
        sci--;

    }
}
