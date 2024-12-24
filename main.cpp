
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

int level = 0;


int width = 120;
int length = 28;

int start_pos_x = 59; // 59
int start_pos_y = 21; // 21

int subtimming = 10;

int game_iter = 1;

my_boy boy(start_pos_x, start_pos_y);
std::vector<monster_type*> monsters;


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

void monsters_data() {

    monster_type* W = new monster_type(
        "W", 
        'W', 
        COLOR_PAIR(10),
        COLOR_PAIR(27),
        { {-1, 0}, {1, 0}, {0, -1}, {0, 1},
          {-1,-1}, {-1,1}, {1, -1}, {1, 1}, },
        2, 
        1, 
        10, 
        5);

    monster_type* Y = new monster_type(
        "Y",
        'Y',
        COLOR_PAIR(25),
        COLOR_PAIR(26),
        { /*{-1, 0}, {1, 0}, {0, -1}, {0, 1},*/
          {-1,-1}, {-1,1}, {1, -1}, {1, 1}, },
        1,
        3,
        30,
        5);

    monsters.push_back(W);
    monsters.push_back(Y);

}

int make_move(char** map) {
     switch (getch()) {
        case 'w':
            if (0 < boy.y) {
                boy.y--;
                return 1;
            
            }
            break;
        case 's':
            if (boy.y < length - 1) {
                boy.y++;
                return 1;
            }
            break;
        case 'a':
            if (boy.x > 0) {
                boy.x--;
                return 1;
            
            }
            break;
        case 'd':
            if (boy.x < width - 1) {
                boy.x++;
                return 1;
            
          
            }
        break;

        case '1':
            if (boy.invent.size() > 0 && boy.invent[0].usage)
                boy.do_something(0, map);
            return 0;
            break;

            
        case 'e':
            iface inn;
            inn.show_invent(boy.invent);
            return 0;
        break;

       

     }
     return 0;
    
}

/*int make_move(monsters_family*& badboys) {
    switch (getch()) {
    case 'w':
        if (0 < boy.y) {
            boy.y--;

            return 1;
        }
        break;
    case 's':
        if (boy.y < length - 1) {
            boy.y++;

            return 1;
        }
        break;
    case 'a':
        if (boy.x > 0) {
            boy.x--;
            badboys->find(boy.x, boy.y);
            return 1;
        }
        break;
    case 'd':
        if (boy.x < width - 1) {
            boy.x++;
            badboys->find(boy.x, boy.y);
            return 1;
        break;
        }
    case 'e':
        iface inn;
        inn.show_invent();
        return 0;
        break;
*//*

    }
}*/

void level_start()

{
    

    my_map map(width, length,1);
    map.show_map();
    boy.move_boy(map.forest);
    iface intface;
    intface.draw(10, 0, boy.invent);

    

    bool gotooldman = true;

    bool iwasoldman1 = true;
    bool ireadom1 = false;
    bool spawn_mushroom = false;
    bool ifindall = true;
    bool iwasoldman2 = false;
    bool iwasoldman2delay = false;
    bool gotoforest = false;

    int nscore = 0;
    int sci = 0;

    while (true) {
        //mvprintw(17, 119, "2"); // 
        if (gotooldman == true){

            intface.subs("��� ���� ������ ��� �� ������� ������� ����.",
                         "���� ����������� � ���� �������� - ������� <S>");
            nscore = 1;
            sci++;
            if (sci >= subtimming)
                gotooldman = false;
        }

        if (boy.x == 8 && boy.y == 19 && iwasoldman1 == true) {
            
            intface.subs(" <������> - ���������� ���� ��� ������, ��� ��������� ������� ����, ", 
                         "����� �������� ������� ���� (enter) - �����");
            getch();
            intface.subs("<������> - ��� ����� ������� ��������� �����, ����������� ����� ����������", 
                         "�� ������, ��� ������ ������ �� ����, ����� 10 ������������ ����");
            iwasoldman1 = false;
            ireadom1 = true;
            spawn_mushroom = true;
        }

        if (ireadom1 == true) {
            intface.subs("<������> - ��� ����� ������� ��������� �����, ����������� ����� ����������",
                         "�� ������, ��� ������ ������ �� ����, ����� 10 ������������ ����");
            
            nscore = 2;
            sci++;
            if (sci >= subtimming * nscore)
                ireadom1 = false;
        }

        if (spawn_mushroom == true) {
            map.add_mushrooms(133, 10, 27, 87);
            spawn_mushroom = false;
        }

        if (boy.count_of_rm == 10 && ifindall == true) {
            intface.subs("��� ����� �������, ����������� � ������",
                "");
            nscore = 3;
            sci++;
            iwasoldman2 = true;
            if (sci >= subtimming * nscore)
                ifindall = false;

        }
        if (boy.count_of_rm == 10 && iwasoldman2 == true && boy.x == 8 && boy.y == 19) {
            intface.subs("<������> - ������, ������ ���� ���� ����� ������� ���������.",
                "���� ����� � ������� ��� �� �������� ����� ���� �� ���� (enter) - �����" );
            getch();
            intface.subs("<������> - � ��� ���� ������� �������, ����� ������� ����.",
                "���� ��������� ��� ������ �� � ���� ��� ������ �� ���������� ����������");
            getch();
            intface.subs("<������> - ��� ����� 20 �����������. ��� ������ �������� ����� �� ����",
                "");
            iwasoldman2 = false;
            iwasoldman2delay = true;
            

        }
        if (iwasoldman2delay == true) {
            intface.subs("<������> - ��� ����� 20 �����������. ��� ������ �������� ����� �� ����",
                "");

            nscore = 4;
            sci++;
            gotoforest = true;
            if (sci >= subtimming * nscore)
                iwasoldman2delay = false;
        }
        if (boy.x == 119 && boy.y > 10 && boy.y < 20 && gotoforest == true) //  17, 119
            break;
        
      

        if (make_move(map.forest) == 1) { ////////.............
            game_iter++;

        }
        else {
;           sci--;
        }
        
        clear();

        map.show_map();
        boy.move_boy(map.forest);

        intface.draw(boy.hp, boy.count_of_m, boy.invent);

        switch (nscore)
        {
        case 0:

            break;

        case 1:
            intface.score("����������� �� �������");
            break;

        case 2:
            intface.score("������� 10 ������������ ����");
            break;

        case 3:
            intface.score("��������� � ������");
            break;

        case 4:
            intface.score("������������� � ������� ���");
            break;

        }


    }
}

