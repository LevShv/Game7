#include "curses.h"
#include "iface.h"

iface::iface() {

    draw(10, 0);
}
iface::iface(bool start) {

    
}
    void iface::draw(int boy_hp, int count_ofm) {

        Bckg(28,31,0,120,COLOR_PAIR(2));
        draw_hp_boy(boy_hp);
       /* draw_Count_of_mushrooms(count_ofm);*/
    }

    void iface::game_over() {
        
        Bckg(10,15,40,80,COLOR_PAIR(21));

        mvprintw(13, 55, "������");

    }

    void iface::game_win() {

        Bckg(10,15,40,80,COLOR_PAIR(21));
       
        mvprintw(13, 55, "Win");

    }

    void iface::subs(const char* a, const char* b)
    {
        Bckg(3,6,20,100,COLOR_PAIR(21));

        mvprintw(4, 23, a);
        mvprintw(5, 23, b);
    }

    void iface::score(const char* a)
    {
        attron(COLOR_PAIR(3));

        mvprintw(29, 85, "����: ");
        mvprintw(29, 91, a);

        attroff(COLOR_PAIR(3));
    }

    void iface::show_invent()
    {
        Bckg(10, 15, 40, 80, COLOR_PAIR(21));
        getch();
    }

    int iface::start_game()
    {
        mvprintw(13, 55, "GAME7.EXE");
        getch();
        clear();

        mvprintw(5, 15, "�����-�� ��� ��� �� ������ ������ � �� ��� ������� �����, ������ ������,");
        mvprintw(6, 15, "������ ��������� ���� � ������ ������ �����. ����� ������ ��������,");
        mvprintw(7, 15, "��� ������ ������ ��� � �������� � ��������.������, ������ �����, ��� ������� ���� ���������.");
        getch();

        mvprintw(11, 15, "������� ���, ������ ��������� ����� �����, ������� ����������, ������� ����� ���� ���� ������� � ������.");
        mvprintw(12, 15, "��������� ���� ������������ � ������� � ������� ����������, ��� ������� ������� ������� � �����.");
        mvprintw(13, 15, "������ ������ ����� ������ ��������� ������� � �����.");
        getch();

        mvprintw(17, 15, "�� ����� ����� ����� ���� �������");
        mvprintw(18, 15, "������� ��� ������ � ��� ������� ������ ������� ���������� ������ ��� �� ��������� ");
        mvprintw(19, 15, "�����, ������ �������� �����������! ���� ���� �������,");
        mvprintw(20, 15, "�� ������ �� ������� ������� ���� � ���� �����-�� ���������� ���!");

        if (getch() == 27)
            return 0;

        clear();
        return 1;
    }

    void iface::draw_hp_boy(int hp) {

        attron(COLOR_PAIR(3));
        mvprintw(29, 46, "Boy");
        attroff(COLOR_PAIR(3));

        attron(COLOR_PAIR(1));
        int i = 0;
        for (i; i < 2 * hp; i++) {
            mvaddch(xposofhp, yposofhp + i, ' ');

        }
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(6));
        for (i; i < 20; i++) {
            mvaddch(xposofhp, yposofhp + i, 'p');

        }

        attroff(COLOR_PAIR(6));

    }

    void iface::draw_Count_of_mushrooms(int count_ofm) {

        attron(COLOR_PAIR(3));

        mvprintw(29, 20, "Gribi");
        char str[3];
        sprintf_s(str, "%d", count_ofm);
        mvprintw(29, 26, str);

        attroff(COLOR_PAIR(3));
    }

    void iface::Bckg(int start_row, int end_row, int start_col, int end_col, int color_pair) {
        attron(color_pair);

        for (int row = start_row; row <= end_row; row++) {
            for (int col = start_col; col <= end_col; col++) {
                mvprintw(row, col, " ");
            }
        }

        attroff(color_pair);
    }
