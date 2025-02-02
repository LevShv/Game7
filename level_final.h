#pragma once
#include <level.h>
#include <vector>
#include <set>
#include "final_boss.h"

class level_final : public Level
{
public:

	

	level_final(my_boy& boy);
	~level_final() override;
	void start() override;
	void update() override;


private:


	std::vector<std::pair<int, int>> visited;

	final_boss boss;

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
};


