#pragma once
#include "curses.h"
#include <vector>
#include <my_boy.h>
#include <random>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream> 
#include <button_table.h>
#include <functional>


class iface {
public:

    iface();

    void draw(int boy_hp, int count_ofm, std::vector<invent_thing>& invent);
    void game_over();
    void game_win();
    void subs(const char* a, const char* b);
    void score(const char* a);
    void show_invent(std::vector<invent_thing> &invent);

    int start_game();
    int level_selection();
    int main_menu(int button_save);

    int pause_menu();
    std::string save_screen();


private:

    
    int posofptr = 0;

    int xposofhp = 29;
    int yposofhp = 50;

    void draw_hp_boy(int hp);
    void draw_Count_of_mushrooms(int count_ofm);
    void draw_slots(std::vector<invent_thing> &invent);

    void Bckg(int start_row, int end_row, int start_col, int end_col, int color_pair);
    void Bckg_effect();
    void clean_left_corner();
    void cmvprintw(int y, int x, const char* text, int color_pair);
    
    int random_x();
    int random_y();
    
    std::vector<std::string> getPlayerSaveFiles(std::string& directory);
    void delete_save(std::string filename);
    std::string new_file_name();
    
};
