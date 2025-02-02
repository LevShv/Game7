#pragma once
#include <set>
#include <vector>
#include <curses.h>
#include <chrono>
#include "monster_type.h"
#include <future>

class final_boss {

public:

    int y = 100;
    int x = 15;
    char icon = 'M';
    int power = 2;
    int hp = 50;
    bool alive = true;

    void give_map(char** Map);

    void give_waythim(int bx, int by, int& hp);
   /* int move_monster(bool stop);*/
    int move_monster(bool stop, int bx, int by);



private:

    int length = 28;
    int width = 120;
    int delay_observer = 0;
    bool started = false;

    std::chrono::time_point<std::chrono::steady_clock> last_time_walk = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::steady_clock> last_time_shoot = std::chrono::steady_clock::now();

    int iterofwaypoint = 0;
    char** map;

    bool iseeya = false;

    struct PointHash {

        size_t operator()(const Point& p) const {
            return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
        }
    };
    std::future<std::vector<int>> future;
    std::vector<Point> way;
    std::vector<Point> shortestPath(int bx, int by);

    

    void print_me();
    bool wait(std::chrono::time_point<std::chrono::steady_clock>& last_time, int pause);
    void shoot_arrow(int y, int x, int& hp);


    int color = COLOR_PAIR(51);
    int color_in_1 = COLOR_PAIR(52);
    const std::vector<Point> directions 
            { {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1,-1}, {-1,1}, {1, -1}, {1, 1}, };
    int delay = 1;

    int radius = 30;
    bool can_go_throw = false;


};

