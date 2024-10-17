#pragma once
class my_map
{
public:

    my_map();
    void show_map();
    ~my_map();

private:

    int width = 120;
    int length = 30;
    char** map;
    void map_gen();

};

