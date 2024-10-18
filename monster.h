#pragma once
#include <set>
#include <vector>
#include <curses.h>

class monster {
public:

    int x;
    int y;

    int width;
    int length;


    monster(int spx, int spy, int width_of_area, int length_of_area);

    void move_monster(int boy_x, int boy_y, char** map);

private:

    struct point
    {
    public:
        point(int X, int Y) : x(X), y(Y) {}

        int x;
        int y;

        int move;
        int weight;

        bool operator>>(const point& other) const {

            return x == other.x && y == other.y;

        }

        bool operator<(const point& other) const {

            if (weight < other.weight)
                return true;
            if (weight == other.weight && weight < other.weight)
                return true;
            return false;
        }

    };
    bool check_in_way(std::vector<point> way, point point);

    /*  std::set<point>PointAdd(point active_point, point p, point boy, openlist ) {

          p.cfx = active_point.x;
          p.cfy = active_point.y;
          p.move = 10 + active_point.move;
          p.weight = p.move + pow(boy.x - p.x, 2) + pow(boy.y - p.y, 2);
          open_list.insert(p);

      }*/

};
