
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
        mvprintw(x, y, "0");
    }

private:
};

int main()
{ 
    // ����������� ����� ��� ����������� ���������
    system("chcp 1251");
    // �������������� ����� curses
    initscr();
    // ������ ������
    //curs_set(0);
    //// ��������� ������� �����
    //start_color();
    //// ������ ������ 1,2,3,4,5
    //init_pair(1, COLOR_WHITE, COLOR_BLUE);
    //init_pair(2, COLOR_MAGENTA, COLOR_BLUE);
    //init_pair(3, COLOR_GREEN, COLOR_BLUE);
    //init_pair(4, COLOR_RED, COLOR_BLUE);
    //init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    ////���� ����, ����� 1
    //bkgd(COLOR_PAIR(1));
    
    my_map map;
    map.show_map();
   
    getch();
    endwin();

   /* vec start_pos{ 10,10 };
    vec step{ 1,0 };

    int framerate = 100;*/
}
