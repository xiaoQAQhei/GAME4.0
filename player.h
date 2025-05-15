#pragma once
#include <graphics.h>
#include <vector>
#include <string>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include "bullet.h"
#include "rebound.h"
#include "util.h"
using namespace std;

extern const int GameW;
extern const int GameH;
const int PlayerHP = 20;
extern bool gameover;

extern vector<IMAGE> shadow;
extern vector<IMAGE> nut_run_left;
extern vector<IMAGE> nut_run_right;
extern vector<IMAGE> bow_pulling_left;
extern vector<IMAGE> bow_pulling_right;
extern vector<IMAGE> crossbow_pulling_left;
extern vector<IMAGE> crossbow_pulling_right;

extern IMAGE iron_door;
extern IMAGE signboard;
extern IMAGE P1;
extern IMAGE P2;

class bullet;
class rebound;

class player {
public:
    player(int x1, int y1, const int r1, std::wstring s1, int choose1, int player_idx);
    ~player();

    void loadAnimation(std::wstring s);
    void processdeal(ExMessage m);
    void Move();
    void Shot();
    void Rebound(player& enemy);
    void Hurt(player& enemy);
    void Live();
    void Counttimer();
    void Draw();
    void Reset();

    int x;
    int y;
    const int r = 35;
    int vy = 0;
    int vx = 0;
    int jumpfreq = 2;

    vector<bullet> bullet_list;

    rebound* reb = nullptr;

    int choose;
    int HP = 20; // PlayerHP
    const int location_r;
    bool isAboveGround = false;
    int shadow_idx = 0;
    int shadow_x = 0;
    int shadow_y = INT_MAX;
    int weaponState_idx = 0;
private:
    int temp_x, temp_y;
    int player_idx;
    const int speed = 3;
    const int maxSpeed = 10;
    const int PlusRepelSpeed = 50;
    const int repelamount = 30;
    const int jumpspeed = 30;

    int goldtimer = 0;

    std::vector<IMAGE> player_left;
    std::vector<IMAGE> player_right;
    IMAGE player_pic_idx;


    int current_idx = 0;
    int counter = 0;

    bool player_p = true;
    bool singlejump = true;

    bool jumpwalk = false;
    bool downwalk = false;
    bool rightwalk = false;
    bool leftwalk = false;

    int bullet_shot_timer = 0;

    bool single_b_s = false;
    bool single_reb = false;

    bool ifplusattack = false;

    bool isDeath = false;

    const int enter_player_cursor_delay = 100;
    int enter_player_cursor_timer = enter_player_cursor_delay;
};

void Show(player& p);