void level_forest() {

    clear();

    int nscore = 1;
    int sci = 0;
    bool igotall = true;
    bool gotoborder = false;

    boy.x = 1;
    my_map map(width, length, 2);
    map.show_map();

    iface intface;
    intface.draw(10, 0, boy.invent);

    monsters_family* badboys = new monsters_family(map.forest, monsters[0]);


    
    while (true) {

        if (boy.hp == 0) {
            intface.game_over();
            getch();
            break;
        }
        if (boy.count_of_m == 20 && igotall == true) {
            intface.subs("��� ����� �������, ����������� � ������",
                "");
            nscore = 2;
            sci++;
            gotoborder = true;
            if (sci >= subtimming * nscore)
                igotall = false;

        }
        if (gotoborder == true && boy.x == 0 && boy.y > 10 && boy.y < 20) 
            break;

        if (game_iter % 100 == 0) {
            badboys->give_some_boys_rand(monsters[0]);
          /*  badboys->give_some_boys_rand(monsters[1]);*/
        }
           

        switch (nscore)
        {
        case 1:
            intface.score("�������� 20 �����������");
            break;

        case 2:
            intface.score("������������ �� ����");
            break;

        default:
            break;
        }

        bool move = make_move(map.forest);
        if (move) { ////////.............
            game_iter++;
            badboys->find(boy.x, boy.y);
        }
        else {
            sci--;

        }

        clear();

        map.show_map();
        boy.move_boy(map.forest);

        if(move)
            boy.hp -= badboys->monsters_move(0);
        else
            badboys->monsters_move(1);

         

        intface.draw(boy.hp, boy.count_of_m, boy.invent);

    }

    getch();
    delete badboys;
 }

void level_back_ff() {

    boy.x = 119;

    my_map map(width, length, 1);
    map.show_map();
    boy.move_boy(map.forest);
    iface intface;
    intface.draw(10, 0, boy.invent);



   
    bool gotooldman = true;
    bool iwasoldman1 = true;
    bool ireadom1 = true;
    bool gotoborder = false;

    int nscore = 0;
    int sci = 0;

    while (true) {
        //mvprintw(17, 119, "2"); // 
        if (gotooldman == true) {
            nscore = 1;
        }
        if (boy.x == 8 && boy.y == 19 && iwasoldman1 == true) {

            intface.subs(" <������> - �� ������� ������ ���, �� ��������� ������� ��������� ",
                "�� ��� ���� ������ �������...");
            getch();

            intface.subs(" <������> - � ���������� ����� c ������� �������� �� ������� ��������� ",
                "������� � ������� ���. ����� �������� ����� ����������.");
            getch();

            intface.subs("������ ���� ����� ����������� � ����������� �������, ",
                "������� ��������� �� ������� ����.");
            getch();

            intface.subs("���, � ����� �� �����, ������� ��������� � ����� ������� �������." ,
                " ����� ���, ������� �����-�� ����������� �������� ��������.");
            getch();

            intface.subs("������ �� ������ ����� �� ����, ������� ����� �� ������",
                "�� ���� ����� ����������� ��������� ������� �������� ����� ����� ���������");
            getch();

            boy.add_to_invent("�������", 'o', 5, COLOR_PAIR(10), 1);

            iwasoldman1 = false;
            gotooldman = false;

        }
        if (iwasoldman1 == false && ireadom1 == true) {
            intface.subs("������ �� ������ ����� �� ����, ������� ����� �� ������",
                "�� ���� ����� ����������� ��������� ������� �������� ����� ����� ���������");
            nscore = 2;
            sci++;
            gotoborder = true;
            if (sci >= subtimming * nscore)
                ireadom1 = false;

        }
        if (boy.x > 30 && boy.x < 38 && boy.y == 0 && gotoborder == true) {
            break;
        }
        switch (nscore)
        {
        case 1:
            intface.score("������������ �� ����");
            break;

        case 2:
            intface.score("������������� � �������");
            break;

        default:
            break;
        }


        if (make_move(map.forest) == 1) { ////////.............
            game_iter++;
        }
        else {
             sci--;
        }

        clear();

        map.show_map();
        boy.move_boy(map.forest);

        intface.draw(boy.hp, boy.count_of_m, boy.invent);
        game_iter++;

    }
}

