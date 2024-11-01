
#include <random>
#include <curses.h>
#include <my_map.h>
#include "my_boy.h"
#include <monster.h>
#include <set>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

//void draw_big_letter(int start_x, int start_y, const char* letter[5]) {
//    for (int i = 0; i < 5; ++i) {
//        mvprintw(start_y + i, start_x, letter[i]);
//    }
//}
//
//void hello_screen() {
//
//    int start_wrx = 40;
//    int start_wry = 20;
//
//    int start_x = 40;
//    int start_y = 10;
//
//    int width = 40;
//    int height = 6;
//
//    //const char* game7_matrix[5][5] = {
//
//    //{ " G  ", "G G ", "GGG ", "G G ", "G G " }, // G
//    //{ "A   ", "A A ", "AAA ", "A A ", "A A " }, // A
//    //{ "M   ", "MM M", "M M ", "M M ", "M M " }, // M
//    //{ "E   ", "EEE ", "E   ", "EEE ", "E   " }, // E
//    //{ "7   ", "  7 ", " 7  ", "7   ", "7   " }  // 7
//    //};
//    const char* game7_matrix[5][10] = {
//    { "  GGGG  ", " G    G ", "G      G", "G      G", "G      G", "G      G", "G      G", "G      G", " G    G ", "  GGGG  " }, // G
//    { " AAAAAA ", "A      A", "A      A", "A      A", "AAAAAAA ", "A      A", "A      A", "A      A", "A      A", " AAAAAA " }, // A
//    { " M     M", "MM    MM", "M M  M M", "M  MM  M", "M   M  M", "M     M", "M     M", "M      M", "M      M", "M      M" }, // M
//    { " EEEEEE ", "E       ", "E       ", "E       ", " EEEEEEE", "E       ", "E       ", "E       ", "E       ", " EEEEEE " }, // E
//    { " 777777 ", "     7  ", "    7   ", "   7    ", "  7     ", " 7      ", " 7      ", " 7      ", " 7      ", " 7      " }  // 7
//    };
//
//    draw_big_letter(start_wrx,      start_wry, game7_matrix[0]); // G
//    draw_big_letter(start_wrx + 10, start_wry, game7_matrix[1]); // A
//    draw_big_letter(start_wrx + 20, start_wry, game7_matrix[2]); // M
//    draw_big_letter(start_wrx + 30, start_wry, game7_matrix[3]); // E
//    draw_big_letter(start_wrx + 40, start_wry, game7_matrix[4]); // 7
//
//   /* box(stdscr, 0, 0);*/
//    /*box(stdscr, 0, 0);*/
//    mvhline(start_y, start_x, 0, width); 
//    mvhline(start_y + height, start_x, 0, width); 
//    mvvline(start_y, start_x, 0, height); 
//    mvvline(start_y, start_x + width, 0, height); 
//    mvaddch(start_y, start_x, ACS_ULCORNER); 
//    mvaddch(start_y, start_x + width, ACS_URCORNER); 
//    mvaddch(start_y + height, start_x, ACS_LLCORNER); 
//    mvaddch(start_y + height, start_x + width, ACS_LRCORNER); 
//
//    mvprintw(60, 20, "START");
//    refresh();
//
//    // Ожидание ввода пользователя
//    getch();
//
//}

class scary_monster {
private:

    struct Point {
        int x, y;
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    // Хэш-функция для Point
    struct PointHash {
        size_t operator()(const Point& p) const {
            return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
        }
    };

    

    int x;
    int y;

    int width;
    int length;


    std::vector<Point> shortestPath(int bx, int by, char** map) {

        Point start = { x, y };
        Point end = { by ,bx };

        int rows = length;
        int cols = width;

        std::vector<Point> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}, // Вверх, вниз, влево, вправо
            {-1, -1}, {-1, 1}, {1, -1}, {1, 1} // Диагонали: вверх-влево, вверх-вправо, вниз-влево, вниз-вправо
        };

        std::queue<Point> q;
        std::unordered_set<Point, PointHash> visited;
        std::unordered_map<Point, Point, PointHash> path;

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
                    map[next.x][next.y] == ' ' && visited.find(next) == visited.end()) {
                    q.push(next);
                    visited.insert(next);
                    path[next] = current;
                }
            }
        }

        return {}; // Если путь не найден
    }

    public:

        scary_monster(int spx, int spy, int width_of_area, int length_of_area) :

            x(spx),
            y(spy),
            width(width_of_area),
            length(length_of_area)

        {}
        
        void move_monster(int bx, int by, char** map){

            std::vector<Point> path = shortestPath(bx, by, map);

            for (const auto& p : path) {
                move(p.x, p.y);
                printw("w");
            }
        }
    


    
};

int main()
{ 

    
    int width = 120;
    int length = 30;
    int frame_rate = 100;

    int start_pos_x = 1;
    int start_pos_y = 1;

  /*  system("chcp 1251");*/

    initscr();
    curs_set(0);
    noecho();
 /*   hello_screen();*/

    my_map map(width, length);
    map.show_map();

    my_boy boy(start_pos_x,start_pos_y);

    scary_monster W (5, 5, width, length);

    while (true) {
        switch (getch()) {
        case 'w':
            if (0 < boy.y) {
                boy.y--;
            }
            break;
        case 's':
            if (boy.y < length-1) {
                boy.y++;
            }
            break;
        case 'a':
            if (boy.x > 0) {
                boy.x--;
            }
            break;
        case 'd':
            if (boy.x < width-1) {
                boy.x++;
            }
            break;
        case 'q':

          
        default:
            break;
        }
      /*   timeout(100);*/
        clear();

        map.show_map();
        boy.move_boy(map.forest);
        W.move_monster(boy.x,boy.y,map.forest);
        
       /* refresh();*/


    }
    
    getch();
    endwin();
   /* delete map;*/
   /* vec start_pos{ 10,10 };
    vec step{ 1,0 };

    int framerate = 100;*/
}
