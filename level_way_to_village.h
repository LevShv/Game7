#pragma once

#include <level.h>
class level_way_to_village : public Level 
{
public:
    
	level_way_to_village(my_boy& boy);
	~level_way_to_village() override;
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

};

