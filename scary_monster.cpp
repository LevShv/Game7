#include "scary_monster.h"
#include <curses.h>
#include <vector>
#include <windows.h>


scary_monster::scary_monster(int spx, int spy, char** give_me_map) :

    x(spx),
    y(spy),
    iterofwaypoint(0),
    map(give_me_map)

    {
    width = 120;
    length = 28;
    }    

    void scary_monster::give_waythim(int bx, int by) {

        iterofwaypoint = 1;
        if (pow(by - x, 2) + pow(bx - y, 2) < pow(10,2)) {
            iseeya = true;
            way = shortestPath(bx, by);
        }      
    }
    
    std::vector<scary_monster::Point> scary_monster::shortestPath(int bx, int by) {

        scary_monster::Point start = { x, y };
        scary_monster::Point end = { by ,bx };

        int rows = length;
        int cols = width;

        std::vector<scary_monster::Point> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1},
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
        };

        std::queue<scary_monster::Point> q;
        std::unordered_set<scary_monster::Point, scary_monster::PointHash> visited;
        std::unordered_map<scary_monster::Point, scary_monster::Point, scary_monster::PointHash> path;

        q.push(start);
        visited.insert(start);
        path[start] = { -1, -1 }; // Инициализация начальной точки

        while (!q.empty()) {

            scary_monster::Point current = q.front();
            q.pop();

            if (current.x == end.x && current.y == end.y) {
                // Восстановление пути
                std::vector<scary_monster::Point> resultPath;
                while (current.x != -1 && current.y != -1) {
                    resultPath.push_back(current);
                    current = path[current];
                }
                reverse(resultPath.begin(), resultPath.end());
                return resultPath;
            }

            for (const auto& dir : directions) {
                scary_monster::Point next = { current.x + dir.x, current.y + dir.y };

                if (next.x >= 0 && next.x < rows && next.y >= 0 && next.y < cols && /* ++x < width && ++y < length &&*/
                    map[next.x][next.y] == ' ' && visited.find(next) == visited.end()) {
                    q.push(next);
                    visited.insert(next);
                    path[next] = current;
                }
            }
        }

        return {};
    }

    int scary_monster::move_monster()
    {
        
        if (way.size() != 0 && iterofwaypoint < way.size() - 1 && iseeya == true && delay == false) {
            
            lx = x;
            ly = y;
            x = way[iterofwaypoint].x;
            y = way[iterofwaypoint].y;
            

            attron(COLOR_PAIR(5));
            move(x, y);
           // map[x][y] = 'W';

           ///* if(started)*/
           //     map[lx][ly] = ' ';

           // started = true;
            printw("W");
            attroff(COLOR_PAIR(5));

            iterofwaypoint++;
            delay = true;
            return 0;
        }
        else {

            attron(COLOR_PAIR(5));
            move(x, y);
            printw("W");
            attroff(COLOR_PAIR(5));

            delay = false;
        }

        if (iterofwaypoint == way.size()-1)
            return 1;

        return 2;
    }

    

   








