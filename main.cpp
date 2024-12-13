
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

int start_pos_x = 59;
int start_pos_y = 21;

int game_iter = 0;
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
    init_pair(21, COLOR_WHITE, COLOR_BLACK); // Серый старец дома
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

void level_start() {
    

    my_map map(width, length);
    map.show_map();
    boy.move_boy(map.forest);
    iface intface;

    bool gotooldman = true;
    int nscore = 0;
    while (true) {
        
        if (gotooldman == true){

            intface.subs("Мне надо спасти лес от злой напасти леса.","Надо встретиться с моим учителем - Старцем <S>");
            nscore = 1;
            if(game_iter % 5 == 0)
                gotooldman == false;

        }
        
        switch (nscore)
        {
            case 0:
                
            break;
           
            case 1:
                intface.score("Встретиться со старцем");
            break;
        default:
            break;
        }


            //// Текст иди к старому

        if (boy.hp == 0) {
            intface.game_over();
            getch();
            exit(1);
        }
        if (boy.count_of_m == 20) {
            intface.game_win();
            getch();
            exit(1);
        }
        make_move();
        //if (game_iter % 100 == 0)
            
        
        clear();

        map.show_map();
        boy.move_boy(map.forest);

        intface.draw(boy.hp, boy.count_of_m);
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
  
    level_start();
    /*my_map map(width, length);
    map.show_map();

    iface intface;

    monsters_family* badboys = new monsters_family(map.forest);

    while (true) {
        if (boy.hp == 0) {
            intface.game_over();
            getch();
            return 0;
        }
        if (boy.count_of_m == 20) {
            intface.game_win();
            getch();
            return 0;
        }
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
        if (game_iter % 100 == 0)
            badboys->give_some_boys_rand();

        clear();

        map.show_map();
        boy.move_boy(map.forest);

        boy.hp -= badboys->monsters_move();
        intface.draw(boy.hp, boy.count_of_m);
        game_iter++;
        
    }

    getch();*/
    endwin();
   /* delete badboys;*/

}
