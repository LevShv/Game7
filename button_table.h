
#include <string>
#include <vector>

#pragma once
class button {
public:

    int number;
    std::string label;
    button(std::string label);
    button(int number, std::string label, int start_x_pos, int end_x_pos, int start_y_pos, int height, int color_, int color_press);
    void draw(int num);

private:

    int start_row;
    int end_row;
    int start_col;
    int end_col;

    int color_;
    int color_press;
};
#include <curses.h>
class button_table
{
private:

    int start_x_pos = 44; // Начальная координата X
    int end_x_pos = 75; // Конечная координата X
    int start_y_pos = 7; // 

    int height = 2; // Высота кнопки
    int between = 3; // расстояние между кнопками

    int color_ = 0;
    int color_press = 0;

    std::vector<button> button_coll;

    void frame(int start_row, int end_row, int start_col, int end_col, int color_pair);
    void cmvprintw(int y, int x, const char* text, int color_pair);

public:

    button_table(int start_x_pos, int end_x_pos, int start_y_pos, 
        int height, int between, int color_, int color_press);

    void add(std::string label);
    int draw_nget(int button_save);
    void draw_once(int num);

};

