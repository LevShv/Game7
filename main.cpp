
#include <curses.h>
#include <my_map.h>
#include <my_boy.h>
#include <monster.h>
#include <scary_monster.h>
#include <monsters_family.h>
#include "iface.h"
#include <locale.h>
#include <monster_type.h>
#include <vector>
#include <level_manager.h>

 void colors_pairs() {

    init_color(300, 165,165,165); // ����� ������ bar
    init_color(257, 46, 139, 87); //  �����-������� ���� ����
    init_color(258, 0, 0, 128); // �����-�����
    init_color(259, 189, 183, 107); // �������
    init_color(260, 240, 230, 140); // ������-�������


    init_pair(1, COLOR_RED, COLOR_RED); // ������� ��������
    init_pair(2, COLOR_BLACK, 8); // ���� "Boy"
    init_pair(3, COLOR_BLACK, 8); // ���� "�����"

    init_pair(4, 7, 257); // �����-������� ���� ����
    init_pair(5, COLOR_RED, 257); // ���� ��� ����

    init_pair(6, COLOR_BLACK, COLOR_BLACK); // ������ ��� ����������� ��������
    init_pair(7, COLOR_BLUE, 257); // "0"
    init_pair(8, COLOR_YELLOW, 257);// �����

    init_pair(10, COLOR_RED, 257); // W

    init_pair(11, COLOR_BLUE, COLOR_BLUE); // ����
    init_pair(12, COLOR_BLUE, 258); // ���� ���� 
    
    init_pair(13, 258, 258); // ����...
    init_pair(14, 259, 259); // ����
    init_pair(15, 260, 260); // �������
    
    init_pair(16, COLOR_BLUE, 259); // ������� � ����������

    init_pair(17, COLOR_WHITE, COLOR_WHITE); // �������
    init_pair(18, COLOR_BLUE, COLOR_WHITE); // �������� �� �������

    init_pair(19, 8, 259); // ����� ������ ����

    init_pair(20, 300, COLOR_BLACK); // ����� ������ ����
    init_pair(21, COLOR_WHITE, COLOR_BLACK); // Subs
    init_pair(22, COLOR_RED, 257); // ������� ����

    init_pair(23, 258, 8);//������� ���������

    init_pair(24, COLOR_RED, COLOR_BLACK);//������������ ��� ���������

    init_pair(25, COLOR_MAGENTA, 257); // Y
    init_pair(26, COLOR_MAGENTA, 259); // Y1
    init_pair(27, COLOR_RED, 259); // W1

    init_pair(28, COLOR_BLUE, 257); // �����������

}

 int main()
 {
    std::system("chcp 1251");

    initscr();
    curs_set(0);
    noecho();
    start_color();
    colors_pairs();

    iface init;
    
    if (init.start_game()) {

        level_manager Manager;

        while (!Manager.all_levels_done()) {

            Manager.start_next_level();
        }
    }

    else {

        clear();

        level_manager Manager;
        bool chose = true;
        while (chose) { // ����������� �����

            mvprintw(7, 15, "Choose level");
            int lv = getch();
            clear();

            switch (lv)
            {
            case 48:
                Manager.select_level(0);
                chose = false;
                break;

            case 49:
                Manager.select_level(1);
                chose = false;
                break;

            case 50:
                Manager.select_level(2);
                chose = false;
                break;

            case 51:
                Manager.select_level(3);
                chose = false;
                break;

                    //boy.hp = 8;
                    //boy.add_to_invent("���������", '.', 20, COLOR_PAIR(8), 0);
                    //boy.add_to_invent("������������", (char)133, 10, COLOR_PAIR(22), 0);
                    //boy.add_to_invent("�������", 'o', 5, COLOR_PAIR(10), 1);*/


                // level_way_to_village();
            }
            clear();
          //  boy.boy_reset(start_pos_x, start_pos_y);
            
        }
        while (!Manager.all_levels_done()) {

            Manager.start_next_level();
        }
        
    }
       
    endwin();

 }
