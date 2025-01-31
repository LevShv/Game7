#include "scary_monster.h"
#include <curses.h>
#include "monster_type.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>


scary_monster::scary_monster(int spx, int spy, char** give_me_map, monster_type* mon)
    : x(spx),
    y(spy),
    iterofwaypoint(0),
    monster(mon),
    map(give_me_map),
    directions(mon->directions),
    power(mon->power),
    icon(mon->icon),
    color(mon->color),
    color_in_1(mon->color_in_1),
    delay(mon->delay),
    radius(mon->radius),
    hp(mon->hp),
    can_go_throw(mon->can_go_throw)
{
   
}

    void scary_monster::give_waythim(int bx, int by) {

        iterofwaypoint = 1;
        if (pow(by - x, 2) + pow(bx - y, 2) < pow(radius,2)) {
            iseeya = true;
            way = shortestPath(bx, by);
        }      
    }
    
    std::vector<Point> scary_monster::shortestPath(int bx, int by) {
        Point start = { x, y };
        Point end = { by, bx }; // Исправлено: bx и by поменяны местами

        int rows = 28;
        int cols = 120;

        std::queue<Point> q;
        std::unordered_set<Point, scary_monster::PointHash> visited;
        std::unordered_map<Point, Point, scary_monster::PointHash> path;

        q.push(start);
        visited.insert(start);
        path[start] = { -1, -1 }; // Инициализация начальной точки

        while (!q.empty()) {
            Point current = q.front();
            q.pop();

            // Если достигли конечной точки, восстанавливаем путь
            if (current.x == end.x && current.y == end.y) {
                std::vector<Point> resultPath;
                while (current.x != -1 && current.y != -1) {
                    resultPath.push_back(current);
                    current = path[current];
                }
                reverse(resultPath.begin(), resultPath.end());
                return resultPath;
            }

            // Проверяем все возможные направления
            for (const auto& dir : directions) {
                Point next = { current.x + dir.x, current.y + dir.y };

                // Проверяем, находится ли следующая точка в пределах карты
                if (next.x >= 0 && next.x < rows && next.y >= 0 && next.y < cols) {
                    // Проверяем, может ли монстр пройти через стену
                    bool can_go = false;

                    if (can_go_throw) {
                        // Монстр может ходить сквозь стены
                        can_go = true;
                    }
                    else {
                        // Монстр не может ходить сквозь стены
                        can_go = (map[next.x][next.y] == ' ' || map[next.x][next.y] == '1' || map[next.x][next.y] == 'o');
                    }

                    // Если можно пройти и точка не посещена, добавляем её в очередь
                    if (can_go && visited.find(next) == visited.end()) {
                        q.push(next);
                        visited.insert(next);
                        path[next] = current;
                    }
                }
            }
        }

        // Если путь не найден, возвращаем пустой вектор
        return {};
    }
    int scary_monster::move_monster(bool stop)
    {
        
        if (way.size() != 0 && iterofwaypoint < way.size() - 1 && alive && iseeya && (delay_observer % delay == 0) &&  stop == false) {
            
            x = way[iterofwaypoint].x;
            y = way[iterofwaypoint].y;

            if (map[x][y] == 'o')
                alive = false;

            print_me();

            iterofwaypoint++;
            delay_observer = 1;
            return 0;
        }
        else {
            print_me();

            delay_observer++;
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


    

   








