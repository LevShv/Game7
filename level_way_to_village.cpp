#include "level_way_to_village.h"

level_way_to_village::level_way_to_village(my_boy& boy) : Level(boy,3) 
{
    start_pos_x = 65;
    start_pos_y = 27;

    River = new track();
    River->play("River.wav");
    River->loaded_track->setVolume(30);
}

level_way_to_village::~level_way_to_village()
{
    River->stop();
    delete badboys;
}

void level_way_to_village::start()
{
    Level::start();
    clear;
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

        if (boy.hp <= 0) {
            dead();  
            clear();
            continue;
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
        intface.score("������������� � �������");
        break;

    case 2:
        intface.score("������������� � �������");
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
        boy.hp -= badboys->monsters_move(false);
    else
        badboys->monsters_move(true);

    intface.draw(boy.hp, boy.count_of_m, boy.invent);
    game_iter++;
    score_set();
}

void level_way_to_village::moving()
{
    move = make_move();

    if (move) { ////////.............
        game_iter++;
        badboys->find(boy.x, boy.y);
    }
    else {
        sci--;

    }
}
