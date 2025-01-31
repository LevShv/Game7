#include "level_start.h"
//#include"level.h"

level_start::level_start(my_boy& boy) : Level(boy, 1) {}

void level_start::start() {

    Level::start();
    clear();
    map.show_map();
    boy.move_boy(map.forest);
    intface.draw(boy.hp, 0, boy.invent);
}

void level_start::update() {

    while (!exit_) {

        if (notification(gotooldman,
            "��� ���� ������ ��� �� ������� ������� ����.",
            "���� ����������� � ���� �������� - ������� <S>",
            1)) {
        }

        if (boy.x == 8 && boy.y == 19 && iwasoldman1 == true) {

            intface.subs(" <������> - ���������� ���� ��� ������, ��� ��������� ������� ����, ",
                "����� �������� ������� ���� (enter) - �����");
            timeout(-1);
            getch();
            intface.subs("<������> - ��� ����� ������� ��������� �����, ����������� ����� ����������",
                "�� ������, ��� ������ ������ �� ����, ����� 10 ������������ ����");
            iwasoldman1 = false;
            ireadom1 = true;
            spawn_mushroom = true;
        }

        if (notification(ireadom1,
            "<������> - ��� ����� ������� ��������� �����, ����������� ����� ����������",
            "�� ������, ��� ������ ������ �� ����, ����� 10 ������������ ����",
            2)) {}

        if (spawn_mushroom == true) {
            map.add_mushrooms(133, 10, 27, 87);
            spawn_mushroom = false;
        }

        if (boy.count_of_rm == 10 && notification(ifindall,
            "��� ����� �������, ����������� � ������",
            "",
            3, iwasoldman2)) {
        }

        if (boy.count_of_rm == 10 && iwasoldman2 == true && boy.x == 8 && boy.y == 19) {
            intface.subs("<������> - � ���������� �� ���� �������������� ������� ��� ��������.",
                "(enter) - �����");
            timeout(-1);
            getch();
            intface.subs("<������> - ..�������..",
                "(enter) - �����");
            getch();
            intface.subs("<������> - �� 5 �������������� ���������� 1 �������",
                "������� ��� �� �� �����������");
            getch();
            intface.subs("<������> - ..������ �������..",
                "");
            getch();

            invent_thing catcher({ "�������", 'o', 1, COLOR_PAIR(10), 1 });
            buy("������������", catcher, 5);

            intface.subs("<������> - ������, ������ ���� ���� ����� ������� ���������.",
                "���� ����� � ������� ��� �� �������� ����� ���� �� ���� (enter) - �����");
            getch();
            intface.subs("<������> - � ��� ���� ������� �������, ����� ������� ����.",
                "���� ��������� ��� ������ �� � ���� ��� ������ �� ���������� ����������");
            getch();
            intface.subs("<������> - ��� ����� 20 �����������. ��� ������ �������� ����� �� ����",
                "");
            getch();
            intface.subs("<������> - ���� �� ������� �� �������, ��������� �������",
                "������!");

            iwasoldman2 = false;
            iwasoldman2delay = true;


        }

        if (notification(iwasoldman2delay,
            "<������> - ���� �� ������� �� �������, ��������� �������",
            "������!",
            4,gotoforest)) {
        }

        if (boy.hp <= 0) dead();

        if (boy.x == 119 && boy.y > 10 && boy.y < 20 && gotoforest == true) {
            boy.loaded_boy = false;
            break;
        }

         
        moving();
        draw();
       
    }
}

void level_start::score_set() {

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

void level_start::draw()
{
    clear();

    map.show_map();
    boy.move_boy(map.forest);

    intface.draw(boy.hp, boy.count_of_m, boy.invent);
    score_set();
}

void level_start::moving()
{
    if (make_move(map.forest) == 1) { ////////.............
        game_iter++;
    }

    else {
        sci--;
    }

    save_check();
}

