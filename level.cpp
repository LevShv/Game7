#include "level.h"


Level::Level(my_boy& boy, int map_type)
: boy(boy), map(width, length, map_type) 
{

}

Level::Level(my_boy& boy, int map_type, std::vector<monster_type*>* monsters)
: boy(boy), map(width, length, map_type), monsters(monsters) {}

int Level::make_move(char** map) {

    switch (getch()) {
    case 'w':
        if (0 < boy.y) {
            boy.y--;
            return 1;
        }
        break;
    case 's':
        if (boy.y < length - 1) {
            boy.y++;
            return 1;
        }
        break;
    case 'a':
        if (boy.x > 0) {
            boy.x--;
            return 1;
        }
        break;
    case 'd':
        if (boy.x < width - 1) {
            boy.x++;
            return 1;
        }
        break;
    case '1':
        if (boy.invent.size() > 0 && boy.invent[0].usage)
            boy.do_something(0, map);
        return 0;
        break;
    case 'e':
        intface.show_invent(boy.invent);
        return 0;
        break;
    }
    return 0;
}

Level::~Level() {

}

