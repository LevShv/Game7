#include "curses.h"
#include "iface.h"
#include "my_boy.h"
#include <filesystem>
#include <iostream>


iface::iface() {

    
}

void iface::draw(int boy_hp, int count_ofm, std::vector<invent_thing> &invent)
{
    Bckg(28, 31, 0, 120, COLOR_PAIR(2));
    draw_hp_boy(boy_hp);
    draw_slots(invent);
}

void iface::game_over() {
        
    Bckg(10,15,40,80,COLOR_PAIR(21));

    mvprintw(13, 55, "СмЭрть");

}

void iface::game_win() {

    Bckg(10,15,40,80,COLOR_PAIR(21));
       
    mvprintw(13, 55, "Win");

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
    
        switch (getch())
        {
        case 48:
            return 0;

        case 49:
            return 1;

        case 50:
            return 2;

        case 51:
            return 3;

        case 27:
            return 27;
        }
    }
}

int iface::main_menu(int button_save) {


    bool selected = false;
    int button = button_save;

    while (!selected) {

        Bckg(0, 29, 0, 120, COLOR_PAIR(29));
        Bckg_effect();
        cmvprintw(5, 55, "GAME7.EXE", COLOR_PAIR(32));

            
        Bckg(8, 10, 44, 75, (button == 0) ? COLOR_PAIR(31) : COLOR_PAIR(30));
        cmvprintw(9, 55, "Новая игра", (button == 0) ? COLOR_PAIR(31) : COLOR_PAIR(3)); // 1

        Bckg(13, 15, 44, 75, (button == 1) ? COLOR_PAIR(31) : COLOR_PAIR(30));
        cmvprintw(14, 52, "Поуровневый режим", (button == 1) ? COLOR_PAIR(31) : COLOR_PAIR(3)); // 2

        Bckg(18, 20, 44, 75, (button == 2) ? COLOR_PAIR(31) : COLOR_PAIR(30));
        cmvprintw(19, 55, "Загрузить", (button == 2) ? COLOR_PAIR(31) : COLOR_PAIR(3)); // 3

        refresh();


        switch (getch()) {

        case 'w': 
            button = (button - 1 + 3) % 3; 
            break;

        case 's': 
            button = (button + 1) % 3; 
            break;

        case 10: 
            selected = true;
            break;

        default:
            break;
        }
    }
     
    switch (button) {

    case 0:
        start_game();
        return 0;

    case 1:
        return 1;

    case 2:
        return 2;

    }
    return 0;
}

int iface::pause_menu()
{

    bool selected = false;
    int button = 0;

    while (!selected) {

        int bsx = 44; // Начальная координата X
        int bex = 75; // Конечная координата X
        int bsy = 7;
        
        int height = 2; // Высота кнопки
        int between = 3;

        Bckg(4, 21, 42, 77, COLOR_PAIR(30));
        /*Bckg_effect();*/
        cmvprintw(5, 57, "Пауза", COLOR_PAIR(23));


        Bckg(bsy, bsy + height, bsx, bex, (button == 0) ? COLOR_PAIR(31) : COLOR_PAIR(33));
        cmvprintw(bsy + 1, 55, "Продолжить", (button == 0) ? COLOR_PAIR(31) : COLOR_PAIR(33)); // 1
        bsy += between + height;

        //Bckg(bsy, bsy + height, bsx, bex, (button == 1) ? COLOR_PAIR(31) : COLOR_PAIR(33));
        //cmvprintw(bsy + 1, 55, "Сохранить", (button == 1) ? COLOR_PAIR(31) : COLOR_PAIR(33)); // 2
        //bsy += between + height;

        Bckg(bsy, bsy + height, bsx, bex, (button == 1) ? COLOR_PAIR(31) : COLOR_PAIR(33));
        cmvprintw(bsy + 1, 55, "Загрузить", (button == 1) ? COLOR_PAIR(31) : COLOR_PAIR(33)); // 3
        bsy += between + height;

        Bckg(bsy, bsy + height, bsx, bex, (button == 2) ? COLOR_PAIR(31) : COLOR_PAIR(33));
        cmvprintw(bsy + 1, 50, "Выйти в главное меню", (button == 2) ? COLOR_PAIR(31) : COLOR_PAIR(33)); // 4
        bsy += between + height;

        refresh();


        switch (getch()) {

        case 'w':
            button = (button - 1 + 3) % 3; //!
            break;

        case 's':
            button = (button + 1) % 3;
            break;

        case 10:
            selected = true;
            break;

        case 27:
            return 0;

        default:
            break;
        }
    }

    switch (button) {

    case 0:
        return 0;

    case 1:
        return 1;

    case 2:

        return 2;
    //case 3:

    //    return 3;

    }
    return 0;


}

