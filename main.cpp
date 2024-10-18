
#include <random>
#include <curses.h>
#include <my_map.h>
#include "my_boy.h"
#include <monster.h>
#include <set>
#include <vector>



int main()
{ 
    int width = 120;
    int length = 30;
    int frame_rate = 100;

    int start_pos_x = 0;
    int start_pos_y = 0;

    system("chcp 1251");

    initscr();
    curs_set(0);
    noecho();
   /* timeout(frame_rate);*/

    my_map map(width, length);
    map.show_map();

    my_boy boy(start_pos_x,start_pos_y);
    monster W(5, 5, width, length);

    while (true) {
        switch (getch()) {
        case 'w':
            if (0 < boy.y) { //0<y<30
                boy.y--;
            }
            break;
        case 's':
            if (boy.y < length-1) {
                boy.y++;
            }
            break;
        case 'a':
            if (boy.x > 0) {
                boy.x--;
            }
            break;
        case 'd':
            if (boy.x < width-1) {
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
        boy.move_boy(map.forest);
        W.move_monster(boy.x,boy.y,map.forest);
        
       /* refresh();*/
        

    }
    
    getch();
    endwin();
   /* delete map;*/
   /* vec start_pos{ 10,10 };
    vec step{ 1,0 };

    int framerate = 100;*/
}
