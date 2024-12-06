
#include <curses.h>
#include <my_map.h>
#include <my_boy.h>
#include <monster.h>
#include <scary_monster.h>


int main()
{ 

    int width = 120;
    int length = 28;
    int frame_rate = 100;

    int start_pos_x = 69;
    int start_pos_y = 9;

  /*  system("chcp 1251");*/

    initscr();
    curs_set(0);
    noecho();
   /* nodelay(stdscr, TRUE);*/

 /*   hello_screen();*/

    my_map map(width, length);
    map.show_map();

    my_boy boy(start_pos_x,start_pos_y);

    scary_monster W (7, 67, width, length, map.forest);
    scary_monster I (18, 51, width, length, map.forest);

 

    while (true) {
      /*  timeout(100);*/
        switch (getch()) {
        case 'w':
            if (0 < boy.y) {
                boy.y--;
                W.give_waythim(boy.x, boy.y);
                I.give_waythim(boy.x, boy.y);

            }
            break;
        case 's':
            if (boy.y < length-1) {
                boy.y++;
                W.give_waythim(boy.x, boy.y);
                I.give_waythim(boy.x, boy.y);
            }
            break;
        case 'a':
            if (boy.x > 0) {
                boy.x--;
                W.give_waythim(boy.x, boy.y);
                I.give_waythim(boy.x, boy.y);
            }
            break;
        case 'd':
            if (boy.x < width-1) {
                boy.x++;
                W.give_waythim(boy.x, boy.y);
                I.give_waythim(boy.x, boy.y);
            }
            break;
        case 'q':
            break;
            
        }

        clear();

        map.show_map();
        boy.move_boy(map.forest);
        W.move_monster();
        I.move_monster();

    }
    
    getch();
    endwin();

}
