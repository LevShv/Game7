
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <curses.h>
#include <my_map.h>

class my_boy {

public:

    int x;
    int y;

    my_boy() {}

    void move_boy() {
        mvprintw(y, x, "0");
    }

private:
};
//bool border_check()
//{
//    return ((boy.x > 0 )&()&()&())
//}
int main()
{ 
    int width = 120;
    int length = 30;
    int frame_rate = 100;

    system("chcp 1251");

    initscr();
    curs_set(0);
    noecho();
   /* timeout(frame_rate);*/

    my_map map(width, length);
    map.show_map();

    my_boy boy;
    boy.x = 0;
    boy.y = 0;
   

    while (true) {
        switch (getch()) {
        case 'w':
            if (0 < boy.y) { //0<y<30
                boy.y--;
            }
            break;
        case 's':
            if (boy.y < length) {
                boy.y++;
            }
            break;
        case 'a':
            if (boy.x > 0) {
                boy.x--;
            }
            break;
        case 'd':
            if (boy.x < width) {
                boy.x++;
            }
            break;
      /*  case 'q':

            stop*/
        default:
            break;
        }
      /*   timeout(100);*/
        clear();

        map.show_map();
        boy.move_boy();
        

        

    }
    
    getch();
    endwin();
   /* delete map;*/
   /* vec start_pos{ 10,10 };
    vec step{ 1,0 };

    int framerate = 100;*/
}
