#include "my_boy.h"
#include "curses.h"
#include <my_map.h>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream> 

my_boy::my_boy(int spx, int spy) : x(spx), y(spy) 
{
    xl = x;
    yl = y;
}

my_boy::my_boy() {

    x = 59;
    y = 21;
}

void my_boy::move_boy(char** map) {

    if (map[y][x] == ' ' || map[y][x] == '1' || map[y][x] == 'я') {
        if (map[y][x] == ' ') {

            print_me(COLOR_PAIR(7));
        }
        else if (map[y][x] == '1'){

            print_me(COLOR_PAIR(16));
        }
        else {

            print_me(COLOR_PAIR(18));
        }
    }

    else if (map[y][x] == '.' || map[y][x] == (char)133 || map[y][x] == ',') {

        if (map[y][x] == '.') {

            count_of_m++;
            add_to_invent("Желтогрив", '.', 1, COLOR_PAIR(8), 0);
        }

        if(map[y][x] == ',') {
           
            add_to_invent("Голубозубки", ',', 1, COLOR_PAIR(28), 0); //28
        }
            
        if((map[y][x] == (char)133))
        {
            count_of_rm++;
            add_to_invent("Краснолгазик", 133 , 1, COLOR_PAIR(22), 0);
        }

        print_me(COLOR_PAIR(7));
        map[y][x] = ' ';
    }
    else {

        x = xl;
        y = yl;
        
        if (map[y][x] == ' ') {

            print_me(COLOR_PAIR(7));
        }
        else {
            print_me(COLOR_PAIR(16));
        }

    }

    xl = x;
    yl = y;
 
}

void my_boy::boy_reset(int start_pos_x, int start_boy_y)
{
    hp = 10;
    x = start_pos_x;
    y = start_boy_y;
    count_of_m = 0;
    count_of_rm = 0;
}

void my_boy::add_to_invent(std::string name, char icon, int count, int color, bool usage)
{
    bool founded = false;
    for (int i = 0; i < invent.size(); i++)
    {
        if (invent[i].name == name) {
            invent[i].count++;
            founded = true;
            break;
        }
        
    }

    if (founded == false) {
        /*          ivent_thing var{ name, count };*/
        invent.push_back({ name, icon ,count ,color , usage});
    }
}

void my_boy::remove_thing(std::string name) {

    for (int i = 0; i < invent.size(); i++)
    {
        if (invent[i].name == name) {
            std::swap(invent[i], invent[invent.size() - 1]);
            invent.pop_back();
            break;

        }

    }
}

void my_boy::do_something(int num, char** map)
{
    switch (invent[num].icon)
    {
    case 'o':
        map[y][x] = 'o';
        invent[num].count--;
    default:
        break;
    }
}

void my_boy::save()
{
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm tm;

    localtime_s(&tm, &now_time_t); 

    std::ostringstream filename_stream;
    filename_stream << "player_save_" << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".txt";
    std::string filename = filename_stream.str();

    std::ofstream file(filename);
    if (!file.is_open()) {
        // Если файл не удалось открыть, выводим ошибку
        printw("Ошибка: не удалось сохранить игру!\n");
        refresh();
        return;
    }


    file << "hp: " << hp << "\n";

    file << "x: " << x << "\n";
    file << "y: " << y << "\n";

    file << "count_of_m: " << count_of_m << "\n";
    file << "count_of_rm: " << count_of_rm << "\n";

    file << "invent_size: " << invent.size() << "\n"; 
    for (const auto& item : invent) {
        file << item.name << " " << item.icon << " " << item.count << " " << item.color << " " << item.usage << "\n";
    }

    file.close();

    printw("Игра успешно сохранена в файл: %s\n", filename.c_str());
    refresh();

    
}

void my_boy::print_me(int color) {

    attron(color);
    move(y, x);
    printw("0");
    attroff(color);
}






