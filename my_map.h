#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <curses.h>

class my_map
{
public:

    my_map(int width_of_map, int length_of_map, int lv);
    void create_map(int level);
    void show_map();
    char** forest;
   
    void add_mushrooms(char obj, int count, int posx, int posy);

    ~my_map();
    
private:
    char vline = (char)151; // 151 горизонт
   
    int level;
    int width;
    int length;

    int random_x();
    int random_y();

    void make_claen_map();
    void add_to_map(std::vector<std::vector<char>> addon, int posx, int posy);

    void add_trees(int count);
    void add_trees(int posx, int posy, int count);
    void add_trees(int posx1, int posy1, int posx2, int posy2, int count);
    

    std::vector<std::vector<char>> home = {
    {'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_'},
    {'|', 'S', '1', '1', '1', '1', '1', '1', '1', '1', '1', '|'},
    {'|', '1', '1', '|', '1', '1', '1', '1', '1', '1', '1', '|'},
    {'|', '_', '_', '|', '1', '_', '_', '_', '_', '_', '1', '|'},
    {'|', '1', '1', '1', '1', '1', '1', '1', '|'},
    {'|', '1', '1', '1', '1', '1', '1', '1', '|'},
    {'|', '_', '_', '_', '_', '_', '_', '_', '|'}
    };

    std::vector<std::vector<char>> base_of_map; 

    std::unordered_map<char, int> color_map = {

        {'~', COLOR_PAIR(12)},
        {'.', COLOR_PAIR(8)},
        {'_', COLOR_PAIR(45)},
        {'|', COLOR_PAIR(8)},
        {'g', COLOR_PAIR(17)},
        {'S', COLOR_PAIR(19)},
        {',', COLOR_PAIR(28)},
        {'o', COLOR_PAIR(28)},
        {'2', COLOR_PAIR(14)},
        {'=', COLOR_PAIR(46)},
        {'\\', COLOR_PAIR(8)},
        {'/', COLOR_PAIR(8)},
        {133, COLOR_PAIR(22)},

        // default

        {'T', COLOR_PAIR(4)},
        {' ', COLOR_PAIR(4)}
        /*{')', COLOR_PAIR(8)}*/

       /* {'T', COLOR_PAIR(44) }*/
    };

};

