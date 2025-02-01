#pragma once
#include <set>
#include <vector>

#include "monster_type.h"

class scary_monster {

public:

    int x;
    int y;
    char icon;
    int power;
    int hp;
    bool alive = true;

    scary_monster(int spx, int spy, char** give_me_map, monster_type* mon);

    void give_waythim(int bx, int by);
    void moveTowards(int target_x, int target_y);
    int move_monster(bool stop);

    
    
private:

    int delay_observer = 0;
    bool started = false;


    int iterofwaypoint = 0;
    char** map;

    bool iseeya = false;

    struct PointHash {

        size_t operator()(const Point& p) const {
            return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
        }
    };
    
    monster_type* monster;

    std::vector<Point> way;
    std::vector<Point> shortestPath(int bx, int by);

    void print_me();
  

    int color;
    int color_in_1;
    const std::vector<Point>& directions;
    int delay;

    int radius;
    
    bool can_go_throw;
        

};

