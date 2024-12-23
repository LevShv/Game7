#pragma once
#include <set>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "monster_type.h"

class scary_monster {

public:

    int x;
    int y;

    void give_waythim(int bx, int by);

    int move_monster(bool stop);

    scary_monster(int spx, int spy, char** give_me_map);
    
private:
    

    int bx;
    int by;

    bool started = false;

    int width;
    int length;
    int iterofwaypoint;
    char** map;

    bool iseeya = false;
    bool delay = false;

    int hp = 5;

    struct PointHash {

        size_t operator()(const Point& p) const {
            return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
        }
    };
    
    monster_type monster;
    std::vector<Point> way;

    std::vector<Point> shortestPath(int bx, int by);


};

