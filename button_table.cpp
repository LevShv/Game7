#include "button_table.h"

button_table::button_table(int start_x_pos, int end_x_pos, int start_y_pos, int height, int between, int color_, int color_press) :

	start_x_pos(start_x_pos), 
	end_x_pos(end_x_pos), 
	start_y_pos(start_y_pos), 
	height(height), 
	between(between), 
	color_(color_), 
	color_press(color_press)
{
}

void button_table::add(std::string label)
{
	button_coll.push_back(button(label));
}

int button_table::draw_nget(int button_save)
{	
	bool selected = false;
	int num = button_save;

	int count = button_coll.size();
	while (!selected) {

		draw_once(num);
		refresh();

		switch (getch()) {

		case 'w':
			num = (num - 1 + count) % count; //!
			break;

		case 's':
			num = (num + 1) % count;
			break;

		case 10:
			selected = true;
			break;

		case 27:
			return 0;

		default:
			break;
		}

	}
	
	return num;

}

void button_table::draw_once(int num)
{
	int bsy = start_y_pos;
	int count = button_coll.size();

	for (int i = 0; i < count; i++) {

		int startx_label_text = (end_x_pos + start_x_pos + 1) / 2 - (button_coll[i].label.size() + 1) / 2;
		Bckg(bsy, bsy + height, start_x_pos, end_x_pos, (num == i) ? color_press : color_);
		cmvprintw(bsy + 1, startx_label_text, button_coll[i].label.c_str(), (num == i) ? color_press : color_);
		bsy += between + height;

	}
}

button::button(std::string label) : label(label) {}

button::button(int number, std::string label, int start_x_pos, int end_x_pos, int start_y_pos, int end_col, int color_, int color_press) :

	number(number),
	label(label),
	start_row(start_x_pos),
	end_row(end_x_pos),
	start_col(start_y_pos),
	end_col(end_col),
	color_(color_),
	color_press(color_press)

{}

//void button::draw(int num)
//{
//	 Bckg(bsy, bsy + height, bsx, bex, (num == 0) ? color_pair(31) : color_pair(33));
//        cmvprintw(bsy + 1, 57, "новое", (num == 0) ? color_pair(31) : color_pair(33)); // 1
//}
