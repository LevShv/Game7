#include "level_village.h"
#include "random"

level_village::level_village(my_boy& boy) : Level(boy, 4)
{
	start_pos_x = 65;
	start_pos_y = 27;
}

level_village::~level_village()
{
	delete badboys;
}

void level_village::start()
{
    Level::start();

    clear();
    boy.y = 27;
    boy.hp  = 10000;
    map.show_map();
    boy.move_boy(map.forest);
    intface.draw(boy.hp, 0, boy.invent);

    badboys = new monsters_family(map.forest, 0);
    badboys->give_some_boys_rand(1);

    for (int i = 0; i < count_of_monsters; i++) {

        badboys->give_some_boys_rand(3, 20, 29, 0, 100);
        badboys->give_some_boys_rand(3, 20, 29, 0, 100);
    }

    std::random_device rd;  // ������������ ��� ��������� ���������� �������� (seed)
    std::mt19937 gen(rd()); // ��������� ��������� ����� (Mersenne Twister)

    std::uniform_int_distribution<> disx(0, 7); // ����������� ������������� �� 0 �� 

    house_number = disx(gen);
   /* house_number = 0;*/
    badboys->monsters_move(1);
}

void level_village::update()
{
    while (!exit_) {

        if (gotofind)
            nscore = 1;

        if (map.forest[boy.y][boy.x] == '2') {
            if (house_counter == house_number) {
                ifound = true;

            }
            else {

                bool check = true;
                std::pair<int, int> boy_c{ boy.x, boy.y };

                for (int i = 0; i < visited.size(); i++) {
                    if (visited[i] == boy_c)
                        check = false;
                }
                if (check) {
                    visited.push_back({ boy.x, boy.y });
                    house_counter++;
                }
                intface.subs(" ����� ", "");
            }
        }

        if(ifound)

        if (boy.hp <= 0) {
            dead();
            clear();
            continue;
        }

        if (boy.x > 65 && boy.x < 80 && boy.y == 0) {
            break;
        }
        moving();

        draw();
    }
}

void level_village::score_set()
{
    switch (nscore)
    {


    case 1:
        intface.score("������� ����");
        break;

    case 2:
        intface.score("������������� �� ����");
        break;

    default:
        break;
    }
}

void level_village::draw()
{

    clear();

    map.show_map();
    boy.move_boy(map.forest);

    if (move)
        boy.hp -= badboys->monsters_move(false);
    else
        badboys->monsters_move(true);

    intface.draw(boy.hp, boy.count_of_m, boy.invent);
    game_iter++;
    score_set();
}

void level_village::moving()
{
    move = make_move(map.forest);

    if (move) { ////////.............
        game_iter++;
        badboys->find(boy.x, boy.y);
    }
    else {
        sci--;

    }
}
