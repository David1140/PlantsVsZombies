#include "zombies.hpp"
IMAGE imgZmDead[20];
struct zm zms[10];
IMAGE imgZM[22];
void createZM() {
    static int zmFre = 500;
    static int count = 0;
    count++;
    if (count > zmFre) {
        zmFre = rand() % 200 + 300;
        count = 0;

        int i;
        int zmMax = sizeof(zms) / sizeof(zms[0]);
        for (i = 0; i < zmMax && zms[i].used; i++);
        if (i < zmMax) {
            zms[i].used = true;
            zms[i].x = 900;
            zms[i].row = rand() % 3; // 0..2;
            zms[i].y = 180 + (1 + rand() % 3) * 100 - 8;
            zms[i].speed = 1;
            zms[i].blood = 100;
        }
    }
}

void updateZM() {
    int zmMax = sizeof(zms) / sizeof(zms[0]);

    static int count1 = 0;
    count1++;
    if (count1 > 2) {
        count1 = 0;
        for (int i = 0; i < zmMax; i++) {
            if (zms[i].used) {
                zms[i].x -= zms[i].speed;
                if (zms->x < 236 - 66) {
                    //printf("GAME OVER!\n");
                    MessageBox(NULL, "over", "over", 0); //TO DO
                    break;
                }
            }
        }
    }

    static int count2 = 0;
    count2++;
    if (count2 > 4) {//三次循环判断一次
        count2 = 0;
        for (int i = 0; i < zmMax; i++) {
            if (zms[i].used) {
                //判断是否已经死亡
                if (zms[i].dead) {
                    zms[i].frameIndex++;
                    if (zms[i].frameIndex >= 20) {
                        zms[i].used = false;
                    }
                }
                else {
                    zms[i].frameIndex = (zms[i].frameIndex + 1) % 22;
                }
            }
        }
    }
}

void drawZM() {
    int zmCount = sizeof(zms) / sizeof(zms[0]);
    for (int i = 0; i < zmCount; i++) {
        if (zms[i].used) {
            //选择对应的渲染图片
            IMAGE* img = (zms[i].dead) ? imgZmDead : imgZM;
            img += zms[i].frameIndex;

            int x = zms[i].x;
            int y = zms[i].y - img->getheight();
            putimagePNG(x, y, img);
        }
    }
}