#pragma once

#include <graphics.h>
#include <string>
#include "player.h"

extern IMAGE GameMap;

class Map {
public:
    Map() = default;
    ~Map() = default;

    virtual void on_enter() {}
    virtual void on_exit() {}

    virtual void Render() {
        putimage(0, 0, background);
        // 渲染地形等其他元素
    }

    virtual void on_update(player& p) {
        // 地图更新逻辑
    }

    std::string GetName() const { return name; }

protected:
    std::string name;
    IMAGE* background;
    // 可以添加地形数据等其他成员

private:
};