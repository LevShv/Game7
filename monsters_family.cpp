#include "monsters_family.h"
#include <random>
#include <vector>
#include "monster_type.h"
#include <curses.h>



monsters_family::monsters_family(char** give_me_map, monster_type* first_type) : map(give_me_map) {
    give_some_boys_rand(first_type);
}

monsters_family::monsters_family(char** give_me_map, int mType)
{

}

monsters_family::~monsters_family() {

    for (monster_type* type : types) {
        delete type;
}
    delete Monsters;
}

void monsters_family::give_some_boys_rand(monster_type* type) {

   
    int rx, ry;
    random_point(&rx, &ry);

    while (map[ry][rx] != ' ') {
        random_point(&rx, &ry);
    }

    scary_monster W(ry, rx, map, type);

    Monsters->push_back(W);
}

void monsters_family::give_some_boys_rand(monster_type* type, int start_row, int end_row, int start_col, int end_col) {


    int rx, ry;
    random_point(&rx, &ry);

    while (map[ry][rx] != ' ' &&
        rx >= start_col && rx <= end_col &&
        ry >= start_row && ry <= end_row) {

        random_point(&rx, &ry);
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

    void monsters_family::monsters_data()
    {
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

        types.push_back(W);
        types.push_back(Y);
    }

    void monsters_family::random_point(int* rx, int* ry) {

        std::random_device rd;  // Используется для получения начального значения (seed)
        std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)

        std::uniform_int_distribution<> disx(1, 120 - 1); // Равномерное распределение от 0 до 
        std::uniform_int_distribution<> disy(1, 28 - 1);

        *rx = disx(gen);
        *ry = disy(gen);
    }
