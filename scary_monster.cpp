#include "scary_monster.h"
#include <curses.h>
#include <vector>
#include <windows.h>
#include "monster_type.h"


scary_monster::scary_monster(int spx, int spy, char** give_me_map, monster_type* mon) :

    x(spx),
    y(spy),
    iterofwaypoint(0),
    monster(mon),
    map(give_me_map)

    {
    width = 120;
    length = 28;
    power = monster->power;
    }    

    void scary_monster::give_waythim(int bx, int by) {

        iterofwaypoint = 1;
        if (pow(by - x, 2) + pow(bx - y, 2) < pow(monster->radius,2)) {
            iseeya = true;
            way = shortestPath(bx, by);
        }      
    }
    
    std::vector<Point> scary_monster::shortestPath(int bx, int by) {

        Point start = { x, y };
        Point end = { by ,bx };

        int rows = length;
        int cols = width;

        std::vector<Point> directions = monster->directions;/*{
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
        };*/

        std::queue<Point> q;
        std::unordered_set<Point, scary_monster::PointHash> visited;
        std::unordered_map<Point, Point, scary_monster::PointHash> path;

        q.push(start);
        visited.insert(start);
        path[start] = { -1, -1 }; // Инициализация начальной точки

        while (!q.empty()) {

            Point current = q.front();
            q.pop();

            if (current.x == end.x && current.y == end.y) {
                // Восстановление пути
                std::vector<Point> resultPath;
                while (current.x != -1 && current.y != -1) {
                    resultPath.push_back(current);
                    current = path[current];
                }
                reverse(resultPath.begin(), resultPath.end());
                return resultPath;
            }

            for (const auto& dir : directions) {
                Point next = { current.x + dir.x, current.y + dir.y };

                if (next.x >= 0 && next.x < rows && next.y >= 0 && next.y < cols && /* ++x < width && ++y < length &&*/
                    (map[next.x][next.y] == ' ' || map[next.x][next.y] == '1' || map[next.x][next.y] == 'o')
                    && visited.find(next) == visited.end()) {
                    q.push(next);
                    visited.insert(next);
                    path[next] = current;
                }
            }
        }

        return {};
    }

    int scary_monster::move_monster(bool stop)
    {
        
        if (way.size() != 0 && iterofwaypoint < way.size() - 1 && alive && iseeya && (delay % monster->delay == 0) && stop == false) {
            
            x = way[iterofwaypoint].x;
            y = way[iterofwaypoint].y;

            if (map[x][y] == 'o')
                alive = false;

            print_me();

            iterofwaypoint++;
            delay = 1;
            return 0;
        }
        else {
            print_me();

            delay++;
        }

        if (iterofwaypoint == way.size() - 1 && alive/*&& check_boy()*/)
            return 1;
        

        return 0;
    }

    void scary_monster::print_me()
    {
        move(x, y);
        if (alive) {
            if (map[x][y] == '1') {
                attron(monster->color_in_1);
                addch(monster->icon);
                attroff(monster->color_in_1);
            }
            else {
                attron(monster->color);
                addch(monster->icon);
                attroff(monster->color);
            }
        }
        else
            if (map[x][y] == '1') {
                attron(monster->color_in_1);
                addch('x');
                attroff(monster->color_in_1);
            }
            else {
                attron(monster->color);
                addch('x');
                attroff(monster->color);
            }
        
    }


    

   








