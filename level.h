#pragma once

#include "my_map.h"
#include "my_boy.h"
#include "iface.h"
#include "monsters_family.h"
#include <vector>

class Level {
protected:

    int width = 120;
    int length = 28;
    int start_pos_x = 59; //
    int start_pos_y = 21; //
    int subtimming = 10; // �������� ������ sub
    int game_iter; //  ��������

    my_boy boy; // ��������
    my_map map; // � ������������ ������ � ������������ � �������
    iface intface;
    std::vector<monster_type*> monsters;

public:

    Level(my_boy& boy, int map_type);
    virtual ~Level() = default;

    virtual void start() = 0; // ����� ����������� ������� ��� ������� ������
    virtual void update() = 0; // ����� ����������� ������� ��� ���������� ������

    int make_move(char** map);
};
