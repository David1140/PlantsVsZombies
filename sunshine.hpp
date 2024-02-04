#ifndef __SUNSHINE_HPP__
#define __SUNSHINE_HPP__
#include <graphics.h>
#include <cmath>
#pragma once
extern IMAGE imgSunshineBall[29];//太阳球29帧
extern int sunshine;
extern int sunshineTable[2];

struct sunshineBall {
    int x, y;
    int frameIndex;
    bool used;
    int destY;
    int timer = 0;
    //添加以下两个成员
    float xOff;
    float yOff;
};
extern struct sunshineBall balls[10];
void collectSunshine(ExMessage* msg);
void createSunshine();
void updateSunshine();
#endif // !1
