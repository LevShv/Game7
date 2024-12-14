#include <curses.h>
#include <my_map.h>
#include <iostream>
#include <fstream>
#include <random>




    my_map::my_map(int width_of_map, int length_of_map, int lv) : width(width_of_map), length(length_of_map),level(lv){

        forest = new char* [length];
        create_map(level);
    }

    void my_map::create_map(int level)
    {
        make_claen_map();

        switch (level)
        {
        case 1: 

            get_data_ff(river, "river2.txt");
            add_to_map(river, 10, 0);

            add_trees(10,12,100); // y x
            add_trees(27,87,50);

            add_to_map(home, 6, 18); // y x

            break;
        case 2: 

            add_trees(300);
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
                if (*str == '~') {

                    attron(COLOR_PAIR(12));
                    printw("%c", *str);
                    attroff(COLOR_PAIR(12));
                    
                }
                else if (*str == '1') {

                    attron(COLOR_PAIR(14));
                    printw("%c", *str);
                    attroff(COLOR_PAIR(14));

                }
                else if (*str == '2') {

                    attron(COLOR_PAIR(14));
                    printw("%c", *str);
                    attroff(COLOR_PAIR(14));

                }
                else if (*str == '.') {
                    attron(COLOR_PAIR(8));
                    printw("%c", *str);
                    attroff(COLOR_PAIR(8));
                }
                else if (*str == '_') {
                    attron(COLOR_PAIR(8));
                    addch('_'); //151
                    attroff(COLOR_PAIR(8));
                }
                else if (*str == '|') {
                    attron(COLOR_PAIR(8));
                    addch(124);
                    attroff(COLOR_PAIR(8));
                }
                else if (*str == 'g') {     // Кровать подушка

                    attron(COLOR_PAIR(17));
                    addch(' ');
                    attroff(COLOR_PAIR(17));

                }
                else if (*str == 'S') {        

                    attron(COLOR_PAIR(19));
                    addch('S');
                    attroff(COLOR_PAIR(19)); // Старец

                }
                else if (*str == (char)133) {

                    attron(COLOR_PAIR(22));
                    addch(133);
                    attroff(COLOR_PAIR(22)); // красный гриб

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

    void my_map::add_to_map(std::vector<std::vector<char>> addon,  int posx, int posy )
    {
        for (int i = 0; i < addon.size(); i++) {

          /*  forest[i] = new char[width];*/

            for (int j = 0; j < addon[i].size(); j++) {
                forest[i + posy][j + posx] = addon[i][j];
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

    void my_map::add_redmushrooms(int count,int posx, int posy)
    {
        for (int i = 0; i < count; ++i) {
            int rx = random_x();
            int ry = random_y();
         
            if (forest[ry][rx] == ' ' && ry < posx && rx > posy)
                forest[ry][rx] = 133;
            else
                i--;
        }
    }

    void my_map::get_data_ff(std::vector<std::vector<char>>& mapobj, std::string name)
    {
        std::ifstream inputFile(name);
        std::string line;

        while (std::getline(inputFile, line)) { 
            std::vector<char> row;

            for (char ch : line) {
                row.push_back(ch);
            }
            mapobj.push_back(row);
        }
        inputFile.close();
    }

    void my_map::add_trees( int count) {

        for (int i = 0; i < count; ++i) {
            int rx = random_x();
            int ry = random_y();
            if (forest[ry][rx] == ' ')
                forest[ry][rx] = 'T';
            else
                i--;
        }
  
    }

    void my_map::add_trees(int posx1, int posy1, int posx2, int posy2, int count)
    {
        for (int i = 0; i < count; ++i) {
            int rx = random_x();
            int ry = random_y();

            if (forest[ry][rx] == ' ' && ry < posx1 && rx > posy1 && ry < posx2 && rx > posy2)
                forest[ry][rx] = 'T';
            else
                i--;
        }
    }

    void my_map::add_trees(int posx, int posy, int count)
    {
        for (int i = 0; i < count; ++i) {
            int rx = random_x();
            int ry = random_y();
            
            if (forest[ry][rx] == ' ' && ry < posx && rx > posy)
                forest[ry][rx] = 'T';
            else
                i--;
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
