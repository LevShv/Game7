#pragma once
#include <set>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

class scary_monster {

public:

    void give_waythim(int bx, int by, char** map);

    int move_monster();

    scary_monster(int spx, int spy, int width_of_area, int length_of_area);
    
private:

    int x;
    int y;

    int width;
    int length;
    int iterofwaypoint;
    struct Point {

        int x, y;

        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    struct PointHash {

        size_t operator()(const Point& p) const {
            return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
        }
    };

    std::vector<Point> way;

    std::vector<Point> shortestPath(int bx, int by, char** map);
    

    

};

