#include "rebound.h"
#include "player.h"
#include "bullet.h"
#include "util.h"
#include <iostream>

class bullet;

void rebound::check(player& p, bullet& b) {
    if (isParrying) {
        if (parryWindow > 0) {
            parryWindow--;
            if (distance(b.b_x + 10, b.b_y, p.x, p.y) < b.plus_b_r + p.r) {
                p.reb->canParrying = true;
            }
        }
        else { parryWindow = 10; }
    }
}

void rebound::parryCooldown() {
    if (timer >= t && !isParrying) {
        isParrying = true;
        timer = 0;
    }
}

void rebound::bullet_rebound(bullet& b) {
    if (canParrying) {
        std::cout << "·´µ¯£¡" << std::endl;
        b.bullet_speed += 20;
        bool temp = b.bullet_dir;
        b.bullet_dir = temp ? false : true;
    }
}

void rebound::Reset() {
    isParrying = false;
    canParrying = false;
}