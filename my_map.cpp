
#include <my_map.h>
#include <random>
#include <file_tools.h>
#include <curses.h>

my_map::my_map(int width_of_map, int length_of_map, int lv) : width(width_of_map), length(length_of_map),level(lv){

    forest = new char* [length];
    create_map(level);
}

void my_map::create_map(int level)
{
    make_claen_map();
    file_tools ft;

    switch (level)
    {
    case 1: 

        ft.get_data_ff(base_of_map, "river2.txt");
        add_to_map(base_of_map, 10, 0);

        add_trees(10,12,100); // y x
        add_trees(27,87,50);

        add_to_map(home, 6, 18); // y x

        break;
    case 2: 

        add_trees(300);
        add_mushrooms('.',20,120,29);
        add_mushrooms(133, 30, 120, 29);
        break;
        
    case 3:

        ft.get_data_ff(base_of_map, "way_to_village.txt");
        add_to_map(base_of_map, 0, 0);
        add_trees(100);
        add_mushrooms(133, 20, 120, 29);
        add_mushrooms('.', 5, 120, 29);
        add_mushrooms(',', 3, 120, 29);
    
        break;

    default:
        break;
    }
     

}

void my_map::show_map(){
        
    for (int i = 0; i < length; i++) {
        char* str = forest[i];

        for (int j = 0; j < width; j++) {

            switch (*str)
            {
            case '~':
                print_char('~', COLOR_PAIR(12));
            break;

            case '1':
                print_char(' ', COLOR_PAIR(14));
            break;

            case '.':
                print_char('.', COLOR_PAIR(8));
                break;

            case '_':
                print_char('_', COLOR_PAIR(8));
                break;

            case '|':
                print_char(124, COLOR_PAIR(8));
                break;

            case 'g':
                print_char('g', COLOR_PAIR(17));
                break;

            case 'S':
                print_char('S', COLOR_PAIR(19));
                break;

            case (char)133:

                attron(COLOR_PAIR(22));
                addch(133); //151
                attroff(COLOR_PAIR(22));
                break;

            case ',':
                print_char(',', COLOR_PAIR(28));
                break;

            case 'o':
                print_char('o', COLOR_PAIR(28));
                break;
            default:
                print_char(*str, COLOR_PAIR(4));
                break;
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

void my_map::add_mushrooms(char obj, int count, int posx, int posy)
{
    for (int i = 0; i < count; ++i) {
        int rx = random_x();
        int ry = random_y();
        if (forest[ry][rx] == ' ' && ry < posx && rx > posy)
            forest[ry][rx] = obj;
        else
            i--;
    }
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

void my_map::print_char(char obj, int color)
{
    attron(color);
    addch(obj); //151
    attroff(color);
}
