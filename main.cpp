
#include <random>
#include <vector>
#include <string>
#include <curses.h>
#include <my_map.h>
#include "my_boy.h"
#include <set>
#include <vector>


class monster{
public:

    int x;
    int y;

    int width;
    int length;


    monster(int spx, int spy, int width_of_area, int length_of_area) : x(spx), y(spy), width(width_of_area), length(length_of_area) {}

    void move_monster(int boy_x, int boy_y, char** map) {

        point boy(boy_y, boy_x);
        point active_point(x,y);

        std::set<point> open_list;
        std::vector<point> way ;

       /* way.push_back(active_point);*/
        active_point.move = 0;

        while (!(boy >> active_point)) {
           

            if (active_point.x + 1 < width && map[active_point.y][active_point.x + 1] == ' ') {
                point p = active_point;

                p.x++;
                if (check_in_way(way, p)) {
                    p.move = 10 + active_point.move;
                    p.weight = p.move + 10*(abs(boy.x - p.x) + abs(boy.y - p.y));

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
            if (active_point.y + 1 < length && map[active_point.y+1][active_point.x] == ' ' ) {
                point p = active_point;

                p.y++;
               
                if (check_in_way(way, p)) {
                    p.move = 10 + active_point.move;
                    p.weight = p.move + 10 * (abs(boy.x - p.x) + abs(boy.y - p.y));

                    open_list.insert(p);
                   
                    
                }

            }
            if (0 <= active_point.y - 1 && map[active_point.y-1][active_point.x] == ' ') {
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

private:

    struct point
    {
        public:
            point(int X, int Y ) : x(X), y(Y) {}

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
    bool check_in_way(std::vector<point> way, point point) {
        if (way.size() == 0)
            return true;

        for (const auto& p : way)
            if (p >> point)
                return false;
            else return true;
    }

  /*  std::set<point>PointAdd(point active_point, point p, point boy, openlist ) {

        p.cfx = active_point.x;
        p.cfy = active_point.y;
        p.move = 10 + active_point.move;
        p.weight = p.move + pow(boy.x - p.x, 2) + pow(boy.y - p.y, 2);
        open_list.insert(p);
        
    }*/

};
int main()
{ 
    int width = 120;
    int length = 30;
    int frame_rate = 100;

    int start_pos_x = 0;
    int start_pos_y = 0;

    system("chcp 1251");

    initscr();
    curs_set(0);
    noecho();
   /* timeout(frame_rate);*/

    my_map map(width, length);
    map.show_map();

    my_boy boy(start_pos_x,start_pos_y);
    monster W(5, 5, width, length);

    while (true) {
        switch (getch()) {
        case 'w':
            if (0 < boy.y) { //0<y<30
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
      /*  case 'q':

            stop*/
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
