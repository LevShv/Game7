
#include <curses.h>
#include <my_map.h>
#include <my_boy.h>
#include <monster.h>
#include <scary_monster.h>
#include <monsters_family.h>
#include "iface.h"
#include <locale.h>
#include <monster_type.h>
#include <vector>

int level = 0;


int width = 120;
int length = 28;

int start_pos_x = 59; // 59
int start_pos_y = 21; // 21

int subtimming = 10;

int game_iter = 1;

my_boy boy(start_pos_x, start_pos_y);
std::vector<monster_type*> monsters;


void colors_pairs() {

    init_color(300, 165,165,165); // серый нижний bar
    init_color(257, 46, 139, 87); //  темно-зеленый цвет фона
    init_color(258, 0, 0, 128); // темно-синий
    init_color(259, 189, 183, 107); // бежевый
    init_color(260, 240, 230, 140); // светло-бежевый


    init_pair(1, COLOR_RED, COLOR_RED); // полоска здоровья
    init_pair(2, COLOR_BLACK, 8); // цвет "Boy"
    init_pair(3, COLOR_BLACK, 8); // цвет "Грибы"

    init_pair(4, 7, 257); // темно-зеленый цвет фона
    init_pair(5, COLOR_RED, 257); // пара для фона

    init_pair(6, COLOR_BLACK, COLOR_BLACK); // черный для опустевшего здоровья
    init_pair(7, COLOR_BLUE, 257); // "0"
    init_pair(8, COLOR_YELLOW, 257);// грибы

    init_pair(10, COLOR_RED, 257); // W

    init_pair(11, COLOR_BLUE, COLOR_BLUE); // вода
    init_pair(12, COLOR_BLUE, 258); // край воды 
    
    init_pair(13, 258, 258); // Вода...
    init_pair(14, 259, 259); // Мост
    init_pair(15, 260, 260); // дорожка
    
    init_pair(16, COLOR_BLUE, 259); // дорожка с персонажем

    init_pair(17, COLOR_WHITE, COLOR_WHITE); // кровать
    init_pair(18, COLOR_BLUE, COLOR_WHITE); // Персонаж на кровати

    init_pair(19, 8, 259); // Серый старец дома

    init_pair(20, 300, COLOR_BLACK); // Серый старец дома
    init_pair(21, COLOR_WHITE, COLOR_BLACK); // Subs
    init_pair(22, COLOR_RED, 257); // Красный гриб

    init_pair(23, 258, 8);//стрелка инвентаря

    init_pair(24, COLOR_RED, COLOR_BLACK);//Красноглазик для инвентаря

    init_pair(25, COLOR_MAGENTA, 257); // Y
    init_pair(26, COLOR_MAGENTA, 259); // Y1
    init_pair(27, COLOR_RED, 259); // W1

    init_pair(28, COLOR_BLUE, 257); // Голубозубки

}

void monsters_data() {

    monster_type* W = new monster_type(
        "W", 
        'W', 
        COLOR_PAIR(10),
        COLOR_PAIR(27),
        { {-1, 0}, {1, 0}, {0, -1}, {0, 1},
          {-1,-1}, {-1,1}, {1, -1}, {1, 1}, },
        2, 
        1, 
        10, 
        5);

    monster_type* Y = new monster_type(
        "Y",
        'Y',
        COLOR_PAIR(25),
        COLOR_PAIR(26),
        { /*{-1, 0}, {1, 0}, {0, -1}, {0, 1},*/
          {-1,-1}, {-1,1}, {1, -1}, {1, 1}, },
        1,
        3,
        30,
        5);

    monsters.push_back(W);
    monsters.push_back(Y);

}

