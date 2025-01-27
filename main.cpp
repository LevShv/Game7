
#include <curses.h>
#include <iface.h>
#include <level_manager.h>

 void colors_pairs() {

    init_color(300, 165,165,165); // ����� ������ bar
    init_color(257, 46, 139, 87); //  �����-������� ���� ����
    init_color(258, 0, 0, 128); // �����-�����
    init_color(259, 189, 183, 107); // �������
    init_color(260, 240, 230, 140); // ������-�������
    init_color(301, 213, 213, 213); // �����-����� ��� ����

    init_pair(0, COLOR_WHITE, COLOR_BLACK); // default
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

    init_pair(29, 257, 257); //��� �������� ����
    init_pair(30, 8, 8); //��� ������ �������� ����

    init_pair(31, COLOR_BLACK,COLOR_WHITE); //���� ��������� ������

    init_pair(32, COLOR_MAGENTA, 257); // ���� ��� �������

    init_pair(33, COLOR_WHITE, 301); // ���� ������ � ���� �����
    init_pair(34, COLOR_WHITE, COLOR_BLACK);

    init_pair(35, 301, 301); // ������ ��������� 
 

}

 void call_manager(level_manager& Manager) {

     while (!Manager.all_levels_done()) {

         Manager.start_next_level();
     }
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
    
    int button_save = 0;
    int selection = 0;


    //init.pause_menu();
    //init.save_screen();
  /*  init.load_screen();*/

    level_manager Manager;

    while (true) {

        

        if (Manager.download) {

            Manager.download = false;
            call_manager(Manager);
        }
        else {

  

            switch (init.main_menu(button_save)) {

            case 0:

                init.start_game();
                call_manager(Manager);

                break;

            case 1:

                clear();

                button_save = 1;
                selection = init.level_selection();

                clear();

                if (selection == 27)
                    break;

                else {

                    Manager.currentLevelIndex = selection;
                    Manager.preset();
                    call_manager(Manager);

                    break;
                }

            case 2:
                //init.load()
                break;
            case 3:
                endwin();
                exit(0);
                break;
            }
        }    
    }
    endwin();

 }

