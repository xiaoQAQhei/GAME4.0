#pragma once

#include <graphics.h>
#include <string>
#include <memory>
#include "map.h"
#include "util.h"



class Map2 : public Map {
    friend void CollisionBoxDetction(player& p, const int& bx, const int& by, const int& bw, const int& bh);
public:
    Map2() = default;
    ~Map2() = default;

    void on_enter() {
        BeginBatchDraw();
        while (map2_enter_timer--) {
            cleardevice();
            unsigned char alpha = 255 * (map2_enter_delay - map2_enter_timer) / map2_enter_delay;
            Alpha_putimage(0, 0, GameMap, alpha);

            FlushBatchDraw();
        }
        EndBatchDraw();
        map2_enter_timer = map2_enter_delay;
        // 地图1特有的进入逻辑
    }

    void on_exit() {
        BeginBatchDraw();
        while (map2_exit_timer--) {
            cleardevice();
            unsigned char alpha = 255 * map2_exit_timer / map2_exit_delay;
            Alpha_putimage(0, 0, GameMap, alpha);

            FlushBatchDraw();
        }
        EndBatchDraw();
        map2_exit_timer = map2_exit_delay;
        // 地图1特有的退出逻辑
    }


    void Render() override {
        Map::Render();
        // 地图2特有的渲染逻辑
    }

    void on_update(player& p) {
        p.vy += map2_g;

        //bottom1
        //rectangle(bottom1_x, bottom1_y, bottom1_x + bottom1_w, bottom1_y + bottom1_h);
        CollisionBoxDetction(p, bottom1_x, bottom1_y, bottom1_w, bottom1_h);
        //bottom2_left
        //rectangle(bottom2_left_x, bottom2_left_y, bottom2_left_x + bottom2_left_w, bottom2_left_y + bottom2_left_h);
        CollisionBoxDetction(p, bottom2_left_x, bottom2_left_y, bottom2_left_w, bottom2_left_h);
        //bottom2_right
        //rectangle(bottom2_right_x, bottom2_right_y, bottom2_right_x + bottom2_right_w, bottom2_right_y + bottom2_right_h);
        CollisionBoxDetction(p, bottom2_right_x, bottom2_right_y, bottom2_right_w, bottom2_right_h);
        //bottom3
        //rectangle(bottom3_x, bottom3_y, bottom3_x + bottom3_w, bottom3_y + bottom3_h);
        CollisionBoxDetction(p, bottom3_x, bottom3_y, bottom3_w, bottom3_h);
        if (p.isAboveGround) {
            Alpha_putimage(p.shadow_x, p.shadow_y, shadow[p.shadow_idx]);
        }
        p.shadow_y =INT_MAX;
        // 地图2特有的更新逻辑
    }

private:
    IMAGE bgImg;
    // 地图2特有的成员
    const int map2_g = 3;
    const int bottom1_x = 455;
    const int bottom1_y = 695;
    const int bottom1_w = 690;
    const int bottom1_h = 63;

    const int bottom2_left_x = 274;
    const int bottom2_left_y = 550;
    const int bottom2_left_w = 203;
    const int bottom2_left_h = 63;

    const int bottom2_right_x = 1123;
    const int bottom2_right_y = 550;
    const int bottom2_right_w = 203;
    const int bottom2_right_h = 63;

    const int bottom3_x = 610;
    const int bottom3_y = 430;
    const int bottom3_w = 380;
    const int bottom3_h = 60;

    const int map2_exit_delay = 100;
    int map2_exit_timer = map2_exit_delay;
    const int map2_enter_delay = 200;
    int map2_enter_timer = map2_enter_delay;

};