#include "monsters_family.h"
#include <random>


monsters_family::monsters_family(char** give_me_map) : map(give_me_map) {
    create_two_boys();
}

monsters_family::~monsters_family() {
    delete Monsters;
}

void monsters_family::give_some_boys_rand() {

    std::random_device rd;  // Используется для получения начального значения (seed)
    std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)

    std::uniform_int_distribution<> disx(1, 120 - 1); // Равномерное распределение от 0 до 
    std::uniform_int_distribution<> disy(1, 28 - 1);

    int rx = disx(gen);
    int ry = disy(gen);

    scary_monster W(ry, rx, map);

    Monsters->push_back(W);
}

    void monsters_family::find(int x, int y) {
        for (scary_monster& M : *Monsters)
        {
            M.give_waythim(x, y);
        }
    }

    int monsters_family::monsters_move() {

        int hp = 0;

        for (int i = 0; i < Monsters->size()-1; i++)
        {
            for (int j = i+1; j < Monsters->size(); j++)
            {
                if ((*Monsters)[i].x == (*Monsters)[j].x && (*Monsters)[i].y == (*Monsters)[j].y) {
                    (*Monsters)[i].x++;
                }
            }
        }

        for (scary_monster& M : *Monsters)
        {
            if (M.move_monster() == 1)
                hp++;

        }
        return hp;
    }


    
    void monsters_family::create_two_boys() {
        scary_monster W(7, 67, map);
        scary_monster I(18, 51, map);

        Monsters->push_back(W);
        Monsters->push_back(I);
    }
