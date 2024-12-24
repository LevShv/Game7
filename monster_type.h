#include <vector>
#include <string>
#pragma once
struct Point {
public:

    //Point(int x, int y) : x(x), y(y) {}
  /*  Point() {}*/

    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct monster_type
{
public:
 /*   monster_type(){}*/
    monster_type(

        const std::string& name, 
        char icon, 
        int color, 
        const std::vector<Point>& directions, 
        int delay, 
        int power, 
        int radius, 
        int hp)
        : 
        name(name), 
        icon(icon), 
        color(color), 
        directions(directions), 
        delay(delay), 
        power(power), 
        radius(radius), 
        hp(hp) 
    {}

    std::string name;
	char icon;
	int color;
    std::vector<Point> directions;
    int delay;
    int power;
    int radius;
    int hp;
    

};



