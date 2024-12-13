#pragma once
#include <vector>
#include <string>

class my_map
{
public:

    my_map(int width_of_map, int length_of_map);
    void create_map(int level);
    void show_map();
    char** forest;
   
    ~my_map();
    
private:
    

    int width;
    int length;

    int random_x();
    int random_y();

    void make_claen_map();
    void add_to_map(std::vector<std::vector<char>> addon, int posx, int posy);

    void add_trees(int count);
    void add_trees(int posx, int posy, int count);
    void add_trees(int posx1, int posy1, int posx2, int posy2, int count);
    
    void add_mushrooms();
    void get_data_ff(std::vector<std::vector<char>>& mapobj, std::string name);

    std::vector<std::vector<char>> home = {
    {'|', '_', '_', '_', '|'},
    {'|', 'o', 'r', 'l', '|'},
    {'|', '-', '-', '-', '|'}
    };

    std::vector<std::vector<char>> river; 
};

