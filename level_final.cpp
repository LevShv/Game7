#include "level_final.h"
#include "final_boss.h"
#include "random"



level_final::level_final(my_boy& boy) : Level(boy, 5)
{
    start_pos_x = 65;
    start_pos_y = 27;

}

level_final::~level_final()
{
    delete badboys;
}

void level_final::start()
{
    Level::start();

    clear();
    boy.y = 27;
    boy.hp = 10000;
    map.show_map();
    boy.move_boy(map.forest);
    intface.draw(boy.hp, 0, boy.invent);
    boss.give_map(map.forest);

    badboys = new monsters_family(map.forest, 0);
    badboys->give_some_boys_rand(1);


    /*for (int i = 0; i < count_of_monsters; i++) {

        badboys->give_some_boys_rand(3, 20, 29, 0, 100);
        badboys->give_some_boys_rand(3, 20, 29, 0, 100);
    }*/
    boss.move_monster(false, boy.x, boy.y);
    boss_enabled = true;
    badboys->monsters_move(1);
}

void level_final::update()
{
    while (!exit_) {

        if (gotofind)
            nscore = 1;

        if (notification(ifound, "Лук Найден!", "Возращайтесь на базу", 2, gotoborder)) {}

        if (boy.hp <= 0) {
            dead();
            clear();
            continue;
        }

        if (boy.x > 65 && boy.x < 80 && boy.y == 27 && gotoborder) {
            break;
        }

        moving();

        draw();
    }
}

void level_final::score_set()
{
    switch (nscore)
    {


    case 1:
        intface.score("Обыщите дома");
        break;

    case 2:
        intface.score("Отправляйтесь на базу");
        break;

    default:
        break;
    }
}

void level_final::draw()
{

    clear();

    map.show_map();
    boy.move_boy(map.forest);

    if (move) {
        boy.hp -= badboys->monsters_move(false);
        boss.move_monster(false, boy.x, boy.y);
    }
       
    else {
        badboys->monsters_move(true);
        boss.move_monster(true, boy.x, boy.y);
    }
        


    intface.draw(boy.hp, boy.count_of_m, boy.invent);
    game_iter++;
    score_set();
}

void level_final::moving()
{
    move = make_move(map.forest, boss.y, boss.x);

    if (move) { ////////.............
        game_iter++;
        badboys->find(boy.x, boy.y);
        boss.give_waythim(boy.x, boy.y, boy.hp);
    }
    else {
        sci--;

    }
    if (boss_beat == true) {
        boss.hp -= 4;
        boss_beat = false;
    }
}