std::string iface::save_screen()
{
    std::string path;

    bool selected = false;
    int button = 0;

    std::string directory = ".";
    std::vector<std::string> saveFiles = getPlayerSaveFiles(directory);

    int Count_of_saves = saveFiles.size();
   
    while (!selected) {

        int bsx = 44; // Начальная координата X
        int bex = 75; // Конечная координата X
        int bsy = 7;

        int height = 2; // Высота кнопки
        int between = 3;

        Bckg(0, 29, 0, 120, COLOR_PAIR(29));
        Bckg_effect();

        Bckg(4, 21, 41, 79, COLOR_PAIR(30));
        Bckg(11, 20 , 43, 77, COLOR_PAIR(35));

        cmvprintw(5, 55, "Загрузить", COLOR_PAIR(23));


        Bckg(bsy, bsy + height, bsx, bex, (button == 0) ? COLOR_PAIR(31) : COLOR_PAIR(33));
        cmvprintw(bsy + 1, 57, "Новое", (button == 0) ? COLOR_PAIR(31) : COLOR_PAIR(33)); // 1
        bsy += 4;

        for (int i = 0; i < Count_of_saves; i++) {
            cmvprintw(bsy + i, 43, saveFiles[i].c_str(), (button == i+1) ? COLOR_PAIR(31) : COLOR_PAIR(33));
            
        }

        refresh();

        switch (getch()) {

        case 'w':
            button = (button - 1 + (Count_of_saves+1)) % (Count_of_saves+1); //!
            break;

        case 's':
            button = (button + 1) % (Count_of_saves + 1);
            break;

        case 10:

            selected = true;

            if (button == 0) 
                path = new_file_name();
            else 
                path = saveFiles[button-1];

            saveFiles = getPlayerSaveFiles(directory);
            Count_of_saves = saveFiles.size();
            break;

        case 27:

            return 0;
            
        case 'i':

            delete_save(saveFiles[button - 1]);
            saveFiles = getPlayerSaveFiles(directory);
            Count_of_saves = saveFiles.size();

        default:
            break;
        }
    }
    clear();
   return path;
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

void iface::Bckg(int start_row, int end_row, int start_col, int end_col, int color_pair) {
    attron(color_pair);

    for (int row = start_row; row <= end_row; row++) {
        for (int col = start_col; col <= end_col; col++) {
            mvprintw(row, col, " ");
        }
    }

    attroff(color_pair);
}

void iface::clean_left_corner()
{
    Bckg(28, 31, 0, 50, COLOR_PAIR(2));
}

void iface::cmvprintw(int y, int x, const char* text, int color_pair)
{
    attron(color_pair);
    mvprintw(y, x, text);
    attroff(color_pair);

}

void iface::Bckg_effect()
{
    int count_of_stars = 45;
    attron(COLOR_PAIR(32));

    for (int i = 0; i < count_of_stars; i++) {

        
        mvaddch(random_y(), random_x(), '*');

    }
    attroff(COLOR_PAIR(32));

}

int iface::random_x()
{

    std::random_device rd;  // Используется для получения начального значения (seed)
    std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)

    std::uniform_int_distribution<> disx(1, 120 - 1); // Равномерное распределение от 0 до 

    return disx(gen);
}

int iface::random_y()
{

    std::random_device rd;  // Используется для получения начального значения (seed)
    std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)

    std::uniform_int_distribution<> disy(1, 29 - 1);

    return disy(gen);
}

std::vector<std::string> iface::getPlayerSaveFiles(std::string& directory)
{
    std::vector<std::string> saveFiles;
    namespace fs = std::filesystem;

    for (auto& entry : fs::directory_iterator(directory)) 
    {
        if (entry.is_regular_file()) 
        { 
            std::string filename = entry.path().filename().string(); 
            if (filename.find("player_save_") == 0) { 
                saveFiles.push_back(filename); 
            }
        }
    }

    return saveFiles;
}

void iface::delete_save(std::string filename)
{
    namespace fs = std::filesystem;

    if (fs::exists(filename))
        fs::remove(filename);
       

}

std::string iface::new_file_name()
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm tm;

    localtime_s(&tm, &now_time_t);

    std::ostringstream filename_stream;

    filename_stream << "player_save_" << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".txt";

    return filename_stream.str();
}

/*void iface::button(int start_row, int end_row, int start_col, int end_col, int color_pair_bckg, int y, int x, const char* text, int color_pair_text)
{
    Bckg(start_row, end_row, start_col, end_col, color_pair_bckg);
    cmvprintw(19, 55, "Загрузить", COLOR_PAIR(3));

}*/


