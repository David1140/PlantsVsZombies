#include "sunshine.hpp"
IMAGE imgSunshineBall[29];//Ì«ÑôÇò29Ö¡
int sunshine;
int sunshineTable[2] = { 100, 50 };
struct sunshineBall balls[10];
void collectSunshine(ExMessage* msg) {
    int count = sizeof(balls) / sizeof(balls[0]);
    int w = imgSunshineBall[0].getwidth();
    int h = imgSunshineBall[0].getheight();
    for (int i = 0; i < count; i++) {
        if (balls[i].used) {
            int x = balls[i].x;
            int y = balls[i].y;
            if (msg->x > x && msg->x < x + w && msg->y > y && msg->y < y + h) {
                balls[i].used = false;
                //sunshine += 25;
                mciSendString("play res/sunshine.mp3", 0, 0, 0);
                // ÉèÖÃ³õÊ¼Æ«ÒÆÁ¿
                float destX = 262;
                float destY = 0;
                float angle = atan((y - destY) / (x - destX));
                balls[i].xOff = 4 * cos(angle);
                balls[i].yOff = 4 * sin(angle);
            }
        }
    }
}
void createSunshine() {
    int ballMax = sizeof(balls) / sizeof(balls[0]);

    static int frameCount = 0;
    static int fre = 400;
    frameCount++;
    if (frameCount >= fre) {
        fre = 200 + rand() % 200;
        frameCount = 0;
        int i;
        for (i = 0; i < ballMax && balls[i].used; i++);
        if (i >= ballMax) return;

        balls[i].used = true;
        balls[i].frameIndex = 0;
        balls[i].x = 260 + rand() % (905 - 260);
        balls[i].y = 60;
        balls[i].destY = 180 + (rand() % 4) * 90 + 20;
        balls[i].timer = 0;
        balls[i].xOff = 0;
        balls[i].yOff = 0;
    }
}
void updateSunshine() {
    int ballMax = sizeof(balls) / sizeof(balls[0]);

    for (int i = 0; i < ballMax; i++) {
        if (balls[i].used) {
            balls[i].frameIndex = (balls[i].frameIndex + 1) % 29;
            if (balls[i].timer == 0) balls[i].y += 2;
            if (balls[i].y >= balls[i].destY) {
                balls[i].timer++;
                if (balls[i].timer > 100) balls[i].used = false;
            }
            
        }
        else if (balls[i].xOff) {
            float destX = 263;
            float destY = 0;
            float angle = atan((balls[i].y - destY) / (balls[i].x - destX));
            balls[i].xOff = 4 * cos(angle);
            balls[i].yOff = 4 * sin(angle);

            balls[i].x -= balls[i].xOff;
            balls[i].y -= balls[i].yOff;
            if (balls[i].y < 0 || balls[i].x < 262) {
                balls[i].xOff = 0;
                balls[i].yOff = 0;
                sunshine += 25;
            }
        }
    }
}