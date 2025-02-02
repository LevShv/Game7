
#include <curses.h>
#include <iface.h>
#include <level_manager.h>
#include <Audio.h>

 void colors_pairs() {

    init_color(300, 165,165,165); // серый нижний bar
    init_color(257, 46, 139, 87); //  темно-зеленый цвет фона
    init_color(258, 0, 0, 128); // темно-синий
    init_color(259, 189, 183, 107); // бежевый
    init_color(260, 240, 230, 140); // светло-бежевый
    init_color(301, 213, 213, 213); // темно-серый для меню
    init_color(302, 0, 0, 0); // Цвет I


    init_pair(0, COLOR_WHITE, COLOR_BLACK); // default
    init_pair(1, COLOR_RED, COLOR_RED); // полоска здоровья
    init_pair(2, COLOR_BLACK, 8); // цвет "Boy"
    init_pair(3, COLOR_BLACK, 8); // цвет "Грибы"

    init_pair(4, COLOR_WHITE, 257); // темно-зеленый цвет фона
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

    init_pair(29, 257, 257); //фон главного меню
    init_pair(30, 8, 8); //фон кнопок главного меню

    init_pair(31, COLOR_BLACK,COLOR_WHITE); //цвет выбранной кнопки

    init_pair(32, COLOR_MAGENTA, 257); // цвет для эффекта

    init_pair(33, COLOR_WHITE, 301); // цвет кнопки в меню паузы
    init_pair(34, COLOR_WHITE, COLOR_BLACK);

    init_pair(35, 301, 301); // задник закгрузок / экран вы уверены?
    init_pair(36, COLOR_WHITE, 301); // цвет текста на экран вы уверены?

    init_pair(37, COLOR_WHITE, 257);
    init_pair(38, COLOR_WHITE, 8);

    init_pair(39, COLOR_RED, 301); // текст смерть

    init_pair(40, 302, COLOR_MAGENTA); // I
    init_pair(41, 302, COLOR_MAGENTA); // I на дороге

    init_pair(42, COLOR_YELLOW, 257); // o
    init_pair(43, COLOR_YELLOW, 259); // o на дороге

    //init_pair(44, /*303*/ COLOR_RED, 257); // T

    init_pair(45, COLOR_YELLOW, 259); // "_"
    init_pair(46, COLOR_WHITE, 259); // =

    init_pair(47, COLOR_YELLOW, COLOR_BLACK); // & healer

    init_pair(48, COLOR_WHITE, 257); // след от стрелы на траве
    init_pair(49, COLOR_WHITE, 259); // след от стрелы на дороге

    init_pair(50, COLOR_BLUE, COLOR_BLACK); // & power

    init_pair(51, COLOR_MAGENTA, 257); // Маг
    init_pair(52, COLOR_MAGENTA, 259); // Маг на дорге
}

 void call_manager(level_manager& Manager) {

     while (!Manager.all_levels_done()) {

         Manager.start_next_level();
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
    timeout(500);
    nodelay(stdscr, TRUE);

    track *my_track = new track();
    my_track->play(my_track->Main);

    iface init;
    
    int button_save = 0;
    int selection = 0;

  /*  init.game_over();*/
    //init.pause_menu();
    //init.save_screen();
   // init.load_screen();
 /*   if (!init.are_you_sure_screen()) exit(0);*/

    file_tools ft;

    level_manager Manager;

    while (true) {

        if (Manager.download) {

            Manager.download = false;
            call_manager(Manager);
        }
        else {

            Manager.reset();

            switch (init.main_menu(button_save)) {
            
            case 0:
               
                init.start_game();
                my_track->stop();
                call_manager(Manager);
               
                break;

            case 1:

                clear();

                button_save = 1;
                selection = init.level_selection();

                clear();

                if (selection == 27)
                    break;

                else {

                    Manager.currentLevelIndex = selection;
                    Manager.preset();
                    my_track->stop();
                    call_manager(Manager);

                    break;
                }

            case 2:
                if (Manager.load_game()) {
                    my_track->stop();
                    call_manager(Manager);
                }
                break;

            case 3:
                endwin();
                exit(0);
                break;
            }
            
        }    
    }
    endwin();

 }

