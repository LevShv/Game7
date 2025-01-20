#pragma once

#include <level.h>

class level_village : public Level
{
public:

	level_village(my_boy& boy);

	void start() override;
	void update() override;


private:

	void score_set() override;
	void draw() override;
};

