#include "level.h"
#include <file_tools.h>
#include <chrono>

std::shared_ptr<my_boy> Level::auto_saved = nullptr;

Level::Level(my_boy& boy, int map_type)
: boy(boy), map(width, length, map_type){

    Background = new track();
    Background->play("Background.mp3");
    sounds.step->setVolume(30);
  
}

void Level::Level_setup()
{
    boy.x = start_pos_x;
    boy.y = start_pos_y;
}

Level::~Level()
{
    Background->stop();

    delete Background;
    delete River; 


    if (map_with_monsters) {
        int size = sizeof(map.forest) / sizeof(map.forest[0]);

        for (int i = 0; i < size; ++i) {
            delete[] map_with_monsters[i];
        }

        delete[] map_with_monsters;
    }
}

void Level::start()
{

    if (boy.need_to_setup) {

        boy.x = start_pos_x;
        boy.y = start_pos_y;
        boy.need_to_setup = false;
    }

    if (!auto_saved) {
        auto_saved = std::make_shared<my_boy>(boy); // Создаём новый shared_ptr, копируя boy
    }
    else {
        *auto_saved = boy; // Копируем данные из boy в auto_saved
    }
}

int Level::make_move(char** map) {

    static char last_input = 0;
    static auto last_time = std::chrono::steady_clock::now();

    timeout(300);
    char input = getch();

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count();

    if (input != ERR) {
        if (input == last_input && elapsed < 50) { // 200 ms задержка между повторными нажатиями
            return 1; // Игнорируем быстрое повторное нажатие
        }

        last_input = input;
        last_time = now;

        switch (input) {
        case 'w':
            if (0 < boy.y) {
                boy.y--;
                sounds.play(sounds.step);
                return 1;
            }
            break;
        case 's':
            if (boy.y < length - 1) {
                boy.y++;
                sounds.play(sounds.step);
                return 1;
            }
            break;
        case 'a':
            if (boy.x > 0) {
                boy.x--;
                sounds.play(sounds.step);
                return 1;
            }
            break;
        case 'd':
            if (boy.x < width - 1) {
                boy.x++;
                sounds.play(sounds.step);
                return 1;
            }
            break;

        case '1':
            if (boy.invent.size() > 0 && boy.invent[0].usage)
                do_something(0);
            return 0;
            break;

        case '2':
            if (boy.invent.size() > 0 && boy.invent[1].usage)
                do_something(1);
            return 0;
            break;
        case 'e':
            intface.show_invent(boy.invent);
            return 0;
            break;
        case 27:
            pause();
            return 0;
        }
    }
    else {
        last_input = 0; // Сбрасываем последнюю нажатую клавишу, если ничего не нажато
    }

    return 1;
}

int Level::make_move(char** map, int mx, int my) {

    bossx = mx;
    bossy = my;

    static char last_input = 0;
    static auto last_time = std::chrono::steady_clock::now();

    timeout(300);
    char input = getch();

    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_time).count();

    if (input != ERR) {
        if (input == last_input && elapsed < 50) { // 200 ms задержка между повторными нажатиями
            return 1; // Игнорируем быстрое повторное нажатие
        }

        last_input = input;
        last_time = now;

        switch (input) {
        case 'w':
            if (0 < boy.y) {
                boy.y--;
                sounds.play(sounds.step);
                return 1;
            }
            break;
        case 's':
            if (boy.y < length - 1) {
                boy.y++;
                sounds.play(sounds.step);
                return 1;
            }
            break;
        case 'a':
            if (boy.x > 0) {
                boy.x--;
                sounds.play(sounds.step);
                return 1;
            }
            break;
        case 'd':
            if (boy.x < width - 1) {
                boy.x++;
                sounds.play(sounds.step);
                return 1;
            }
            break;

        case '1':
            if (boy.invent.size() > 0 && boy.invent[0].usage)
                do_something(0);
            return 0;
            break;

        case '2':
            if (boy.invent.size() > 0 && boy.invent[1].usage)
                do_something(1);
            return 0;
            break;
        case 'e':
            intface.show_invent(boy.invent);
            return 0;
            break;
        case 27:
            pause();
            return 0;
        }
    }
    else {
        last_input = 0; // Сбрасываем последнюю нажатую клавишу, если ничего не нажато
    }

    return 1;
}

void Level::pause()
{
    int choice = intface.pause_menu();

    if (choice == 1) {

        file_tools ft;
        std::string path = intface.load_screen();

        if (path == "0")
            intface.pause_menu();
        try {
            number_of_loading = ft.load_boy(boy, path);
            download = true;
            exit_ = true; 
        }
        catch (const std::exception& e) {

        }
    }
     
    if (choice == 2 && !intface.are_you_sure_screen()) {
        exit_ = true;
    }
       
    
}

