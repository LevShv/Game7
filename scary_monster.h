#pragma once
#include <set>
#include <vector>

#include "monster_type.h"

class scary_monster {

public:

    int x;
    int y;

    int power;

    scary_monster(int spx, int spy, char** give_me_map, monster_type* mon);

    void give_waythim(int bx, int by);
    int move_monster(bool stop);

    
    
private:

    bool started = false;
    bool alive = true;

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
  
    char icon;
    int color;
    int color_in_1;
    const std::vector<Point>& directions;
    int delay;

    int radius ;
    int hp;
        

};

