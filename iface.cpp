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

        mvprintw(13, 55, "СмЭрть");

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

        mvprintw(29, 85, "Цель: ");
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

        mvprintw(5, 15, "Когда-то Лес был не просто местом — он был сердцем жизни, полным зелени,");
        mvprintw(6, 15, "звуков щебетания птиц и лёгкого шёпота ветра. Здесь царила гармония,");
        mvprintw(7, 15, "где каждый житель жил в согласии с природой.Однако, спустя время, его идиллия была разрушена.");
        getch();

        mvprintw(11, 15, "Древний маг, будучи одержимым тёмной силой, наложил заклинание, оставив после себя лишь пустоту и смерть.");
        mvprintw(12, 15, "Спокойные поля превратились в мрачные и опасные территории, где обитают ужасные монстры и порча.");
        mvprintw(13, 15, "Бывшие оазисы жизни сейчас наполнены страхом и тьмой.");
        getch();

        mvprintw(17, 15, "Но среди этого хаоса есть надежда");
        mvprintw(18, 15, "Молодой маг Нолиус и его учитель Старец Соломун собираются спасти лес от проклятья ");
        mvprintw(19, 15, "Вперёд, смелый искатель приключений! Твой путь тернист,");
        mvprintw(20, 15, "но только ты сможешь вернуть свет в этот когда-то прекрасный дом!");

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
