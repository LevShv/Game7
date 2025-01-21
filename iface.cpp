#include "curses.h"
#include "iface.h"
//#include "ivent_thing.h"
#include "my_boy.h"

iface::iface() {

    
}

void iface::draw(int boy_hp, int count_ofm, std::vector<invent_thing> &invent)
{
    Bckg(28, 31, 0, 120, COLOR_PAIR(2));
    draw_hp_boy(boy_hp);
    draw_slots(invent);
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
    cmvprintw(29, 85, "����: ", COLOR_PAIR(3));
    cmvprintw(29, 91, a, COLOR_PAIR(3));
}

void iface::show_invent(std::vector<invent_thing> &invent)
{
    int start_row = 10;
    int start_col = 42;
    int end_row = 18;
    int end_col = 80;

    bool exit = false;

    while (!exit) {

        Bckg(start_row, end_row, start_col - 2, end_col, COLOR_PAIR(2));
        cmvprintw(start_row + 1, (end_col + start_col) / 2 - 5, "���������", COLOR_PAIR(3));

        int j = 0;
        int k = 0;

        for (int i = 0; i < invent.size(); i++)
        {

            attron(invent[i].color);
            move(start_row + (j + 3), start_col + (k + 1));
            printw("%c",invent[i].icon);

            attroff(invent[i].color);

            attron(COLOR_PAIR(3));
            move(start_row + (j + 3), start_col + (k + 3));
            printw("%d", invent[i].count);
            attroff(COLOR_PAIR(3));
                

            if (posofptr == i) {

                cmvprintw(start_row + (j + 3), start_col + (k - 2), "->", COLOR_PAIR(23));
                    
            }

            if ((i + 1) % 3 == 0 && i != 0) {
                j = 0;
                k += 8;
            }

            else {
                j += 2;
            } 

                
        }
        refresh();

        switch (getch()) {
        case 'w':
            if (posofptr - 1 >= 0)
                posofptr -= 1;
            break;

        case 's':
            if (posofptr + 1 < invent.size())
                posofptr += 1;
            break;

        case 'a':
            if (posofptr - 3 >= 0)
                posofptr -= 3;
            break;

        case 'd':
            if (posofptr + 3 < invent.size())
                posofptr += 3;
            break;

        case '1':

            std::swap(invent[posofptr], invent[0]);
            clean_left_corner();
            draw_slots(invent);
                break;

        case '2':

            std::swap(invent[posofptr], invent[1]);
            clean_left_corner();
            draw_slots(invent);
                break;

        case 'e':
                exit = true;
                break;
        }
           

    }
      
}

void iface::draw_slots(std::vector<invent_thing>& invent)
{
    if (invent.size() > 0) {
        cmvprintw(28, 15, ("[" + std::string(1, invent[0].icon) + "] " + invent[0].name += " <" + std::to_string(invent[0].count) + ">").c_str(), COLOR_PAIR(3));

    }
    if (invent.size() > 1 && invent[1].name != "") {
        cmvprintw(29, 15, ("[" + std::string(1, invent[1].icon) + "] " + invent[1].name += " <" + std::to_string(invent[1].count) + ">").c_str(), COLOR_PAIR(3));

    }
}

int iface::start_game()
{
    clear();
    Bckg(0, 29, 0, 120, COLOR_PAIR(29));
    attron(COLOR_PAIR(4));

    mvprintw(5, 13, "�����-�� ��� ��� �� ������ ������ � �� ��� ������� �����, ������ ������,");
    mvprintw(6, 13, "������ ��������� ���� � ������ ������ �����. ����� ������ ��������,");
    mvprintw(7, 13, "��� ������ ������ ��� � �������� � ��������.������, ������ �����, ��� ������� ���� ���������.");
    getch();

    mvprintw(11, 13, "������� ���, ������ ��������� ����� �����, ������� ����������, ������� ����� ���� ���� ������� � ������.");
    mvprintw(12, 13, "��������� ���� ������������ � ������� � ������� ����������, ��� ������� ������� ������� � �����.");
    mvprintw(13, 13, "������ ������ ����� ������ ��������� ������� � �����.");
    getch();

    mvprintw(17, 13, "�� ����� ����� ����� ���� �������");
    mvprintw(18, 13, "������� ��� ������ � ��� ������� ������ ������� ���������� ������ ��� �� ��������� ");
    mvprintw(19, 13, "�����, ������ �������� �����������! ���� ���� �������,");
    mvprintw(20, 13, "�� ������ �� ������� ������� ���� � ���� �����-�� ���������� ���!");

    attron(COLOR_PAIR(4));

    if (getch() == 27)
        return 0;

    clear();
    return 1;
}

