#pragma once
#include "bullet.h"

class player; // Ç°ÏòÉùÃ÷
class bullet;

class rebound {
public:
    void check(player& p, bullet& b);
    void parryCooldown();
    void bullet_rebound(bullet& b);
    void Reset();

    bool isParrying = false;
    bool canParrying = false;
    int parryDuration = 10;
    int timer = t;
    const int t = 3;

private:
    int parryWindow = 10;
};