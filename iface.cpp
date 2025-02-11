
#include "iface.h"
#include "curses.h"
#include <button_table.h>

void iface::draw(int boy_hp, int count_ofm, std::vector<invent_thing> &invent)
{
    Bckg(28, 31, 0, 120, COLOR_PAIR(2));
    draw_hp_boy(boy_hp);
    draw_slots(invent);
}

int iface::game_over() {
        
    timeout(-1);
    
    bool selection = false;
    int num = 0;

    Bckg(8, 18, 38, 82, COLOR_PAIR(30));
    Bckg(9, 11, 40, 80, COLOR_PAIR(35));
    cmvprintw(10, 57, "СМЕРТЬ", COLOR_PAIR(39));
  

    button yes_but(0, "Возродиться", 14, 16, 42, 57, COLOR_PAIR(33), COLOR_PAIR(31));
    button no_but(1, "Выйти", 14, 16, 63, 78, COLOR_PAIR(33), COLOR_PAIR(31));

    while (!selection) {

        yes_but.draw(num);
        no_but.draw(num);

        switch (getch()) {

        case 'a':
            num = (num + 1) % 2;
            break;

        case 'd':
            num = (num + 1) % 2;
            break;

        case 10:
            if (num == 0) return 0;
            if (num == 1) return 1;
            break;
        }
    }

    getch();
}



void iface::subs(const char* a, const char* b)
{
    Bckg(3,6,20,100,COLOR_PAIR(21));

    mvprintw(4, 23, a);
    mvprintw(5, 23, b);
}

void iface::score(const char* a)
{
    cmvprintw(29, 85, "Цель: ", COLOR_PAIR(3));
    cmvprintw(29, 91, a, COLOR_PAIR(3));
}

void iface::show_invent(std::vector<invent_thing> &invent)
{
    int start_row = 10;
    int start_col = 42;
    int end_row = 18;
    int end_col = 80;

    bool exit = false;

    while (!exit) {

        Bckg(start_row, end_row, start_col - 2, end_col, COLOR_PAIR(2));
        cmvprintw(start_row + 1, (end_col + start_col) / 2 - 5, "Инвентарь", COLOR_PAIR(3));

        int j = 0;
        int k = 0;

        for (int i = 0; i < invent.size(); i++)
        {

            attron(invent[i].color);
            move(start_row + (j + 3), start_col + (k + 1));
            printw("%c",invent[i].icon);

            attroff(invent[i].color);

            attron(COLOR_PAIR(3));
            move(start_row + (j + 3), start_col + (k + 3));
            printw("%d", invent[i].count);
            attroff(COLOR_PAIR(3));
                

            if (posofptr == i) {

                cmvprintw(start_row + (j + 3), start_col + (k - 2), "->", COLOR_PAIR(23));
                    
            }

            if ((i + 1) % 3 == 0 && i != 0) {
                j = 0;
                k += 8;
            }

            else {
                j += 2;
            } 

                
        }
        refresh();

        switch (getch()) {
        case 'w':
            if (posofptr - 1 >= 0)
                posofptr -= 1;
            break;

        case 's':
            if (posofptr + 1 < invent.size())
                posofptr += 1;
            break;

        case 'a':
            if (posofptr - 3 >= 0)
                posofptr -= 3;
            break;

        case 'd':
            if (posofptr + 3 < invent.size())
                posofptr += 3;
            break;

        case '1':

            std::swap(invent[posofptr], invent[0]);
            clean_left_corner();
            draw_slots(invent);
                break;

        case '2':

            std::swap(invent[posofptr], invent[1]);
            clean_left_corner();
            draw_slots(invent);
                break;

        case 'e':
             exit = true;
             break;

        case 27:
            exit = true;
            break;
        }
           

    }
      
}

void iface::draw_slots(std::vector<invent_thing>& invent)
{
    if (invent.size() > 0) {
        cmvprintw(28, 15, ("[" + std::string(1, invent[0].icon) + "] " + invent[0].name += " <" + std::to_string(invent[0].count) + ">").c_str(), COLOR_PAIR(3));

    }
    if (invent.size() > 1 && invent[1].name != "") {
        cmvprintw(29, 15, ("[" + std::string(1, invent[1].icon) + "] " + invent[1].name += " <" + std::to_string(invent[1].count) + ">").c_str(), COLOR_PAIR(3));

    }
}