int iface::level_selection()
{
    Bckg(0, 29, 0, 120, COLOR_PAIR(29));

    cmvprintw(5, 51, "������� ����� ������", COLOR_PAIR(4));

    return getch();
}

int iface::main_menu() {


    bool selected = false;
    int button = 0;

    while (!selected) {
        int button_wide = 31;

        Bckg(0, 29, 0, 120, COLOR_PAIR(29));
        Bckg_effect();
        cmvprintw(5, 55, "GAME7.EXE", COLOR_PAIR(4));

            
        Bckg(8, 10, 44, 75, (button == 0) ? COLOR_PAIR(31) : COLOR_PAIR(30));
        cmvprintw(9, 55, "����� ����", (button == 0) ? COLOR_PAIR(31) : COLOR_PAIR(3)); // 1

        Bckg(13, 15, 44, 75, (button == 1) ? COLOR_PAIR(31) : COLOR_PAIR(30));
        cmvprintw(14, 52, "����������� �����", (button == 1) ? COLOR_PAIR(31) : COLOR_PAIR(3)); // 2

        Bckg(18, 20, 44, 75, (button == 2) ? COLOR_PAIR(31) : COLOR_PAIR(30));
        cmvprintw(19, 55, "���������", (button == 2) ? COLOR_PAIR(31) : COLOR_PAIR(3)); // 3

        refresh();


        switch (getch()) {

        case 'w': 
            button = (button - 1 + 3) % 3; 
            break;

        case 's': 
            button = (button + 1) % 3; 
            break;

        case 10: 
            selected = true;
            break;

        default:
            break;
        }
    }
     
    switch (button) {

    case 0:
        start_game();
        return 0;

    case 1:
        return 1;

    case 2:
        return 2;

    }
    return 0;
}

void iface::draw_hp_boy(int hp) {

    cmvprintw(29, 46, "Boy", COLOR_PAIR(3));

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

void iface::clean_left_corner()
{
    Bckg(28, 31, 0, 50, COLOR_PAIR(2));
}

void iface::cmvprintw(int y, int x, const char* text, int color_pair)
{
    attron(color_pair);
    mvprintw(y, x, text);
    attroff(color_pair);

}

void iface::Bckg_effect()
{
    int count_of_stars = 45;
    attron(COLOR_PAIR(32));

    for (int i = 0; i < count_of_stars; i++) {

        
        mvaddch(random_y(), random_x(), '*');

    }
    attroff(COLOR_PAIR(32));

}
int iface::random_x()
{

    std::random_device rd;  // ������������ ��� ��������� ���������� �������� (seed)
    std::mt19937 gen(rd()); // ��������� ��������� ����� (Mersenne Twister)

    std::uniform_int_distribution<> disx(1, 120 - 1); // ����������� ������������� �� 0 �� 

    return disx(gen);
}

int iface::random_y()
{

    std::random_device rd;  // ������������ ��� ��������� ���������� �������� (seed)
    std::mt19937 gen(rd()); // ��������� ��������� ����� (Mersenne Twister)

    std::uniform_int_distribution<> disy(1, 29 - 1);

    return disy(gen);
}

/*void iface::button(int start_row, int end_row, int start_col, int end_col, int color_pair_bckg, int y, int x, const char* text, int color_pair_text)
{
    Bckg(start_row, end_row, start_col, end_col, color_pair_bckg);
    cmvprintw(19, 55, "���������", COLOR_PAIR(3));

}*/


