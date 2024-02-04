#ifndef __ZOMBIES_HPP__
#define __ZOMBIES_HPP__
#include <graphics.h>
#include "tools.h"

struct zm {
    int x, y;
    int frameIndex;
    bool used;
    int speed;
    int row; //0..2
    int blood;
    bool dead;
};
extern IMAGE imgZmDead[20];
extern struct zm zms[10];
extern IMAGE imgZM[22];
void createZM();
void updateZM();
void drawZM();
#endif // !1

