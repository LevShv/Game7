#include "level.h"


Level::Level(my_boy& boy, int map_type)
: boy(boy), map(width, length, map_type) 
{

}

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
    case 27:
        pause();
        return 0;
    }
   

    return 0;
}

void Level::pause()
{
    int choice = intface.pause_menu();

    if (choice == 1) {

        // загрузка
        // number_of_loading
        // int res = init.load();
        // if(res == 27)
        //      pause();
        // else
        // { 
        // download = true;
        // nuber_of_loading = res;
        // exit_ = true;

    }
     
    if (choice == 2)
        exit_ = true;
    
}





