#include "draw.h"
#include <curses.h>
#include <random>

void draw::cmvprintw(int y, int x, const char* text, int color_pair)
{
    attron(color_pair);
    mvprintw(y, x, text);
    attroff(color_pair);

}

void draw::Bckg(int start_row, int end_row, int start_col, int end_col, int color_pair) {
    attron(color_pair);

    for (int row = start_row; row <= end_row; row++) {
        for (int col = start_col; col <= end_col; col++) {
            mvprintw(row, col, " ");
        }
    }

    attroff(color_pair);
}
void draw::randomi(int& x, int& y)
{

    std::random_device rd;  // Используется для получения начального значения (seed)
    std::mt19937 gen(rd()); // Генератор случайных чисел (Mersenne Twister)

    std::uniform_int_distribution<> disx(1, 29 - 1); // Равномерное распределение от 0 до 
    std::uniform_int_distribution<> disy(1, 120 - 1);

    y = disy(gen);
    x = disx(gen);
}

