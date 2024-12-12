#pragma once
#include <vector>
class my_map
{
public:

    my_map(int width_of_map, int length_of_map);
    void create_map(int level);
    void show_map();
    char** forest;
    char matrix[3][5] = {
        {'|', '_', '_', '_', '|'},
        {'|', 'o', 'r', 'l', '|'},
        {'|', '-', '-', '-', '|'} // '\0' — символ конца строки
    };
    ~my_map();
    
private:
    

    int width;
    int length;

    int random_x();
    int random_y();

    void make_claen_map();
    void add_to_map(std::vector<std::vector<char>> addon, int posx, int posy);
    void add_trees();
    void add_mushrooms();
    
    std::vector<std::vector<char>> home = {
    {'|', '_', '_', '_', '|'},
    {'|', 'o', 'r', 'l', '|'},
    {'|', '-', '-', '-', '|'}
    };

};

