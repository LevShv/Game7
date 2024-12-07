
#include <curses.h>
#include <my_map.h>
#include <my_boy.h>
#include <monster.h>
#include <scary_monster.h>

//class mushroom {
//
//    int x;
//    int y;
//};

class iface{
public:
    iface() {
        
        draw(10,0);
    }
    void draw(int boy_hp, int count_ofm ) {
        
        Bckg();
        draw_hp_boy(boy_hp);
        draw_Count_of_mushrooms(count_ofm);
    }
    void game_over() {

        int xpos = 29;
        int ypos = 50;

        int start_row = 10;
        int end_row = 15;
        int start_col = 40;
        int end_col = 80;

        for (int row = start_row; row <= end_row; row++) {
            for (int col = start_col; col <= end_col; col++) {
                mvaddch(row, col, ' ');
            }
        }
        mvprintw(13, 55, "Game Over");

    }
private:

    int xposofhp = 29;
    int yposofhp = 50;

    void draw_hp_boy(int hp) {

        attron(COLOR_PAIR(3));
        mvprintw(29, 46, "Boy");
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(1));
        int i = 0;
        for (i; i < 2*hp; i++) {
            mvaddch(xposofhp, yposofhp + i, ' ');
            
        }
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(6));
        for (i; i < 20; i++) {
            mvaddch(xposofhp, yposofhp + i, 'p');

        }

        attroff(COLOR_PAIR(6));

    }
    void draw_Count_of_mushrooms(int count_ofm){

        attron(COLOR_PAIR(3));

        mvprintw(29, 20, "Gribi");
        char str[3];
        sprintf_s(str, "%d", count_ofm);
        mvprintw(29, 26, str);

        attroff(COLOR_PAIR(3));
    }
    void Bckg() {
        attron(COLOR_PAIR(2));

        int start_row = 28;
        int end_row = 31;
        int start_col = 0;
        int end_col = 120;

        for (int row = start_row; row <= end_row; row++) {
            for (int col = start_col; col <= end_col; col++) {
                mvaddch(row, col, ' ');
            }
        }

        attroff(COLOR_PAIR(2));
    }
};
void colors_pairs() {

    init_color(8, 900, 100, 100); // серый нижний bar
    init_color(257, 46, 139, 87); //  темно-зеленый цвет фона



    init_pair(1, COLOR_RED, COLOR_RED); // полоска здоровья
    init_pair(2, COLOR_BLACK, 8); // цвет "Boy"
    init_pair(3, COLOR_BLACK, 8); // цвет "Грибы"

    init_pair(4, 7, 257); // темно-зеленый цвет фона
    init_pair(5, COLOR_RED, 257); // пара для фона

    init_pair(6, COLOR_BLACK, COLOR_BLACK); // черный для опустевшего здоровья
    init_pair(7, COLOR_BLUE, 257); // "0"
    init_pair(8, COLOR_YELLOW, 257);// грибы

    init_pair(10, COLOR_RED, 257);
    
    
}
int main()
{ 

    int width = 120;
    int length = 28;
    int frame_rate = 100;

    int start_pos_x = 2;
    int start_pos_y = 2;

    initscr();
    curs_set(0);
    noecho();
    start_color();
    colors_pairs();

    my_map map(width, length);
    map.show_map();

    iface intface;
    
    my_boy boy(start_pos_x,start_pos_y);

    /*std::vector<scary_monster>* Monsters = new std::vector<scary_monster>();

   
    Monsters->push_back(W);
    Monsters->push_back(I);*/

    scary_monster W(7, 67, width, length, map.forest);
    scary_monster I(18, 51, width, length, map.forest);


 
   


    while (true) {
        if (boy.hp == 0) {
            intface.game_over();
            getch();
            return 0;
        }
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
        if (W.move_monster() == 1)
            boy.hp--;
        if (I.move_monster() == 1)
            boy.hp--;
        intface.draw(boy.hp,boy.count_of_m);

    }
    
    getch();
    endwin();

}
