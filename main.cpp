
#include <curses.h>
#include <my_map.h>
#include <my_boy.h>
#include <monster.h>
#include <scary_monster.h>
#include <monsters_family.h>
#include "iface.h"
#include <locale.h>

int level = 0;


int width = 120;
int length = 28;

int start_pos_x = 115; // 59
int start_pos_y = 20; // 21

int subtimming = 10;

int game_iter = 1;
my_boy boy(start_pos_x, start_pos_y);

void colors_pairs() {

    init_color(8, 900, 100, 100); // серый нижний bar
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

    init_pair(10, COLOR_RED, 257);

    init_pair(11, COLOR_BLUE, COLOR_BLUE); // вода
    init_pair(12, COLOR_BLUE, 258); // край воды 
    
    init_pair(13, 258, 258); // Вода...
    init_pair(14, 259, 259); // Мост
    init_pair(15, 260, 260); // дорожка
    
    init_pair(16, COLOR_BLUE, 259); // дорожка с персонажем

    init_pair(17, COLOR_WHITE, COLOR_WHITE); // кровать
    init_pair(18, COLOR_BLUE, COLOR_WHITE); // Персонаж на кровати

    init_pair(19, 8, 259); // Серый старец дома

    init_pair(20, 3, COLOR_BLACK); // Серый старец дома
    init_pair(21, COLOR_WHITE, COLOR_BLACK); // Subs
    init_pair(22, COLOR_RED, 257); // Красный гриб

}

void make_move() {
    switch (getch()) {
    case 'w':
        if (0 < boy.y) {
            boy.y--;

        }
        break;
    case 's':
        if (boy.y < length - 1) {
            boy.y++;

        }
        break;
    case 'a':
        if (boy.x > 0) {
            boy.x--;

        }
        break;
    case 'd':
        if (boy.x < width - 1) {
            boy.x++;

        }
        break;
    case 'q':
        break;

    }
}

void make_move(monsters_family*& badboys) {
    switch (getch()) {
    case 'w':
        if (0 < boy.y) {
            boy.y--;
            badboys->find(boy.x, boy.y);
        }
        break;
    case 's':
        if (boy.y < length - 1) {
            boy.y++;
            badboys->find(boy.x, boy.y);
        }
        break;
    case 'a':
        if (boy.x > 0) {
            boy.x--;
            badboys->find(boy.x, boy.y);
        }
        break;
    case 'd':
        if (boy.x < width - 1) {
            boy.x++;
            badboys->find(boy.x, boy.y);
        }
        break;
    case 'q':
        break;

    }
}

void level_start()
{
    

    my_map map(width, length,1);
    map.show_map();
    boy.move_boy(map.forest);
    iface intface;

    

    bool gotooldman = true;

    bool iwasoldman1 = true;
    bool ireadom1 = false;
    bool spawn_mushroom = false;
    bool ifindall = true;
    bool iwasoldman2 = false;
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
            map.add_redmushrooms(10, 27, 87);
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
                "Тебе нужно в мрачный лес по заросшей тропе вниз по реке ");
            getch();
            intface.subs("<Старец> - В том лесу обитают монстры, твари черного мага.",
                "Будь осторожен чем дольше ты в лесу тем больше их появляется поблизости");
            getch();
            intface.subs("<Старец> - нам нужно 20 желтогривов. Как только соберешь уходи из леса",
                "");
            getch();
            nscore = 4;
            sci++;
            gotoforest = true;
            if (sci >= subtimming * nscore)
                iwasoldman2 = false;

        }
        if (boy.x == 119 && boy.y > 10 && boy.y < 20 /*&& gotoforest == true*/) //  17, 119
            break;
        
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
        default:
            break;
        }

        make_move();        
        clear();

        map.show_map();
        boy.move_boy(map.forest);

        intface.draw(boy.hp, boy.count_of_m);
        game_iter++;

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

    monsters_family* badboys = new monsters_family(map.forest);

    while (true) {

        if (boy.hp == 0) {
            intface.game_over();
            getch();
            exit(1);
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

        if (game_iter % 100 == 0)
            badboys->give_some_boys_rand();

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
        make_move(badboys);
        clear();

        map.show_map();
        boy.move_boy(map.forest);

        boy.hp -= badboys->monsters_move();
        intface.draw(boy.hp, boy.count_of_m);
        game_iter++;

        

    }

    getch();
    delete badboys;
 }
 int main()
 {
    std::system("chcp 1251");


    initscr();
    curs_set(0);
    noecho();
    start_color();
    colors_pairs();
  
    level_start();
    level_forest();

    endwin();
   

}
