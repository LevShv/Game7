#include <vector>
#include <string>
#pragma once
struct Point {

    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct monster_type
{
    std::string name;
	char icon;
	int color;
    std::vector<Point> directions;
    int delay;
    int power;
    int radius;
    int hp;
    

};



