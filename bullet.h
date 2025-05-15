#pragma once
#include <graphics.h>
#include <vector>
#include "util.h"
using namespace std;

extern vector<IMAGE> arrow;
extern vector<IMAGE> spectral_arrow;
extern vector<IMAGE> firework;

const int plus_time = 15;

class bullet {
public:
    bullet(int x, int y, bool dir,int choose, int b_s_time);

    void move();
    void check();
    void draw();
    bool getdir();

    bool isPlusShot = false;
    int b_x;
    int b_y;
    int b_r = 5;
    int plus_b_r = 25;
    int bullet_speed = 30;
    bool bullet_dir;
private:
    int bullet_shot_time;
    int choose;

};

void shotbullet(int& x, int& y, bool& dir, int& choose ,int& bst,std::vector<bullet>& bullet_list);
void updatebullet(std::vector<bullet>& bullet_list);