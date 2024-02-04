#include "plants.hpp"
#include "zombies.hpp"
#include "bullet.hpp"
struct zhiWu  map[3][9];

IMAGE imgBar;//
IMAGE imgCards[ZHI_WU_COUT];//卡组
IMAGE* imgZhiWu[ZHI_WU_COUT][20];//植物类型（count*20帧）
void shoot() {
    int zmCount = sizeof(zms) / sizeof(zms[0]);
    int directions[3] = { 0 };
    int dangerX = 900 - imgZM[0].getwidth();
    for (int i = 0; i < zmCount; i++) {
        if (zms[i].used && zms[i].x < dangerX) {
            directions[zms[i].row] = 1;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 9; j++) {
            if (map[i][j].type == WAN_DOU + 1 && directions[i]) {
                static int count = 0;
                count++;
                if (count > 20) {
                    count = 0;
                    int k;
                    int maxCount = sizeof(bullets) / sizeof(bullets[0]);
                    for (k = 0; k < maxCount && bullets[k].used; k++);
                    if (k < maxCount) {
                        bullets[k].row = i;
                        bullets[k].speed = 4;
                        bullets[k].used = true;
                        bullets[k].blast = false;
                        bullets[k].blastTime = 0;
                        int zwX = 260 + j * 81.6;    // (msg.x - 260) / 81.6;
                        int zwY = 180 + i * 103.6 + 14; // (msg.y - 210) / 103.6;

                        bullets[k].x = zwX + imgZhiWu[map[i][j].type - 1][0]->getwidth() - 10;
                        bullets[k].y = zwY + 5;
                    }
                }
            }
        }
    }
}

void collisionCheck() {
    int bCount = sizeof(bullets) / sizeof(bullets[0]);
    int zCount = sizeof(zms) / sizeof(zms[0]);
    for (int i = 0; i < bCount; i++) {
        if (bullets[i].used == false || bullets[i].blast)continue;
        for (int k = 0; k < zCount; k++) {
            int x1 = zms[k].x + 80;
            int x2 = zms[k].x + 110;
            if (zms[k].dead == false &&  //添加这个条件
                bullets[i].row == zms[k].row && bullets[i].x > x1 && bullets[i].x < x2) {
                zms[k].blood -= 20;
                bullets[i].blast = true;
                bullets[i].speed = 0;

                //对血量进行检测
                if (zms[k].blood <= 0) {
                    zms[k].dead = true;
                    zms[k].speed = 0;
                    zms[k].frameIndex = 0;
                }
                break;
            }
        }
    }
}
void updateBullets() {
    int countMax = sizeof(bullets) / sizeof(bullets[0]);
    for (int i = 0; i < countMax; i++) {
        if (bullets[i].used) {
            bullets[i].x += bullets[i].speed;
            if (bullets[i].x > 900) {//WIN_WIDTH
                bullets[i].used = false;
            }

            if (bullets[i].blast) {
                bullets[i].blastTime++;
                if (bullets[i].blastTime >= 4) {
                    bullets[i].used = false;
                }
            }
        }
    }
}
