#include "monsters_family.h"
#include <random>
#include <vector>
#include "monster_type.h"



monsters_family::monsters_family(char** give_me_map, monster_type* first_type) : map(give_me_map) {
    give_some_boys_rand(first_type);
}

monsters_family::~monsters_family() {
    delete Monsters;
}

void monsters_family::give_some_boys_rand(monster_type* type) {

    std::random_device rd;  // ������������ ��� ��������� ���������� �������� (seed)
    std::mt19937 gen(rd()); // ��������� ��������� ����� (Mersenne Twister)
    
    std::uniform_int_distribution<> disx(1, 120 - 1); // ����������� ������������� �� 0 �� 
    std::uniform_int_distribution<> disy(1, 28 - 1);

    int rx, ry;

    rx = disx(gen);
    ry = disy(gen);

    while (map[ry][rx] != ' ') {

        rx = disx(gen);
        ry = disy(gen);
    }

    scary_monster W(ry, rx, map, type);

    Monsters->push_back(W);
}

void monsters_family::give_some_boys_rand(monster_type* type, int start_row, int end_row, int start_col, int end_col) {

    std::random_device rd;  // ������������ ��� ��������� ���������� �������� (seed)
    std::mt19937 gen(rd()); // ��������� ��������� ����� (Mersenne Twister)

    std::uniform_int_distribution<> disx(1, 120 - 1); // ����������� ������������� �� 0 �� 
    std::uniform_int_distribution<> disy(1, 28 - 1);

    int rx, ry;

    rx = disx(gen);
    ry = disy(gen);

    while (map[ry][rx] != ' ' 
        && (start_row > rx || rx > end_row)
        && (start_col > ry || ry > end_col)) {

        rx = disx(gen);
        ry = disy(gen);
    }

    scary_monster W(ry, rx, map, type);

    Monsters->push_back(W);
}



    void monsters_family::find(int x, int y) {
        for (scary_monster& M : *Monsters)
        {
            M.give_waythim(x, y);
        }
    }

    int monsters_family::monsters_move(bool stop) {

        int hp = 0;
        if (Monsters->size() > 2) {
            for (int i = 0; i < Monsters->size() - 1; i++)
            {
                for (int j = i + 1; j < Monsters->size(); j++)
                {
                    if ((*Monsters)[i].x == (*Monsters)[j].x && (*Monsters)[i].y == (*Monsters)[j].y) {
                        (*Monsters)[i].x++;
                    }
                }
            }
        }
        

        for (scary_monster& M : *Monsters)
        {
            if (M.move_monster(stop) == 1)
                hp += M.power;

        }
        return hp;
    }
  
    void monsters_family::create_two_boys(monster_type* type) {

        scary_monster W(7, 67, map, type);
        scary_monster I(18, 51, map, type);

        Monsters->push_back(W);
        Monsters->push_back(I);
    }
