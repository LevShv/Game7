#pragma once
class my_boy {

public:

    int x;
    int y;

    int hp = 10;
    int count_of_m = 1;
    my_boy(int spx, int spy);

    void move_boy(char** map);

private:

    int xl;
    int yl;
};