int iface::start_game()
{
    
    timeout(-1);
    clear();
    Bckg(0, 29, 0, 120, COLOR_PAIR(29));
    attron(COLOR_PAIR(4));

    mvprintw(5, 13, "Когда-то Лес был не просто местом — он был сердцем жизни, полным зелени,");
    mvprintw(6, 13, "звуков щебетания птиц и лёгкого шёпота ветра. Здесь царила гармония,");
    mvprintw(7, 13, "где каждый житель жил в согласии с природой.Однако, спустя время, его идиллия была разрушена.");
    getch();

    mvprintw(11, 13, "Древний маг, будучи одержимым тёмной силой, наложил заклинание, оставив после себя лишь пустоту и смерть.");
    mvprintw(12, 13, "Спокойные поля превратились в мрачные и опасные территории, где обитают ужасные монстры и порча.");
    mvprintw(13, 13, "Бывшие оазисы жизни сейчас наполнены страхом и тьмой.");
    getch();

    mvprintw(17, 13, "Но среди этого хаоса есть надежда");
    mvprintw(18, 13, "Молодой маг Нолиус и его учитель Старец Соломун собираются спасти лес от проклятья ");
    mvprintw(19, 13, "Вперёд, смелый искатель приключений! Твой путь тернист,");
    mvprintw(20, 13, "но только ты сможешь вернуть свет в этот когда-то прекрасный дом!");

    attron(COLOR_PAIR(4));

    if (getch() == 27)
        return 0;
    nodelay(stdscr, TRUE);
    clear();
    return 1;
}

int iface::level_selection()
{
    int level;
    bool chose = true;

    Bckg(0, 29, 0, 120, COLOR_PAIR(29));
    cmvprintw(5, 51, "Введите номер уровня", COLOR_PAIR(4)); 
   
    while (chose) {
    
        timeout(-1);
        char input = getch();

        if (input == 27)
            return 27;

        else if (input < 60 && input >= 48){
            return input - 48;
        }
    
    }
}

int iface::main_menu(int button_save) {

    bool selected = false;
    int num = button_save;
    int count = 4;

    button_table bt(44, 75, 6, 2, 3, COLOR_PAIR(3), COLOR_PAIR(31));

    bt.add("Новая игра");
    bt.add("Поуровневый режим");
    bt.add("Загрузить");
    bt.add("Выйти из игры");

    while (!selected) {

        Bckg(0, 29, 0, 120, COLOR_PAIR(29));
        Bckg_effect();
        cmvprintw(3, 55, "GAME7.EXE", COLOR_PAIR(32));

        bt.draw_once(num);
   
        refresh();

        switch (getch()) {

        case 'w': 
            num = (num - 1 + count) % count;
            break;

        case 's': 
            num = (num + 1 + count) % count;
            break;

        case 10: 
            selected = true;
            break;

        default:
            break;
        }
    }
    return num;
}

int iface::pause_menu()
{
    button_table bt(44, 75, 7, 2, 3, COLOR_PAIR(33), COLOR_PAIR(31));

    bt.add("Продолжить");
    bt.add("Загрузить");
    bt.add("Выйти в главное меню");

    Bckg(4, 21, 42, 77, COLOR_PAIR(30));
    cmvprintw(5, 57, "Пауза", COLOR_PAIR(23));

    return bt.draw_nget(0);

}

std::string iface::save_screen()
{
    file_tools ft;
    std::string path;

    bool selected = false;
    int num = 0;

    std::string directory = ft.save_directory();
    std::vector<std::string> saveFiles = ft.getPlayerSaveFiles();

    int Count_of_saves = saveFiles.size();

    button bt(0,"Новое", 44, 75, 7, 2, COLOR_PAIR(33), COLOR_PAIR(31));
   
    while (!selected) {

        int bsx = 44; 
        int bex = 75; 
        int bsy = 7;

        int height = 2; 
        int between = 3;

        Bckg(0, 29, 0, 120, COLOR_PAIR(29));
        Bckg_effect();

        Bckg(4, 21, 41, 79, COLOR_PAIR(30));
        Bckg(11, 20 , 43, 77, COLOR_PAIR(35));

        cmvprintw(5, 55, "Сохранить", COLOR_PAIR(23));


        Bckg(bsy, bsy + height, bsx, bex, (num == 0) ? COLOR_PAIR(31) : COLOR_PAIR(33));
        cmvprintw(bsy + 1, 57, "Новое", (num == 0) ? COLOR_PAIR(31) : COLOR_PAIR(33)); // 1
        bsy += 4;

        for (int i = 0; i < Count_of_saves; i++) {
            cmvprintw(bsy + i, 43, saveFiles[i].c_str(), (num == i+1) ? COLOR_PAIR(31) : COLOR_PAIR(33));
            
        }

        refresh();

        switch (getch()) {

        case 'w':
            num = (num - 1 + (Count_of_saves+1)) % (Count_of_saves+1); //!
            break;

        case 's':
            num = (num + 1) % (Count_of_saves + 1);
            break;

        case 10:

            selected = true;

            if (num == 0)
                path = ft.new_file_name();
            else 
                path = saveFiles[num -1];

            saveFiles = ft.getPlayerSaveFiles();
            Count_of_saves = saveFiles.size();
            break;

        case 27:

            return "0";
            
        case 'i':

            ft.delete_save(saveFiles[num - 1]);
            saveFiles = ft.getPlayerSaveFiles();
            Count_of_saves = saveFiles.size();

        default:
            break;
        }
    }
    clear();
   return path;
}

