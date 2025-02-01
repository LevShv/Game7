#include "monsters_family.h"
#include <random>
#include "monster_type.h"
#include <curses.h>
#include <chrono>
#include <iostream>



monsters_family::monsters_family(char** give_me_map, int type) : map(give_me_map) {

    monsters_data();
    //give_some_boys_rand(type);

    
}

monsters_family::monsters_family() {

    monsters_data();
}

monsters_family::~monsters_family() {

    for (monster_type* type : variations) {
        delete type;
}
   /* delete Monsters;*/
}

void monsters_family::give_some_boys_rand(int type) {


    int rx, ry;
    random_point(&rx, &ry);

    while (map[ry][rx] != ' ') {
        random_point(&rx, &ry);
    }

    scary_monster W(ry, rx, map, variations[type]);

    Monsters.push_back(W);
}

void monsters_family::give_some_boys_rand(int type, int start_row, int end_row, int start_col, int end_col) {
    int rx, ry;
    int attempts = 0;
    const int maxAttempts = 1000; // Максимальное количество попыток

    while (attempts < maxAttempts) {

        random_point(&rx, &ry);


        if (!(rx >= start_col && rx <= end_col && ry >= start_row && ry <= end_row)) {

            if (map[ry][rx] == ' ') {

                scary_monster W(ry, rx, map, variations[type]);
                Monsters.push_back(W);

                return; 
            }
        }
        attempts++;
    }
}

void monsters_family::give_some_boys_rand(bool reverse, int type, int start_row, int end_row, int start_col, int end_col)
{
    int rx, ry;
    int attempts = 0;
    const int maxAttempts = 1000; // Максимальное количество попыток

    while (attempts < maxAttempts) {

        random_point(&rx, &ry);


        if (rx >= start_col && rx <= end_col && ry >= start_row && ry <= end_row) {

            if (map[ry][rx] == ' ') {

                scary_monster W(ry, rx, map, variations[type]);
                Monsters.push_back(W);

                return;
            }
        }
        attempts++;
    }
}

void monsters_family::find(int x, int y) {
    for (scary_monster& M : Monsters)
    {
        M.give_waythim(x, y);
    }
}

int monsters_family::monsters_move(bool stop) {

    bool wait = false;

    static auto last_time = std::chrono::steady_clock::now();

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count();

    int hp = 0;

    if (elapsed > 100 && stop == false) {
          
        wait = false;
        last_time = now;
    }
            
    else {
        wait = true;
          
    }
    // Проверяем дубликаты только если монстры двигаются
    if (!wait && Monsters.size() > 1) {
        for (int i = 0; i < Monsters.size() - 1; i++) {
            for (int j = i + 1; j < Monsters.size(); j++) {
                if (Monsters[i].x == Monsters[j].x && Monsters[i].y == Monsters[j].y) {
                    Monsters[i].x++; // Сдвигаем монстра вправо
                }
            }
        }
    }

    // Движение монстров
    for (scary_monster& M : Monsters) {
        if (M.move_monster(wait) == 1)
            hp += M.power;
    }

    return hp;
}

void monsters_family::make_map_with_monsters(char** map_with_monsters)
{
    for (auto& M : Monsters) {
        map_with_monsters[M.x][M.y] = M.icon;
    }
}

void monsters_family::kill_monster(int x, int y)
{
    for (auto& M : Monsters) {
        if (M.x == x && M.y == y) {
            M.hp = 0;
            M.alive = false;
            break;
        }
                
    }
}
  
void monsters_family::create_two_boys(int type) {

    scary_monster W(7, 67, map, variations[type]);
    scary_monster I(18, 51, map, variations[type]);

    Monsters.push_back(W);
    Monsters.push_back(I);
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
        5,
        0);

    monster_type* Y = new monster_type(
        "Y",
        'Y',
        COLOR_PAIR(25),
        COLOR_PAIR(26),
        { /*{-1, 0}, {1, 0}, {0, -1}, {0, 1},*/
            {-1,-1}, {-1,1}, {1, -1}, {1, 1}, },
            1,
            3,
            15,
            5,
            0);
    monster_type* I = new monster_type(
        "I",
        'I',
        COLOR_PAIR(40),
        COLOR_PAIR(41),
        { {-1, 0}, {1, 0}, {0, -1}, {0, 1} },
        //{-1,-1}, {-1,1}, {1, -1}, {1, 1}, },
        1,
        3,
        15,
        5,
        0);
    monster_type *o = new monster_type(
        "o",
        'o',
        COLOR_PAIR(42),
        COLOR_PAIR(43),
        { {-1, 0}, {1, 0}, {0, -1}, {0, 1},
        {-1,-1}, {-1,1}, {1, -1}, {1, 1} },
        2,
        2,
        12,
        5,
        1);

    variations.push_back(W);
    variations.push_back(Y);
    variations.push_back(I);
    variations.push_back(o);
}

void monsters_family::random_point(int* rx, int* ry) {

    std::random_device rd;  // Используется для получения начального значения (seed)
    std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)

    std::uniform_int_distribution<> disx(1, 120 - 1); // Равномерное распределение от 0 до 
    std::uniform_int_distribution<> disy(1, 28 - 1);

    *rx = disx(gen);
    *ry = disy(gen);
}
