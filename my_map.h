#pragma once
class my_map
{
public:

    my_map(int width_of_map, int length_of_map);
    void show_map();
    ~my_map();
    
private:

    int width;
    int length = 30;
    char** map;
    void map_gen();

};