int make_move(char** map) {
     switch (getch()) {
        case 'w':
            if (0 < boy.y) {
                boy.y--;
                return 1;
            
            }
            break;
        case 's':
            if (boy.y < length - 1) {
                boy.y++;
                return 1;
            }
            break;
        case 'a':
            if (boy.x > 0) {
                boy.x--;
                return 1;
            
            }
            break;
        case 'd':
            if (boy.x < width - 1) {
                boy.x++;
                return 1;
            
          
            }
        break;

        case '1':
            if (boy.invent.size() > 0 && boy.invent[0].usage)
                boy.do_something(0, map);
            return 0;
            break;

            
        case 'e':
            iface inn;
            inn.show_invent(boy.invent);
            return 0;
        break;

       

     }
     return 0;
    
}

/*int make_move(monsters_family*& badboys) {
    switch (getch()) {
    case 'w':
        if (0 < boy.y) {
            boy.y--;

            return 1;
        }
        break;
    case 's':
        if (boy.y < length - 1) {
            boy.y++;

            return 1;
        }
        break;
    case 'a':
        if (boy.x > 0) {
            boy.x--;
            badboys->find(boy.x, boy.y);
            return 1;
        }
        break;
    case 'd':
        if (boy.x < width - 1) {
            boy.x++;
            badboys->find(boy.x, boy.y);
            return 1;
        break;
        }
    case 'e':
        iface inn;
        inn.show_invent();
        return 0;
        break;
*//*

    }
}*/

void level_start()

