#include "curses.h"
#include "iface.h"

iface::iface() {

    draw(10, 0);
}
    void iface::draw(int boy_hp, int count_ofm) {

        Bckg();
        draw_hp_boy(boy_hp);
        draw_Count_of_mushrooms(count_ofm);
    }
    void iface::game_over() {

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
    void iface::game_win() {

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
        mvprintw(13, 55, "Win");

    }
    void iface::subs(const char* a, const char* b)
    {
        attron(COLOR_PAIR(21));

        int start_row = 3;
        int end_row = 6;
        int start_col = 20;
        int end_col = 100;

        for (int row = start_row; row <= end_row; row++) {
            for (int col = start_col; col <= end_col; col++) {
                mvaddch(row, col, ' ');
            }
        }
        mvprintw(4, 23, a);
        mvprintw(5, 23, b);
    }
    void iface::score(const char* a)
    {
        attron(COLOR_PAIR(3));
        mvprintw(29, 85, "Цель: ");
        mvprintw(29, 91, a);

        attroff(COLOR_PAIR(3));
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
    void iface::Bckg() {
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
