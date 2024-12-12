#include <curses.h>
#include <my_map.h>
#include <random>



    my_map::my_map(int width_of_map, int length_of_map) : width(width_of_map), length(length_of_map){

        forest = new char* [length];
        create_map(1);
    }

    void my_map::create_map(int level)
    {
        make_claen_map();

        switch (level)
        {
        case 1: 

            add_trees();
            add_to_map(home, 10, 5);
            break;
        case 2: 

            add_trees();
            add_mushrooms();
            break;
        
        default:
            break;
        }
     

    }

    void my_map::show_map(){

        for (int i = 0; i < length; i++) {
            char* str = forest[i];

            for (int j = 0; j < width; j++) {
                if (*str == '.') {

                    attron(COLOR_PAIR(8));
                    printw("%c", *str);
                    attroff(COLOR_PAIR(8));

                }
                else {
               

                    attron(COLOR_PAIR(4));
                    printw("%c", *str);

                    attroff(COLOR_PAIR(4));
                }
                str++;
                
            }
         
        }
    }
    my_map::~my_map() {
        
        for (int i = 0; i < length; i++)
            delete[] forest[i];
        delete[] forest;
    }

    

    void my_map::make_claen_map()
    {
        for (int i = 0; i < length; i++) {

            forest[i] = new char[width];

            for (int j = 0; j < width; j++) {
                forest[i][j] = ' ';
            }
        }
    }

    void my_map::add_to_map(std::vector<std::vector<char>> addon, int posx, int posy)
    {
        for (int i = 0; i < addon.size(); i++) {

          /*  forest[i] = new char[width];*/

            for (int j = 0; j < addon[0].size(); j++) {
                forest[i + posx][j + posy] = addon[i][j];
            }
        }
    }

    void my_map::add_mushrooms()
    {
        for (int i = 0; i < 20; ++i) {
            int rx = random_x();
            int ry = random_y();
            if (forest[ry][rx] == ' ')
                forest[ry][rx] = '.';
            else
                i--;
        }
    }

    void my_map::add_trees() {

        for (int i = 0; i < 500; ++i) {
            int rx = random_x();
            int ry = random_y();
            forest[ry][rx] = 'T';
        }
  
    }

    int my_map::random_x()
    {

        std::random_device rd;  // Используется для получения начального значения (seed)
        std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)

        std::uniform_int_distribution<> disx(1, width - 1); // Равномерное распределение от 0 до 

        return disx(gen);
    }

    int my_map::random_y()
    {

        std::random_device rd;  // Используется для получения начального значения (seed)
        std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)

        std::uniform_int_distribution<> disy(1, length - 1);

        return disy(gen);
    }
