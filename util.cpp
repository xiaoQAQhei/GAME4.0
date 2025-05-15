#include"util.h"

void CollisionBoxDetction(player& p, const int& bx, const int& by, const int& bw, const int& bh) {    
    //иооб
    if (p.x <= bx + bw && p.x >= bx) {
        p.isAboveGround = true;

        if (p.y - p.r + p.vy <= by + bh && p.y > by) {
            p.vy = 0;
            p.y = by + bh + p.r;
        }
        else if (p.y + p.r + p.vy >= by && p.y < by) {
            p.vy = 0;
            p.y = by - p.r;
            p.jumpfreq = 2;
        }
    }
    //вСср
    if (p.y<by + bh && p.y>by && p.x + p.r > bx && p.x - p.r < bx + bw) {
        if (p.x - p.r < bx + bw && p.x>bx + bw) {
            p.x = bx + bw + p.r;
            p.jumpfreq = 2;
        }
        else if (p.x + p.r >= bx && p.x < bx) {
            p.x = bx - p.r;
            p.jumpfreq = 2;
        }
        p.vx = -p.vx;
    }

    if (p.isAboveGround) {
        if (p.jumpfreq == 2) {
            p.shadow_idx = 0;
            p.shadow_x = p.x - 24;
            p.shadow_y = abs(p.y-by)<abs(p.y-p.shadow_y)&&p.y<by&&p.x <= bx + bw && p.x >= bx ?by:p.shadow_y;
        }
        else {
            p.shadow_idx = 1;
            p.shadow_x = p.x - 16;
            p.shadow_y = abs(p.y - by) < abs(p.y - p.shadow_y) && p.y< by &&p.x <= bx + bw && p.x >= bx ? by : p.shadow_y;
        }
    }
}


    
 