void level_way_to_village() {

    boy.y = 27;

    int n = 4;
    my_map map(width, length, 3);
    map.show_map();
    boy.move_boy(map.forest);
    iface intface;
    intface.draw(boy.hp, 0, boy.invent);

    monsters_family* badboys = new monsters_family(map.forest, monsters[0]);
    badboys->give_some_boys_rand(monsters[1]);


    bool gotovil = true;
    bool iwasoldman1 = true;
    bool ireadom1 = true;
    bool gotoborder = false;

    int nscore = 0;
    int sci = 0;

    for (int i = 0; i < n; i++) {

        badboys->give_some_boys_rand(monsters[0], 20, 29, 0, 100);
        badboys->give_some_boys_rand(monsters[0], 20, 29, 0, 100);
        badboys->give_some_boys_rand(monsters[1], 20, 29, 0, 100);
    }

    badboys->monsters_move(1);


    while (true) {
        //mvprintw(17, 119, "2"); // 
        if (gotovil == true) {
            nscore = 1;
        }

        
        
        /*if (boy.x > 30 && boy.x < 38 && boy.y == 0 && gotoborder == true) {
            break;
        }*/
        switch (nscore)
        {


        case 1:
            intface.score("������������� � �������");
            break;

        case 2:
            intface.score("������������� � �������");
            break;

        default:
            break;
        }


        bool move = make_move(map.forest);
        if (move) { ////////.............
            game_iter++;
            badboys->find(boy.x, boy.y);
        }
        else {
            sci--;

        }

        clear();

        map.show_map();
        boy.move_boy(map.forest);

        if (move)
            boy.hp -= badboys->monsters_move(0);
        else
            badboys->monsters_move(1);

        intface.draw(boy.hp, boy.count_of_m, boy.invent);
        game_iter++;

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
    monsters_data();

    iface init;
    
    if (init.start_game()) {
        while (true) { // �������� ���

            level_start();
            level_forest();

            if (boy.hp == 0) {
                boy.boy_reset(start_pos_x, start_pos_y);
                continue;
            }

            level_back_ff();
            boy.boy_reset(start_pos_x, start_pos_y);

        }
    }
    else {
        clear();
        while (true) { // ����������� �����

            mvprintw(7, 15, "Choose level");
            int lv = getch();
            clear();

            switch (lv)
            {
            case 48:
                level_start();

            case 49:
                if (lv == 49) {
                    boy.count_of_rm = 10;
                }
                level_forest();

            case 50:
                if (lv == 50) {
                    boy.count_of_m = 20;
                    boy.count_of_rm = 10;
                    boy.hp = 8;
                    boy.add_to_invent("���������", '.', 20, COLOR_PAIR(8),0);
                    boy.add_to_invent("������������", (char)133, 10, COLOR_PAIR(22), 0);
                    boy.add_to_invent("�������", '^', 20, COLOR_PAIR(8), 0);
                    boy.add_to_invent("�����������", '"', 10, COLOR_PAIR(22), 0);
                    boy.add_to_invent("������������", (char)133, 10, COLOR_PAIR(22), 0);

                }
                level_back_ff();

            case 51:
                if (lv == 51) {
                    boy.count_of_m = 20;
                    boy.count_of_rm = 10;
                    boy.hp = 8;
                    boy.add_to_invent("���������", '.', 20, COLOR_PAIR(8), 0);
                    boy.add_to_invent("������������", (char)133, 10, COLOR_PAIR(22), 0);
                    boy.add_to_invent("�������", 'o', 5, COLOR_PAIR(10), 1);

                }
                level_way_to_village();
            }
            clear();
            boy.boy_reset(start_pos_x, start_pos_y);
        }
        
    }
       


    endwin();
    
   

    for (monster_type* monster : monsters) {
        delete monster;
    }

 }
