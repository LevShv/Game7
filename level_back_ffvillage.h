#pragma once

#include <level.h>

class level_back_ffvillage : public Level
{
public:

	level_back_ffvillage(my_boy& boy);
	~level_back_ffvillage() override;
	void start() override;
	void update() override;


private:

	monsters_family* badboys = nullptr;

	int count_of_three_monsters = 4;
	bool gotovil = true;
	bool iwasoldman1 = true;
	bool ireadom1 = true;

	void score_set() override;
	void draw() override;
	void moving() override;


};

