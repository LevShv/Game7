#include "level_final.h"
#include "final_boss.h"
#include "random"



level_final::level_final(my_boy& boy) : Level(boy, 5)
{
    start_pos_x = 27;
    start_pos_y = 0;

    Aimbie = new track();
    Aimbie->play("Ambie.wav");
    Aimbie->loaded_track->setVolume(50);
    sadplay = true;
    Happy = new track();
 
    


}

level_final::~level_final()
{
    if(happyplay)
        Happy->stop();

    if (sadplay)
        Aimbie->stop();

    delete badboys;
}

void level_final::start()
{
    Level::start();

    clear();
    boy.y = 0;
    boy.hp = 10;
    map.show_map();
    boy.move_boy(map.forest);
    intface.draw(boy.hp, 0, boy.invent);
    boss.give_map(map.forest);

    badboys = new monsters_family(map.forest, 0);
    badboys->give_some_boys_rand(1);


    for (int i = 0; i < count_of_monsters; i++) {

        badboys->give_some_boys_rand(1,2, 10, 20, 10, 100);
        badboys->give_some_boys_rand(1,2, 10, 20, 10, 100);
    }
    boss.move_monster(false, boy.x, boy.y);
    boss_enabled = true;
    badboys->monsters_move(1);
}

void level_final::update()
{
    while (!exit_) {

        if (killhim)
            nscore = 1;

        if (!boss.alive && killhim) {
            killhim = false;
            win = true;
            ireadom1 = true;
        }
            
        if (notification(win, "Маг повержен!", "Уходите из замка!", 2, gotoborder) && !condition_met && ireadom1) {
         
            condition_met = true; 
            start_time = std::chrono::steady_clock::now(); 
            Aimbie->stop();

            Happy->play("Happy.wav");
            Happy->loaded_track->setVolume(30);
            happyplay = true;
            sadplay = false;
        }


        if (condition_met && !fornext) {
            auto current_time = std::chrono::steady_clock::now();
            auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();

            if (elapsed_time >= 10) {
                killall = true; 
                fornext = true;
              
               
            }
        }
    

        if (boy.hp <= 0) {
            dead();
            clear();
            continue;
        }

        if (boy.x > 12 && boy.x < 35 && boy.y == 0 && gotoborder) {
            intface.game_win();
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
        intface.score("Прикончите мага");
        break;

    case 2:
        intface.score("Победа!");
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

    if (move && !killall) {
        boy.hp -= badboys->monsters_move(false);
        boss.move_monster(false, boy.x, boy.y);
    }
       
    else if (!killall){
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

