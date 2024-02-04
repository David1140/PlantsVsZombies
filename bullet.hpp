#ifndef __BULLET_HPP__
#define __BULLET_HPP__
#include <graphics.h>
#pragma once
struct bullet {
    int x, y;
    int row;
    bool used;
    int speed;
    bool blast;
    int frameIndex;
    int blastTime;
};
extern IMAGE imgBulletBlast[4];
extern struct bullet bullets[30];
extern IMAGE imgBulletNormal;

#endif // !__BULLET_HPP__
