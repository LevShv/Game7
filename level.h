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

    int nscore = 0; // ����� ����
    int sci = 0; // ������� �������� 

    my_boy& boy; // ��������
    my_map map; // �������� ���
    iface intface; 
    std::vector<monster_type*>* monsters;

    virtual void score_set() = 0; // 
    virtual void draw() = 0;
    //virtual void 
    int make_move(char** map);


public:

    Level(my_boy& boy, int map_type);
    virtual ~Level() = default;

    virtual void start() = 0; // ����� ����������� ������� ��� ������� ������
    virtual void update() = 0; // ����� ����������� ������� ��� ���������� ������

};