void Level::save_check()
{
    if (map.forest[boy.y][boy.x] == 'g') {

        file_tools ft;

        ft.save_boy(boy, intface.save_screen());
           
    }
}

void Level::dead()
{
    if (intface.game_over() == 0) {

        boy = *auto_saved;
        alived = true;
        boy.need_to_setup = true;
    }
   
    exit_ = true;
   
}

bool Level::notification(bool& flag, const char* row1, const char* row2, int score)
{
    if (flag == true) {
        intface.subs(row1, row2);
        nscore = score;
        sci++;
        if (sci >= subtimming * nscore) {
            flag = false;
            sci = 0;
        }
        return flag;
    }
}

bool Level::notification(bool &flag, const char* row1, const char* row2, int score, bool &nextbool)
{
    if (flag == true) {
        intface.subs(row1, row2);
        nscore = score;
        sci++;
        nextbool = true;
        if (sci >= subtimming * nscore) {
            flag = false;
            sci = 0;
        }
        return flag;
    }
}

void Level::buy(std::string for_sale, invent_thing need, int price)
{
    if (boy.get_thing_count(for_sale) >= price) {

        int count_of_for_sale = boy.get_thing_count(for_sale) % price;
        int count_of_need = boy.get_thing_count(for_sale) / price;

        boy.set_thing_count(for_sale, count_of_for_sale);
        boy.add_to_invent(need);
        boy.set_thing_count(need.name, count_of_need);

    }
    else return;

}

void Level::do_something(int num)
{
    switch (boy.invent[num].icon)
    {
    case 'o':
        map.forest[boy.y][boy.x] = 'o';
        boy.invent[num].count--;
        boy.check_invent_for_null(num);
        break;

    case '&':
        boy.hp = 10;
        boy.invent[num].count--;
        boy.check_invent_for_null(num);
        break;

    case '@':
        boy.invent[num].count--;
        break;

    case '}':
        fire();
        break;

    default:
        break;
    }
}

void Level::fire()
{
    timeout(-1);
    int first_key = 0;
    bool waiting_for_second = false;

    //while (true) {
    timeout(-1);

    int ch = getch(); // Получаем ввод

    if (ch != ERR) {  // Если клавиша нажата

        if (ch == 'w') {
            shoot_arrow(-1, 0);
        }
        else if (ch == 's') {
            shoot_arrow(1, 0);
        }
        else if (ch == 'a') {
            shoot_arrow(0, -1);
        }
        else if (ch == 'd') {
            shoot_arrow(0, 1);
        }
    }
}

void Level::shoot_arrow(int y, int x)
{
    int radius = 30;
    int count = 0;
    if (boss_enabled)
        copy_maps(1);
    copy_maps();
    badboys->make_map_with_monsters(map_with_monsters);

    int i = boy.y;
    int j = boy.x;

    while (true) {

        i += y;
        j += x;
        count++
            ;
        if (i >= 0 && i < length && j >= 0 && j < width
            && (map_with_monsters[i][j] == ' ' || map_with_monsters[i][j] == '1')
            && count <= radius) {

            ::move(i, j);

            if (map_with_monsters[i][j] == ' ') {
                attron(COLOR_PAIR(48));
                addch('-');
                attroff(COLOR_PAIR(48));
            }
            else {
                attron(COLOR_PAIR(49));
                addch('-');
                attroff(COLOR_PAIR(49));
            }
            refresh();
            continue;
        }
        if (i < 0 || i >= length || j < 0 || j >= width) {
            break;
        }
        else {
            if (map_with_monsters[i][j] == 'M')
                boss_beat = true;
            if (map_with_monsters[i][j] == 'W' || map_with_monsters[i][j] == 'I'
                || map_with_monsters[i][j] == 'o' || map_with_monsters[i][j] == 'Y') {
                badboys->kill_monster(i, j);
                break;
            }
            else {
                break;
            }
        }
    }
}

void Level::copy_maps() {

    map_with_monsters = new char* [length];

    for (int i = 0; i < length; ++i) {
        // Выделяем память для каждой строки
        map_with_monsters[i] = new char[width];

        // Копируем каждый символ
        for (int j = 0; j < width; ++j) {
            map_with_monsters[i][j] = map.forest[i][j];
        }
    }

    map_with_monsters[bossy][bossx] = 'M';
}

void Level::copy_maps(bool a) {

    map_with_monsters = new char* [length];

    for (int i = 0; i < length; ++i) {
        // Выделяем память для каждой строки
        map_with_monsters[i] = new char[width];

        // Копируем каждый символ
        for (int j = 0; j < width; ++j) {
            map_with_monsters[i][j] = map.forest[i][j];
        }
    }
}



