#pragma once

class draw
{
protected:
	void Bckg(int start_row, int end_row, int start_col, int end_col, int color_pair);

	void cmvprintw(int y, int x, const char* text, int color_pair);

	void randomi(int& x, int& y);
};

