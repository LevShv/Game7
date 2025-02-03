
#include "final_boss.h"
#include <curses.h>
#include "monster_type.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <thread>




void final_boss::give_map(char** Map) {
    map = Map;
}

void final_boss::give_waythim(int bx, int by, int& hp) {

    iterofwaypoint = 1;

    if (pow(by - x, 2) + pow(bx - y, 2) < pow(radius, 2) && alive) {

        if (wait(last_time_shoot, 1000))
            shoot_arrow(by, bx, hp);

        iseeya = true;
        way = shortestPath(bx, by);
    }

}

std::vector<Point> final_boss::shortestPath(int bx, int by) {

    Point start = { x, y };
    Point end = { by, bx }; // Исправлено: bx и by поменяны местами

    int rows = 28;
    int cols = 120;

    std::queue<Point> q;
    std::unordered_set<Point, final_boss::PointHash> visited;
    std::unordered_map<Point, Point, final_boss::PointHash> path;

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

int final_boss::move_monster(bool stop, int bx, int by)
{
    if (hp <= 0)
        alive = false;

    if (x > 27 || y > 119)
        return 0;


    if (way.size() != 0
        && iterofwaypoint < way.size() - 1
        && alive
        && iseeya
        && (delay_observer % delay == 0) 
        && stop == false 
        && wait(last_time_walk, 400)) 
    {

        x = way[iterofwaypoint].x;
        y = way[iterofwaypoint].y;

        print_me();

        iterofwaypoint++;
        delay_observer = 1;

        return 2;
    }
    else {
        print_me();

        delay_observer++;
    }

    if (iterofwaypoint == way.size() - 1 && alive/*&& check_boy()*/)
        return 1;


    return 0;
}

void final_boss::print_me()
{
    move(x, y);
    if (alive) {
        if (map[x][y] == '1') {
            attron(color_in_1);
            addch(icon);
            attroff(color_in_1);
        }
        else {
            attron(color);
            addch(icon);
            attroff(color);
        }
    }
    else
        if (map[x][y] == '1') {
            attron(color_in_1);
            addch('x');
            attroff(color_in_1);
        }
        else {
            attron(color);
            addch('x');
            attroff(color);
        }

}
bool final_boss::wait(std::chrono::time_point<std::chrono::steady_clock> &last_time, int pause)
{

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count();


    if (elapsed > pause) {

        last_time = now;
        return true;
        
    }

    else {
        return false;

    }
}
void final_boss::shoot_arrow(int by, int bx, int&hp)
{
    int mx = y, my = x;
    int dirx, diry;

    

    if (bx == mx) {
        // Вертикальная стрельба (вверх или вниз)
        if (by - my > 0) {
            diry = 1;  // стреляем вверх
            dirx = 0;
        }
        else if (by - my < 0) {
            diry = -1; // стреляем вниз
            dirx = 0;
        }
    }
    else if (by == my) {
        // Горизонтальная стрельба (влево или вправо)
        if (bx - mx > 0) {
            dirx = 1;  // стреляем вправо
            diry = 0;
        }
        else if (bx - mx < 0) {
            dirx = -1; // стреляем влево
            diry = 0;
        }
    }
    else {
        // Диагональная стрельба
        if (bx - mx > 0 && by - my > 0) {
            dirx = 1;  // стреляем вправо-вверх
            diry = 1;
        }
        else if (bx - mx > 0 && by - my < 0) {
            dirx = 1;  // стреляем вправо-вниз
            diry = -1;
        }
        else if (bx - mx < 0 && by - my > 0) {
            dirx = -1; // стреляем влево-вверх
            diry = 1;
        }
        else if (bx - mx < 0 && by - my < 0) {
            dirx = -1; // стреляем влево-вниз
            diry = -1;
        }
        else
            return;
    }
    
    if(bx == mx && by == my)
        return;

   /* else return;*/

    int radius = 30;
    int count = 0;

    /*copy_maps();
    badboys->make_map_with_monsters(map_with_monsters);*/

    int i = my;
    int j = mx;

    while (true) {

        i += diry;
        j += dirx;

        count++;

        if (i >= 0 && i < length && j >= 0 && !(by == i && bx == j) && j < width && (map[i][j] == ' ' || map[i][j] == '1') && count <= radius) {
            ::move(i, j);
            if (map[i][j] == ' ') {
                attron(COLOR_PAIR(51));
                addch('*');
                attroff(COLOR_PAIR(52));
            }
            else {
                attron(COLOR_PAIR(51));
                addch('*');
                attroff(COLOR_PAIR(52));
            }
            refresh();
            continue;
        }
        if (i < 0 || i >= length || j < 0 || j >= width) {
            break;
        }

        if (by == i && bx == j){
            hp -= 2;
            break;
        }
        else {
            break;
        }

        
    }



    //for (int i = 0; j < badboys.; j++) {
    //    //if (Monsters[i].x == Monsters[j].x && Monsters[i].y == Monsters[j].y) {
    //    //    Monsters[i].x++; // Сдвигаем монстра вправо
    //    //}
    //}
}













