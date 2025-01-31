#include "level_start.h"
//#include"level.h"

level_start::level_start(my_boy& boy) : Level(boy, 1) {}

void level_start::start() {

    Level::start();
    clear();
    map.show_map();
    boy.move_boy(map.forest);
    intface.draw(boy.hp, 0, boy.invent);
}

void level_start::update() {

    while (!exit_) {

        if (notification(gotooldman,
            "Мне надо спасти лес от напасти черного мага.",
            "Надо встретиться с моим учителем - Старцем <S>",
            1)) {
        }

        if (boy.x == 8 && boy.y == 19 && iwasoldman1 == true) {

            intface.subs(" <Старец> - Приветсвую тебя мой ученик, нам предстоит тяжелый путь, ",
                "чтобы победить темного мага (enter) - далее");
            timeout(-1);
            getch();
            intface.subs("<Старец> - Нам нужно сделать несколько зелей, инградиенты будет заполучить",
                "не просто, для начала ступай за реку, найди 10 красноглазых опят");
            iwasoldman1 = false;
            ireadom1 = true;
            spawn_mushroom = true;
        }

        if (notification(ireadom1,
            "<Старец> - Нам нужно сделать несколько зелей, инградиенты будет заполучить",
            "не просто, для начала ступай за реку, найди 10 красноглазых опят",
            2)) {}

        if (spawn_mushroom == true) {
            map.add_mushrooms(133, 10, 27, 87);
            spawn_mushroom = false;
        }

        if (boy.count_of_rm == 10 && notification(ifindall,
            "Все грибы собраны, возращаемся к старцу",
            "",
            3, iwasoldman2)) {
        }

        if (boy.count_of_rm == 10 && iwasoldman2 == true && boy.x == 8 && boy.y == 19) {
            intface.subs("<Старец> - Я приготовлю из этих красноглазиков ловушки для монстров.",
                "(enter) - далее");
            timeout(-1);
            getch();
            intface.subs("<Старец> - ..готовит..",
                "(enter) - далее");
            getch();
            intface.subs("<Старец> - из 5 красноглазиков получается 1 ловушка",
                "Собирай еще их по возможности");
            getch();
            intface.subs("<Старец> - ..отдает ловушки..",
                "");
            getch();

            invent_thing catcher({ "Ловушка", 'o', 1, COLOR_PAIR(10), 1 });
            buy("Красноглазик", catcher, 5);

            intface.subs("<Старец> - Хорошо, теперь тебя ждет более суровое испытание.",
                "Тебе нужно в мрачный лес по заросшей тропе вниз по реке (enter) - далее");
            getch();
            intface.subs("<Старец> - В том лесу обитают монстры, твари черного мага.",
                "Будь осторожен чем дольше ты в лесу тем больше их появляется поблизости");
            getch();
            intface.subs("<Старец> - нам нужно 20 желтогривов. Как только соберешь уходи из леса",
                "");
            getch();
            intface.subs("<Старец> - Если от монстра не сбежать, используй ловушку",
                "Вперед!");

            iwasoldman2 = false;
            iwasoldman2delay = true;


        }

        if (notification(iwasoldman2delay,
            "<Старец> - Если от монстра не сбежать, используй ловушку",
            "Вперед!",
            4,gotoforest)) {
        }

        if (boy.hp <= 0) dead();

        if (boy.x == 119 && boy.y > 10 && boy.y < 20 && gotoforest == true) {
            boy.loaded_boy = false;
            break;
        }

         
        moving();
        draw();
       
    }
}

void level_start::score_set() {

    switch (nscore)
    {
    case 0:

        break;

    case 1:
        intface.score("Встретиться со старцем");
        break;

    case 2:
        intface.score("Собрать 10 красноглазых опят");
        break;

    case 3:
        intface.score("Вернуться к старцу");
        break;

    case 4:
        intface.score("Отправляйтесь в мрачный лес");
        break;

    }
}

void level_start::draw()
{
    clear();

    map.show_map();
    boy.move_boy(map.forest);

    intface.draw(boy.hp, boy.count_of_m, boy.invent);
    score_set();
}

void level_start::moving()
{
    if (make_move(map.forest) == 1) { ////////.............
        game_iter++;
    }

    else {
        sci--;
    }

    save_check();
}

