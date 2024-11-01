#include "monster.h"
#include <set>
#include <vector>
#include <curses.h>

monster::monster(int spx, int spy, int width_of_area, int length_of_area) : x(spx), y(spy), width(width_of_area), length(length_of_area) {}

void monster::move_monster(int boy_x, int boy_y, char** map) {

    point boy(boy_y, boy_x);
    point active_point(x, y);

    std::set<point> open_list;
    std::vector<point> way;

    /* way.push_back(active_point);*/
    active_point.move = 0;

    while (!(boy >> active_point)) {


        if (active_point.x + 1 < width && map[active_point.y][active_point.x + 1] == ' ') {
            point p = active_point;

            p.x++;
            if (check_in_way(way, p)) {
                p.move = 10 + active_point.move;
                p.weight = p.move + 10 * (abs(boy.x - p.x) + abs(boy.y - p.y));

                open_list.insert(p);


            }
            /*pow(boy.x - p.x, 2) + pow(boy.y - p.y, 2*/

        }
        if (0 <= active_point.x - 1 && map[active_point.y][active_point.x - 1] == ' ') {
            point p = active_point;

            p.x--;

            if (check_in_way(way, p)) {
                p.move = 10 + active_point.move;
                p.weight = p.move + 10 * (abs(boy.x - p.x) + abs(boy.y - p.y));

                open_list.insert(p);


            }

        }
        if (active_point.y + 1 < length && map[active_point.y + 1][active_point.x] == ' ') {
            point p = active_point;

            p.y++;

            if (check_in_way(way, p)) {
                p.move = 10 + active_point.move;
                p.weight = p.move + 10 * (abs(boy.x - p.x) + abs(boy.y - p.y));

                open_list.insert(p);


            }

        }
        if (0 <= active_point.y - 1 && map[active_point.y - 1][active_point.x] == ' ') {
            point p = active_point;
            p.y--;

            if (check_in_way(way, p)) {
                p.move = 10 + active_point.move;
                p.weight = p.move + 10 * (abs(boy.x - p.x) + abs(boy.y - p.y));

                open_list.insert(p);


            }
        }
        ///////

        if (0 <= active_point.y - 1 && map[active_point.y - 1][active_point.x] == ' ') {
            point p = active_point;
            p.y--;

            if (check_in_way(way, p)) {
                p.move = 10 + active_point.move;
                p.weight = p.move + 10 * (abs(boy.x - p.x) + abs(boy.y - p.y));

                open_list.insert(p);


            }
        }
        if (0 <= active_point.y - 1 && map[active_point.y - 1][active_point.x] == ' ') {
            point p = active_point;
            p.y--;

            if (check_in_way(way, p)) {
                p.move = 10 + active_point.move;
                p.weight = p.move + 10 * (abs(boy.x - p.x) + abs(boy.y - p.y));

                open_list.insert(p);


            }
        }
        if (0 <= active_point.y - 1 && map[active_point.y - 1][active_point.x] == ' ') {
            point p = active_point;
            p.y--;

            if (check_in_way(way, p)) {
                p.move = 10 + active_point.move;
                p.weight = p.move + 10 * (abs(boy.x - p.x) + abs(boy.y - p.y));

                open_list.insert(p);


            }
        }
        way.push_back(active_point);
        active_point = *open_list.begin();
        open_list.clear();

    }
    for (const auto& p : way) {
        move(p.x, p.y);
        printw("w");
    }
}

bool monster::check_in_way(std::vector<point> way, point point) {
    if (way.size() == 0)
        return true;

    for (const auto& p : way)
        if (p >> point)
            return false;
        else return true;
}