{
    

    my_map map(width, length,1);
    map.show_map();
    boy.move_boy(map.forest);
    iface intface;
    intface.draw(10, 0, boy.invent);

    

    bool gotooldman = true;

    bool iwasoldman1 = true;
    bool ireadom1 = false;
    bool spawn_mushroom = false;
    bool ifindall = true;
    bool iwasoldman2 = false;
    bool iwasoldman2delay = false;
    bool gotoforest = false;

    int nscore = 0;
    int sci = 0;

    while (true) {
        //mvprintw(17, 119, "2"); // 
        if (gotooldman == true){

            intface.subs("Мне надо спасти лес от напасти черного мага.",
                         "Надо встретиться с моим учителем - Старцем <S>");
            nscore = 1;
            sci++;
            if (sci >= subtimming)
                gotooldman = false;
        }

        if (boy.x == 8 && boy.y == 19 && iwasoldman1 == true) {
            
            intface.subs(" <Старец> - Приветсвую тебя мой ученик, нам предстоит тяжелый путь, ", 
                         "чтобы победить темного мага (enter) - далее");
            getch();
            intface.subs("<Старец> - Нам нужно сделать несколько зелей, инградиенты будет заполучить", 
                         "не просто, для начала ступай за реку, найди 10 красноглазых опят");
            iwasoldman1 = false;
            ireadom1 = true;
            spawn_mushroom = true;
        }

        if (ireadom1 == true) {
            intface.subs("<Старец> - Нам нужно сделать несколько зелей, инградиенты будет заполучить",
                         "не просто, для начала ступай за реку, найди 10 красноглазых опят");
            
            nscore = 2;
            sci++;
            if (sci >= subtimming * nscore)
                ireadom1 = false;
        }

        if (spawn_mushroom == true) {
            map.add_mushrooms(133, 10, 27, 87);
            spawn_mushroom = false;
        }

        if (boy.count_of_rm == 10 && ifindall == true) {
            intface.subs("Все грибы собраны, возращаемся к старцу",
                "");
            nscore = 3;
            sci++;
            iwasoldman2 = true;
            if (sci >= subtimming * nscore)
                ifindall = false;

        }
        if (boy.count_of_rm == 10 && iwasoldman2 == true && boy.x == 8 && boy.y == 19) {
            intface.subs("<Старец> - Хорошо, теперь тебя ждет более суровое испытание.",
                "Тебе нужно в мрачный лес по заросшей тропе вниз по реке (enter) - далее" );
            getch();
            intface.subs("<Старец> - В том лесу обитают монстры, твари черного мага.",
                "Будь осторожен чем дольше ты в лесу тем больше их появляется поблизости");
            getch();
            intface.subs("<Старец> - нам нужно 20 желтогривов. Как только соберешь уходи из леса",
                "");
            iwasoldman2 = false;
            iwasoldman2delay = true;
            

        }
        if (iwasoldman2delay == true) {
            intface.subs("<Старец> - нам нужно 20 желтогривов. Как только соберешь уходи из леса",
                "");

            nscore = 4;
            sci++;
            gotoforest = true;
            if (sci >= subtimming * nscore)
                iwasoldman2delay = false;
        }
        if (boy.x == 119 && boy.y > 10 && boy.y < 20 && gotoforest == true) //  17, 119
            break;
        
      

        if (make_move(map.forest) == 1) { ////////.............
            game_iter++;

        }
        else {
;           sci--;
        }
        
        clear();

        map.show_map();
        boy.move_boy(map.forest);

        intface.draw(boy.hp, boy.count_of_m, boy.invent);

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
}

void level_forest() {

    clear();

    int nscore = 1;
    int sci = 0;
    bool igotall = true;
    bool gotoborder = false;

    boy.x = 1;
    my_map map(width, length, 2);
    map.show_map();

    iface intface;
    intface.draw(10, 0, boy.invent);

    monsters_family* badboys = new monsters_family(map.forest, monsters[0]);


    
    while (true) {

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
        if (gotoborder == true && boy.x == 0 && boy.y > 10 && boy.y < 20) 
            break;

        if (game_iter % 100 == 0) {
            badboys->give_some_boys_rand(monsters[0]);
          /*  badboys->give_some_boys_rand(monsters[1]);*/
        }
           

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

        if(move)
            boy.hp -= badboys->monsters_move(0);
        else
            badboys->monsters_move(1);

         

        intface.draw(boy.hp, boy.count_of_m, boy.invent);

    }

    getch();
    delete badboys;
 }

void level_back_ff() {

    boy.x = 119;

    my_map map(width, length, 1);
    map.show_map();
    boy.move_boy(map.forest);
    iface intface;
    intface.draw(10, 0, boy.invent);



   
    bool gotooldman = true;
    bool iwasoldman1 = true;
    bool ireadom1 = true;
    bool gotoborder = false;

    int nscore = 0;
    int sci = 0;

    while (true) {
        //mvprintw(17, 119, "2"); // 
        if (gotooldman == true) {
            nscore = 1;
        }
        if (boy.x == 8 && boy.y == 19 && iwasoldman1 == true) {

            intface.subs(" <Старец> - Ты молодец ученик мой, тв преодолел тяжелое испытание ",
                "но нас ждет многое впереди...");
            getch();

            intface.subs(" <Старец> - Я приготовлю зелье c помощью которого ты сможешь атаковать ",
                "монстра в ближнем бою. Время действия зелья ограничено.");
            getch();

            intface.subs("Теперь тебе нужно отправиться в заброшенную деревню, ",
                "которая находится на окраине леса.");
            getch();

            intface.subs("Там, в одном из домов, который находится в самой глубине деревни." ,
                " лежит лук, который когда-то принадлежал великому охотнику.");
            getch();

            intface.subs("Ступай по дороге вверх по реке, собирай грибы по дороге",
                "На пути будут встречаться различные монстры применяй зелья чтобы атаковать");
            getch();

            boy.add_to_invent("Ловушка", 'o', 5, COLOR_PAIR(10), 1);

            iwasoldman1 = false;
            gotooldman = false;

        }
        if (iwasoldman1 == false && ireadom1 == true) {
            intface.subs("Ступай по дороге вверх по реке, собирай грибы по дороге",
                "На пути будут встречаться различные монстры применяй зелья чтобы атаковать");
            nscore = 2;
            sci++;
            gotoborder = true;
            if (sci >= subtimming * nscore)
                ireadom1 = false;

        }
        if (boy.x > 30 && boy.x < 38 && boy.y == 0 && gotoborder == true) {
            break;
        }
        switch (nscore)
        {
        case 1:
            intface.score("Возращайтесь на базу");
            break;

        case 2:
            intface.score("Отправляйтесь в деревню");
            break;

        default:
            break;
        }


        if (make_move(map.forest) == 1) { ////////.............
            game_iter++;
        }
        else {
             sci--;
        }

        clear();

        map.show_map();
        boy.move_boy(map.forest);

        intface.draw(boy.hp, boy.count_of_m, boy.invent);
        game_iter++;

    }
}

void level_way_to_village() {

    boy.y = 27;

    int n = 4;
    my_map map(width, length, 3);
    map.show_map();
    boy.move_boy(map.forest);
    iface intface;
    intface.draw(boy.hp, 0, boy.invent);

    monsters_family* badboys = new monsters_family(map.forest, monsters[0]);
    badboys->give_some_boys_rand(monsters[1]);


    bool gotovil = true;
    bool iwasoldman1 = true;
    bool ireadom1 = true;
    bool gotoborder = false;

    int nscore = 0;
    int sci = 0;

    for (int i = 0; i < n; i++) {

        badboys->give_some_boys_rand(monsters[0], 20, 29, 0, 100);
        badboys->give_some_boys_rand(monsters[0], 20, 29, 0, 100);
        badboys->give_some_boys_rand(monsters[1], 20, 29, 0, 100);
    }

    badboys->monsters_move(1);


    while (true) {
        //mvprintw(17, 119, "2"); // 
        if (gotovil == true) {
            nscore = 1;
        }

        
        
        /*if (boy.x > 30 && boy.x < 38 && boy.y == 0 && gotoborder == true) {
            break;
        }*/
        switch (nscore)
        {


        case 1:
            intface.score("Отправляйтесь в деревню");
            break;

        case 2:
            intface.score("Отправляйтесь в деревню");
            break;

        default:
            break;
        }


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
        game_iter++;

    }
}

 int main()
 {
    std::system("chcp 1251");


    initscr();
    curs_set(0);
    noecho();
    start_color();
    colors_pairs();
    monsters_data();

    iface init;
    
    if (init.start_game()) {
        while (true) { // Основной ход

            level_start();
            level_forest();

            if (boy.hp == 0) {
                boy.boy_reset(start_pos_x, start_pos_y);
                continue;
            }

            level_back_ff();
            boy.boy_reset(start_pos_x, start_pos_y);

        }
    }
    else {
        clear();
        while (true) { // Поуровневый режим

            mvprintw(7, 15, "Choose level");
            int lv = getch();
            clear();

            switch (lv)
            {
            case 48:
                level_start();

            case 49:
                if (lv == 49) {
                    boy.count_of_rm = 10;
                }
                level_forest();

            case 50:
                if (lv == 50) {
                    boy.count_of_m = 20;
                    boy.count_of_rm = 10;
                    boy.hp = 8;
                    boy.add_to_invent("Желтогрив", '.', 20, COLOR_PAIR(8),0);
                    boy.add_to_invent("Краснолгазик", (char)133, 10, COLOR_PAIR(22), 0);
                    boy.add_to_invent("Желтогр", '^', 20, COLOR_PAIR(8), 0);
                    boy.add_to_invent("Краснолгазк", '"', 10, COLOR_PAIR(22), 0);
                    boy.add_to_invent("Краснолгазик", (char)133, 10, COLOR_PAIR(22), 0);

                }
                level_back_ff();

            case 51:
                if (lv == 51) {
                    boy.count_of_m = 20;
                    boy.count_of_rm = 10;
                    boy.hp = 8;
                    boy.add_to_invent("Желтогрив", '.', 20, COLOR_PAIR(8), 0);
                    boy.add_to_invent("Краснолгазик", (char)133, 10, COLOR_PAIR(22), 0);
                    boy.add_to_invent("Ловушка", 'o', 5, COLOR_PAIR(10), 1);

                }
                level_way_to_village();
            }
            clear();
            boy.boy_reset(start_pos_x, start_pos_y);
        }
        
    }
       


    endwin();
    
   

    for (monster_type* monster : monsters) {
        delete monster;
    }

 }
