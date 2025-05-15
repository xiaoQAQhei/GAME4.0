#pragma once

#include <graphics.h>
#include <string>
#include <memory>
#include"map.h"
using namespace std;

extern vector<IMAGE> shadow;

class Map1 : public Map {
public:
    Map1() = default;
    ~Map1() = default;

    void on_enter() {
        BeginBatchDraw();
        while (map1_enter_timer--) {
            cleardevice();
            unsigned char alpha = 255 * (map1_enter_delay - map1_enter_timer) / map1_enter_delay;
            Alpha_putimage(0, 0, GameMap, alpha);

            FlushBatchDraw();
        }
        EndBatchDraw();
        map1_enter_timer = map1_enter_delay;
        // 地图1特有的进入逻辑
    }

    void on_exit() {
        BeginBatchDraw();
        while (map1_exit_timer--) {
            cleardevice();
            unsigned char alpha = 255 * map1_exit_timer / map1_exit_delay;
            Alpha_putimage(0, 0, GameMap, alpha);

            FlushBatchDraw();
        }
        EndBatchDraw();
        map1_exit_timer = map1_exit_delay;
        // 地图1特有的退出逻辑
    }

    void Render() {
        Map::Render();
        // 地图1特有的渲染逻辑
    }

    void on_update(player& p) {
        // 地图1特有的更新逻辑
        //重力
        p.vy += g;

        //碰撞检测
        if (p.y + p.r + p.vy >= bottom && p.x > -50 && p.x < GameW + 50) {
            p.vy = 0;
            p.y = bottom - p.r;
            p.jumpfreq = 2;
            p.isAboveGround = true;
        }
        if (p.isAboveGround) {
            if (p.jumpfreq == 2) {
                p.shadow_idx = 0;
                p.shadow_x = p.x - 24;
            }
            else {
                p.shadow_idx = 1;
                p.shadow_x = p.x - 16;
            }
            Alpha_putimage(p.shadow_x, bottom, shadow[p.shadow_idx]);
        }

    }

private:
    IMAGE bgImg;
    // 地图1特有的成员
    const int g = 3;
    const int bottom = GameH / 2 + 15;

    const int map1_exit_delay = 100;
    int map1_exit_timer = map1_exit_delay;
    const int map1_enter_delay = 200;
    int map1_enter_timer = map1_enter_delay;
};