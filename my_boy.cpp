#include "my_boy.h"
#include "curses.h"
#include <my_map.h>
#include <fstream>
#include "file_tools.h"
#include <iface.h>

#define PRINT_BOY(color) \
    do { \
        attron(color); \
        move(y, x); \
        addch('0'); \
        attroff(color); \
    } while (0)

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

    if (map[y][x] == ' ' || map[y][x] == '1' || map[y][x] == '2' || map[y][x] == '�') {
        if (map[y][x] == ' ') {

            PRINT_BOY(COLOR_PAIR(7));
        }
        else if (map[y][x] == '1' || map[y][x] == '2'){

            PRINT_BOY(COLOR_PAIR(16));
        }
        else {

            PRINT_BOY(COLOR_PAIR(18));
        }
    }

    else if (map[y][x] == '.' || map[y][x] == (char)133 || map[y][x] == ',') {

        if (map[y][x] == '.') {

            count_of_m++;
            add_to_invent("���������", '.', 1, COLOR_PAIR(8), 0);
        }

        if(map[y][x] == ',') {
           
            add_to_invent("�����������", ',', 1, COLOR_PAIR(28), 0); //28
        }
            
        if((map[y][x] == (char)133))
        {
            count_of_rm++;
            add_to_invent("������������", 133 , 1, COLOR_PAIR(22), 0);
        }

        PRINT_BOY(COLOR_PAIR(7));
        map[y][x] = ' ';
    }
    /*else if (map[y][x] == 'g') {

       
        save();
    }*/
    else {

        x = xl;
        y = yl;
        
        if (map[y][x] == ' ') {

            PRINT_BOY(COLOR_PAIR(7));
        }
        else {
            PRINT_BOY(COLOR_PAIR(16));
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

void my_boy::add_to_invent(invent_thing thing)
{
    bool founded = false;
    for (int i = 0; i < invent.size(); i++)
    {
        if (invent[i].name == thing.name) {
            invent[i].count += thing.count;
            founded = true;
            break;
        }

    }

    if (founded == false) {
        invent.push_back(thing);
    }
}

bool my_boy::set_thing_count(std::string name, int count)
{
    for (int i = 0; i < invent.size(); i++)
    {
        if (invent[i].name == name) {
            invent[i].count = count;
            if (invent[i].count == 0) {
                std::swap(invent[i], invent[invent.size() - 1]);
                invent.pop_back();
               
            }
            return true;
        }
    }
    return false;
}

int my_boy::get_thing_count(std::string name)
{
    for (int i = 0; i < invent.size(); i++)
    {
        if (invent[i].name == name) {
            return invent[i].count;
        }
    }
    return 0;
}

void my_boy::check_invent_for_null(int num)
{
    if (invent[num].count == 0) {
        std::swap(invent[num], invent[invent.size() - 1]);
        invent.pop_back();
    }
}

//
//void my_boy::print_me(int color) {
//
//    attron(color);
//    move(y, x);
//    printw("0");
//    attroff(color);
//}