std::string iface::load_screen()
{
    file_tools ft;
    std::string path;

    bool selected = false;
    int num = 0;

    std::string directory = ft.save_directory();
    std::vector<std::string> saveFiles = ft.getPlayerSaveFiles();

    int Count_of_saves = saveFiles.size();


    while (!selected) {

        int bsx = 44; 
        int bex = 75; 
        int bsy = 7;

        int height = 2; // Высота кнопки
        int between = 3;

        Bckg(0, 29, 0, 120, COLOR_PAIR(29));
        Bckg_effect();

        Bckg(4, 21, 41, 79, COLOR_PAIR(30));
        Bckg(7, 20, 43, 77, COLOR_PAIR(35));

        cmvprintw(5, 55, "Загрузить", COLOR_PAIR(23));

        for (int i = 0; i < Count_of_saves; i++) {
            cmvprintw(bsy + i, 43, saveFiles[i].c_str(), (num == i) ? COLOR_PAIR(31) : COLOR_PAIR(33));

        }

        refresh();

        switch (getch()) {

        case 'w':
            num = (num - 1 + Count_of_saves) % Count_of_saves; //!
            break;

        case 's':
            num = (num + 1) % Count_of_saves;
            break;

        case 10:

            return saveFiles[num];


        case 27:

            return "0";

        case 'i':

            ft.delete_save(saveFiles[num - 1]);
            saveFiles = ft.getPlayerSaveFiles();
            Count_of_saves = saveFiles.size();

        default:
            break;
        }
    }
    clear();
    return path;
}

bool iface::are_you_sure_screen()
{
    bool selection = false;
    int num = 1;

    Bckg(8, 17, 38, 82, COLOR_PAIR(35));
    cmvprintw(9, 40,"Вы действительно хотите выйти?", COLOR_PAIR(36));
    cmvprintw(10, 40, "Весь несохраненный прогресс будет потерян", COLOR_PAIR(36));

    button yes_but(0, "Выйти", 13, 15, 42, 57, COLOR_PAIR(38), COLOR_PAIR(31));
    button no_but(1, "Остаться", 13, 15, 63, 78, COLOR_PAIR(38), COLOR_PAIR(31));

    while (!selection) {

        yes_but.draw(num);
        no_but.draw(num);


        switch (getch()) {

        case 'a':

            num = (num + 1) % 2;
            break;

        case 'd':
            num = (num + 1) % 2;
            break;

        case 10:
            if (num == 0) return 0;
            if (num == 1) return 1;
            break;

        case 27:
            return 1;
        }

    }

    getch();
}

void iface::draw_hp_boy(int hp) {

    cmvprintw(29, 46, "Boy", COLOR_PAIR(3));

    attron(COLOR_PAIR(1));
    int i = 0;
    for (i; i < 2 * hp; i++) {
        mvaddch(xposofhp, yposofhp + i, ' ');
    }
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(6));
    for (i; i < 20; i++) {
        mvaddch(xposofhp, yposofhp + i, 'p');

    }
    attroff(COLOR_PAIR(6));

}

void iface::draw_Count_of_mushrooms(int count_ofm) {

    attron(COLOR_PAIR(3));

    mvprintw(29, 20, "Gribi");
    char str[3];
    sprintf_s(str, "%d", count_ofm);
    mvprintw(29, 26, str);

    attroff(COLOR_PAIR(3));
}    

void iface::clean_left_corner()
{
    Bckg(28, 31, 0, 50, COLOR_PAIR(2));
}

void iface::Bckg_effect()
{
    int count_of_stars = 45;
    attron(COLOR_PAIR(32));

    for (int i = 0; i < count_of_stars; i++) {

        int x, y;
        randomi(x, y);
        mvaddch(x, y, '*');

    }
    attroff(COLOR_PAIR(32));

}

void iface::game_win() {

    timeout(1000);

    const char* credits[] = {
        "Поздравляем!",
        "Вы победили!",
        "",
        "Разработчик:",
        "Швецов Лев",
        "",
        "Дизайнеры карт:",
        "Швецов Лев",
        "Елена Якимова",
        "",
        "Музыка: ",
        "Павел Чуйкин",
        "Григорий Дорошенко",
        "",
        "Руководитель проекта:",
        "Никита Гоголев",
        "",
        "Тула 2024",
        "",
        "",
        "Спасибо за игру!",
        nullptr
    };

    int y = 30;
    int x = 52;

    while (true) {
        clear();

        for (int i = 0; credits[i] != nullptr; ++i) {
            mvprintw(y + i, x, "%s", credits[i]);
        }

        refresh();
        y--;

        if (y + static_cast<int>(sizeof(credits) / sizeof(credits[0])) < 0) {
            break;
        }

        int ch = getch();
        if (ch != ERR) {
            break;
        }
    }
}


