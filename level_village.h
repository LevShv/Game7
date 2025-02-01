#pragma once

#include <level.h>
#include <vector>
#include <set>

class level_village : public Level
{
public:

	level_village(my_boy& boy);
	~level_village() override;
	void start() override;
	void update() override;


private:


	std::vector<std::pair<int, int>> visited;
	int count_of_monsters = 4;
	int house_number = 5;
	int house_counter = 0;

	bool gotoborder = false;
	bool gotofind = true;
	bool ifound = false;
	bool ireadom1 = true;
	bool fornext = false;

	void score_set() override;
	void draw() override;
	void moving() override;
	bool check_box();
	bool last_place();
};

