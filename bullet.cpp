#include "bullet.h"

#include<algorithm>
#include<cmath>

extern vector<IMAGE> arrow;
extern vector<IMAGE> spectral_arrow;
extern vector<IMAGE> firework;

bullet::bullet(int x, int y, bool dir,int choose ,int b_s_time)
    : b_x(x), b_y(y), bullet_shot_time(b_s_time), bullet_dir(dir) ,choose(choose){
}

void bullet::move() {
    if (bullet_dir) {
        b_x -= bullet_speed;
    }
    else {
        b_x += bullet_speed;
    }
}

void bullet::check() {
    if (bullet_shot_time < 20) { // plus_time
        isPlusShot = false;
    }
    else { isPlusShot = true; }
}

void bullet::draw() {
    if (isPlusShot) {
        if (choose == 1) {
            Alpha_putimage(b_x, b_y-60, spectral_arrow[!bullet_dir]);
        }else if (choose == 2) {
            Alpha_putimage(b_x, b_y-60, firework[!bullet_dir]);
        }
    }
    else {
        Alpha_putimage(b_x, b_y-30, arrow[!bullet_dir]);
    }
}

bool bullet::getdir() {
    return bullet_dir;
}

void shotbullet(int& x, int& y, bool& dir,int& choose, int& bst, std::vector<bullet>& bullet_list) {
    bullet b(x, y, dir,choose, bst);
    bullet_list.push_back(b);
}

void updatebullet(std::vector<bullet>& bullet_list) {
    for (size_t i = 0; i < bullet_list.size(); i++) {
        if (bullet_list[i].b_x < -100 || bullet_list[i].b_x > GameW+100) { // GameW
            swap(bullet_list[i], bullet_list.back());
            bullet_list.pop_back();
            continue;
        }
        bullet_list[i].move();
        bullet_list[i].check();
        bullet_list[i].draw();
    }
}