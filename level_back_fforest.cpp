#include "level_back_fforest.h"

level_back_fforest::level_back_fforest(my_boy& boy) : Level(boy, 1) 
{

    start_pos_x = 119;
    start_pos_y = 10;
    
}

void level_back_fforest::start()
{
    Level::start();

    if (!boy.loaded_boy) {
        boy.x = 119;
    }

    clear();
    map.show_map();
    boy.move_boy(map.forest);;
    intface.draw(boy.hp, 0, boy.invent);
}

void level_back_fforest::update()
{
    while (!exit_) {

        if (gotooldman == true) {
            nscore = 1;
        }

        if (boy.x == 8 && boy.y == 19 && iwasoldman1 == true) {

            intface.subs(" <������> - �� ������� ������ ���, �� ��������� ������� ���������",
                "�� ������������� � ���������� ���� �������� ����� ");
            timeout(-1);
            getch();

            intface.subs(" <������> - �� ���� �������� ����� ����� 10 ������������� ",
                " �������� �������� ��� ��������� �����, ��� ��� ����������� ");
            getch();

            intface.subs("<������> - ���� � ���� ��� ���� ������������ � ������ ��� �������",
                "");
            getch();

            intface.subs(" <������> - ..�������.. ",
                "..������ �������� �����.. ");
            getch();

            invent_thing catcher({ "�������", 'o', 1, COLOR_PAIR(10), 1 });
            invent_thing healer({ "���������",'&', 1, COLOR_PAIR(47), 1 });

            buy("������������", catcher, 5);
            buy("���������", healer, 10);

            intface.subs("������ ���� ����� ����������� � ����������� �������, ",
                "������� ��������� �� ������� ����.");
            getch();

            intface.subs("���, � ����� �� �����, ������� ��������� � ����� ������� �������.",
                " ����� ���, ������� �����-�� ����������� �������� ��������.");
            getch();

            intface.subs("������ �� ������ ����� �� ����, ������� ����� �� ������",
                "");
            getch();

            iwasoldman1 = false;
            gotooldman = false;

        }

        if (iwasoldman1 == false && notification(ireadom1,
            "������ �� ������ ����� �� ����, ������� ����� �� ������",
            "�� ���� ����� ����������� ��������� ������� �������� ����� ����� ���������",
            2, gotoborder)) {
        }

        if (boy.hp <= 0) {
            dead();
            clear();
            continue;
        }

        if (boy.x > 30 && boy.x < 38 && boy.y == 0 && gotoborder == true) {
            boy.loaded_boy = false;
            break;
        }

        moving();
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
    

    clear();

    map.show_map();
    boy.move_boy(map.forest);

    intface.draw(boy.hp, boy.count_of_m, boy.invent);
   
    game_iter++;
    score_set();
}

void level_back_fforest::moving()
{
    if (make_move(map.forest) == 1) { ////////.............
        game_iter++;
    }
    else {
        sci--;
    }
    save_check();

}
