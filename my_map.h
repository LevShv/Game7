#pragma once
#include <vector>
#include <string>

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

    void print_char(char obj, int color);
    /*void print_str(int color)*/

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
    {'|', '1', '1', '1', '1', 'I', 'I', 'I', '|'},
    {'|', '_', '_', '_', '_', '_', '_', '_', '|'}
    };

    std::vector<std::vector<char>> base_of_map; 
};

