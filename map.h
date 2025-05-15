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
        // ��Ⱦ���ε�����Ԫ��
    }

    virtual void on_update(player& p) {
        // ��ͼ�����߼�
    }

    std::string GetName() const { return name; }

protected:
    std::string name;
    IMAGE* background;
    // ������ӵ������ݵ�������Ա

private:
};