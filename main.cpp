
#include <curses.h>
#include <my_map.h>
#include <my_boy.h>
#include <monster.h>
#include <scary_monster.h>


int main()
{ 

    
    int width = 120;
    int length = 30;
    int frame_rate = 100;

    int start_pos_x = 1;
    int start_pos_y = 1;

  /*  system("chcp 1251");*/

    initscr();
    curs_set(0);
    noecho();
    nodelay(stdscr, TRUE);

 /*   hello_screen();*/

    my_map map(width, length);
    map.show_map();

    my_boy boy(start_pos_x,start_pos_y);

    scary_monster W (5, 5, width, length);

 

    while (true) {
        switch (getch()) {
        case 'w':
            if (0 < boy.y) {
                boy.y--;
                W.give_waythim(boy.x, boy.y, map.forest);
            }
            break;
        case 's':
            if (boy.y < length-1) {
                boy.y++;
                W.give_waythim(boy.x, boy.y, map.forest);
            }
            break;
        case 'a':
            if (boy.x > 0) {
                boy.x--;
                W.give_waythim(boy.x, boy.y, map.forest);
            }
            break;
        case 'd':
            if (boy.x < width-1) {
                boy.x++;
                W.give_waythim(boy.x, boy.y, map.forest);
            }
            break;
        case 'q':
            break;
          
        case ERR:
            int a = W.move_monster();
            break;
        }

        clear();

        map.show_map();
        boy.move_boy(map.forest);

    }
    
    getch();
    endwin();

}
