#include "level_back_fforest.h"

level_back_fforest::level_back_fforest(my_boy& boy) : Level(boy, 1) {}

void level_back_fforest::start()
{
    boy.x = 119;

    my_map map(width, length, 1);
    map.show_map();
    boy.move_boy(map.forest);
    iface intface;
    intface.draw(10, 0, boy.invent);
}

void level_back_fforest::update()
{
    while (!exit_) {

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

            intface.subs("���, � ����� �� �����, ������� ��������� � ����� ������� �������.",
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

        score_set();
        draw();
    }
}

void level_back_fforest::score_set()
{
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
}

void level_back_fforest::draw()
{
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
