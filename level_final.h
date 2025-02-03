#pragma once
#include <level.h>
#include <vector>
#include <set>
#include "final_boss.h"
#include <chrono>


class level_final : public Level
{
public:

	

	level_final(my_boy& boy);
	~level_final() override;
	void start() override;
	void update() override;


private:

	track* Aimbie;
	track* Happy;
         
	std::chrono::steady_clock::time_point start_time;

	std::vector<std::pair<int, int>> visited;

	final_boss boss;

	int count_of_monsters = 4;
	int house_number = 5;
	int house_counter = 0;

	bool killhim = true;
	bool win = false;
	bool gotoborder = false;
	bool killall = false;
	bool condition_met = false;
	bool ireadom1 = false;	
	bool fornext = false;
	bool happyplay = false;
	bool sadplay = false;

	void score_set() override;
	void draw() override;
	void moving() override;
};


