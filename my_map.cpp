#include <my_map.h>
#include <random>
#include <file_tools.h>
#include <curses.h>
#include <iostream>
#include <unordered_map>

#define PRINT_CHAR(obj, color) \
    do { \
        attron(color); \
        addch(obj); \
        attroff(color); \
    } while (0)

my_map::my_map(int width_of_map, int length_of_map, int lv) : width(width_of_map), length(length_of_map), level(lv) {
    forest = new char* [length];
    create_map(level);
}

void my_map::create_map(int level) {
    make_claen_map();
    file_tools ft;

    switch (level) {
    case 1:
        ft.get_data_ff(base_of_map, "river2.txt");
        add_to_map(base_of_map, 10, 0);

        add_trees(10, 12, 100); // y x
        add_trees(27, 87, 50);

        add_to_map(home, 6, 18); // y x
        break;

    case 2:
        add_trees(300);
        add_mushrooms('.', 20, 120, 29);
        add_mushrooms(133, 30, 120, 29);
        break;

    case 3:
        ft.get_data_ff(base_of_map, "way_to_village.txt");
        add_to_map(base_of_map, 0, 0);
        add_trees(100);
        add_mushrooms(133, 20, 120, 29);
        add_mushrooms('.', 5, 120, 29);
        add_mushrooms(',', 3, 120, 29);
        break;

    case 4:
        ft.get_data_ff(base_of_map, "Village.txt");
        add_to_map(base_of_map, 0, 0);
        break;

    default:
        break;
    }
}

void my_map::show_map() {
    // Таблица цветов для символов
    std::unordered_map<char, int> color_map = {
        {'~', COLOR_PAIR(12)},
        {'1', COLOR_PAIR(14)},
        {'.', COLOR_PAIR(8)},
        {'_', COLOR_PAIR(8)},
        {'|', COLOR_PAIR(8)},
        {'g', COLOR_PAIR(17)},
        {'S', COLOR_PAIR(19)},
        {',', COLOR_PAIR(28)},
        {'o', COLOR_PAIR(28)}
    };

    int default_color = COLOR_PAIR(4);

    for (int i = 0; i < length; i++) {
        char* str = forest[i];
        for (int j = 0; j < width; j++) {
            char c = *str;


            if (c == (char)133) {
                attron(COLOR_PAIR(22));
                addch(133); 
                attroff(COLOR_PAIR(22));
            }
            else {

                int color = default_color;

                if (color_map.count(c)) {
                    color = color_map[c];
                }

                PRINT_CHAR(c, color);
            }

            str++;
        }
    }
}

my_map::~my_map() {
    for (int i = 0; i < length; i++)
        delete[] forest[i];
    delete[] forest;
}

void my_map::make_claen_map() {
    for (int i = 0; i < length; i++) {
        forest[i] = new char[width];
        for (int j = 0; j < width; j++) {
            forest[i][j] = ' ';
        }
    }
}

void my_map::add_to_map(std::vector<std::vector<char>> addon, int posx, int posy) {
    for (int i = 0; i < addon.size(); i++) {
        for (int j = 0; j < addon[i].size(); j++) {
            forest[i + posy][j + posx] = addon[i][j];
        }
    }
}

void my_map::add_mushrooms(char obj, int count, int posx, int posy) {
    for (int i = 0; i < count; ++i) {
        int rx = random_x();
        int ry = random_y();
        if (forest[ry][rx] == ' ' && ry < posx && rx > posy)
            forest[ry][rx] = obj;
        else
            i--;
    }
}

void my_map::add_trees(int count) {
    for (int i = 0; i < count; ++i) {
        int rx = random_x();
        int ry = random_y();
        if (forest[ry][rx] == ' ')
            forest[ry][rx] = 'T';
        else
            i--;
    }
}

void my_map::add_trees(int posx1, int posy1, int posx2, int posy2, int count) {
    for (int i = 0; i < count; ++i) {
        int rx = random_x();
        int ry = random_y();

        if (forest[ry][rx] == ' ' && ry < posx1 && rx > posy1 && ry < posx2 && rx > posy2)
            forest[ry][rx] = 'T';
        else
            i--;
    }
}

void my_map::add_trees(int posx, int posy, int count) {
    for (int i = 0; i < count; ++i) {
        int rx = random_x();
        int ry = random_y();

        if (forest[ry][rx] == ' ' && ry < posx && rx > posy)
            forest[ry][rx] = 'T';
        else
            i--;
    }
}

int my_map::random_x() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disx(1, width - 1);
    return disx(gen);
}

int my_map::random_y() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disy(1, length - 1);
    return disy(gen);
}

