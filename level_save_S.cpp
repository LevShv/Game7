#include "level_save_S.h"

level_save_S::level_save_S(my_boy& boy) : Level(boy, 1)
{

    start_pos_x = 50;
    start_pos_y = 0;

}

void level_save_S::start()
{
    Level::start();

    boy.hp = 1000;
    if (!boy.loaded_boy)
        boy.y = 0;
    
    clear();
    map.show_map();
    boy.move_boy(map.forest);;
    intface.draw(boy.hp, 0, boy.invent);

    badboys = new monsters_family(map.forest, 0);

    for (int i = 0; i < count_of_monsters; i++) {

        badboys->give_some_boys_rand(true, 0, 16, 27, 0, 70);
        badboys->give_some_boys_rand(true, 1, 16, 27, 0, 70);
        badboys->give_some_boys_rand(true, 3, 16, 27, 0, 70);

    }
}

void level_save_S::update()
{
    while (!exit_) {

        if(notification(gotooldman, "О НЕТ монстры пришли на базу! Надо спасти Старца!",
            "Зачистите базу от монстров", 1, saveS))

        if (boy.x == 8 && boy.y == 19 && iwasoldman1 == true) {

            intface.subs(" <Старец> - Ты молодец ученик мой, ты преодолел тяжелое испытание",
                "Из желтогривиков я приготовлю тебе целебное зелье ");
            timeout(-1);
            getch();

            intface.subs(" <Старец> - на одно целебное зелье нужно 10 желтогривиков ",
                " Старайся собирать все возможные грибы, нам они понадобятся ");
            getch();

            intface.subs("<Старец> - Если у тебя еще есть красоглазики я сделаю еще ловушек",
                "");
            getch();

            intface.subs(" <Старец> - ..готовит.. ",
                "..Отдает целебное зелье.. ");
            getch();

            invent_thing catcher({ "Ловушка", 'o', 1, COLOR_PAIR(10), 1 });
            invent_thing healer({ "Исцеление",'&', 1, COLOR_PAIR(47), 1 });

            buy("Красноглазик", catcher, 5);
            buy("Желтогрив", healer, 10);

            intface.subs("Теперь тебе нужно отправиться в заброшенную деревню, ",
                "которая находится на окраине леса.");
            getch();

            intface.subs("Там, в одном из домов, который находится в самой глубине деревни.",
                " лежит лук, который когда-то принадлежал великому охотнику.");
            getch();

            intface.subs("Ступай по дороге вверх по реке, собирай грибы по дороге",
                "");
            getch();

            iwasoldman1 = false;
            gotooldman = false;

        }

        /*if (iwasoldman1 == false && notification(ireadom1,
            "Ступай по дороге вверх по реке, собирай грибы по дороге",
            "На пути будут встречаться различные монстры применяй зелья чтобы атаковать",
            2, gotoborder)) {
        }*/

        if (boy.hp <= 0) {
            dead();
            clear();
            continue;
        }

        if (boy.x > 30 && boy.x < 38 && boy.y == 0 && gotoborder == true) {
            boy.loaded_boy = false;
            break;
        }

        moving();
        draw();
    }
}

void level_save_S::score_set()
{
    switch (nscore)
    {
    case 1:
        intface.score("Зачистите базу от монстров");
        break;

    case 2:
        intface.score("Отправляйтесь в деревню");
        break;

    default:
        break;
    }
}

void level_save_S::draw()
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

void level_save_S::moving()
{
    move = make_move(map.forest);

    if (move) { ////////.............
        game_iter++;
        badboys->find(boy.x, boy.y);
    }
    else {
        sci--;

    }
    save_check();

}
