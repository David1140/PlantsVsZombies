#include "PlantsVsZombies_EasyX_main.hpp"

void gameInit() {
    
    loadimage(&imgBar, "res/bar5.png");
    loadimage(&imgBulletNormal, "res/bullets/bullet_normal.png");
    sunshine = 150;
    curZhiWu = 0;
    memset(imgZhiWu, 0, sizeof(imgZhiWu));
    memset(map, 0, sizeof(map));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
    memset(bullets, 0, sizeof(bullets));
    char name[64];
    for (int i = 0; i < ZHI_WU_COUT; i++) {
        sprintf_s(name, sizeof(name), "res/Cards/card_%d.png", i + 1);
        loadimage(&imgCards[i], name);

        for (int j = 0; j < 20; j++) {
            sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.png", i, j + 1);
            imgZhiWu[i][j] = new IMAGE;
            loadimage(imgZhiWu[i][j], name);
            if (imgZhiWu[i][j]->getwidth() == 0) {
                delete imgZhiWu[i][j];
                imgZhiWu[i][j] = NULL;
            }
        }
    }
    loadimage(&imgBulletBlast[3], "res/bullets/bullet_blast.png");
    for (int i = 0; i < 3; i++) {
        float k = (i + 1) * 0.2;
        loadimage(&imgBulletBlast[i], "res/bullets/bullet_blast.png",
            imgBulletBlast[3].getwidth() * k,
            imgBulletBlast[3].getheight() * k, true);
    }
    memset(balls, 0, sizeof(balls));
    for (int i = 0; i < 29; i++) {
        sprintf_s(name, sizeof(name), "res/sunshine/%d.png", i + 1);
        loadimage(&imgSunshineBall[i], name);
    }

    memset(zms, 0, sizeof(zms));
    srand(time(NULL));
    for (int i = 0; i < 20; i++) {
        sprintf_s(name, sizeof(name), "res/zm_dead/%d.png", i + 1);
        loadimage(&imgZmDead[i], name);
    }
    for (int i = 0; i < 22; i++) {
        sprintf_s(name, sizeof(name), "res/zm/%d.png", i + 1);
        loadimage(&imgZM[i], name);
    }
   
}


void updateWindow() {
    BeginBatchDraw();
    
    putimage(0, 0, &imgBg);//绘制地图
    putimagePNG(250, 0, &imgBar);//放置卡片槽

    for (int i = 0; i < ZHI_WU_COUT; i++) {//植物卡片
        int x = 338 + i * 64;
        int y = 6;
        putimage(x, y, &imgCards[i]);
    }

    if (curZhiWu > 0) {  // 绘制正在移动的植物
        IMAGE* img = imgZhiWu[curZhiWu - 1][0];
        putimagePNG(curX - img->getwidth() * 0.5, curY - img->getheight() * 0.5, img);
    }
    //绘制3*9个格子里保存的东西
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 9; j++) {
            if (map[i][j].type > 0) {
                int x = 260 + j * 81.6;    // (msg.x - 260) / 81.6;
                int y = 180 + i * 103.6 + 14; // (msg.y - 210) / 103.6;
                int zhiWuIndex = map[i][j].type;
                int frameIndex = map[i][j].frameIndex;
                putimagePNG(x, y, imgZhiWu[zhiWuIndex - 1][frameIndex]);
            }
        }
    }

    drawZM(); 
    int ballMax = sizeof(balls) / sizeof(balls[0]);
    for (int i = 0; i < ballMax; i++) {
        if (balls[i].used|| balls[i].xOff
            ) { //添加这个条件
            IMAGE* img = &imgSunshineBall[balls[i].frameIndex];
             putimagePNG(balls[i].x, balls[i].y, img);
        }
    }
   

    int bulletMax = sizeof(bullets) / sizeof(bullets[0]);
    for (int i = 0; i < bulletMax; i++) {
        if (bullets[i].used) {
            if (bullets[i].blast) {
                IMAGE* img = &imgBulletBlast[bullets[i].blastTime];
                int x = bullets[i].x + 12 - img->getwidth() / 2;
                int y = bullets[i].y + 12 - img->getheight() / 2;
                putimagePNG(x, y, img);

                /*bullets[i].used = false;*/
            }
            else {
                putimagePNG(bullets[i].x, bullets[i].y, &imgBulletNormal);
            }

        }
    }
    char scoreText[8];
    sprintf_s(scoreText, sizeof(scoreText), "%d", sunshine);
    outtextxy(282 - 10 + 4, 50 + 15 + 2, scoreText);//EasyX 绘图库中用于输出文本
    EndBatchDraw();
}

void userClick() {
    ExMessage msg;
    static int status = 0;
    if (peekmessage(&msg)) {
        if (msg.message == WM_LBUTTONDOWN) {
            if (msg.x > 338 && msg.x < 338 + 64 * ZHI_WU_COUT && msg.y>6 && msg.y < 96) {
                int index = (msg.x - 338) / 64;
                printf("%d\n", index);
                status = 1;
                curZhiWu = index + 1; // 1， 2 
                curX = msg.x;
                curY = msg.y;
            }
            else { collectSunshine(&msg); }
        }
        else if (msg.message == WM_MOUSEMOVE && status == 1) {
            curX = msg.x;
            curY = msg.y;
        }
        else if (msg.message == WM_LBUTTONUP && status == 1) {
            //printf("up\n");
            if (msg.x > 260 && msg.y < 995 && msg.y > 180 && msg.y < 491) {
                if (sunshine >= sunshineTable[curZhiWu - 1]) {
                    sunshine -= sunshineTable[curZhiWu - 1];
                    int col = (msg.x - 260) / 81.6;
                    int row = (msg.y - 210) / 103.6;
                    printf("[%d,%d]\n", row, col);
                    if (map[row][col].type == 0) {
                        map[row][col].type = curZhiWu;
                        map[row][col].frameIndex = 0;
                    }
                }
            }
            status = 0;
            curZhiWu = 0;
        }
    }
}

void updateGame() {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 9; j++) {
            if (map[i][j].type > 0) {
                map[i][j].frameIndex++;
                if (imgZhiWu[map[i][j].type - 1][map[i][j].frameIndex] == NULL) {
                    map[i][j].frameIndex = 0;
                }
            }
        }
    }
    createSunshine();
    updateSunshine();

    createZM();
    updateZM();

    shoot();
    updateBullets();

    collisionCheck();
}

void startUI() {
    IMAGE imgBg, imgMenu1, imgMenu2;
    loadimage(&imgBg, "res/menu.png");
    loadimage(&imgMenu1, "res/menu1.png");
    loadimage(&imgMenu2, "res/menu2.png");
    int flag = 0;
    while (1) {
        BeginBatchDraw();
        putimage(0, 0, &imgBg);
        putimagePNG(474, 75, flag ? &imgMenu2 : &imgMenu1);

        ExMessage msg;
        if (peekmessage(&msg)) {
            if (msg.message == WM_LBUTTONDOWN &&
                msg.x > 474 && msg.x < 474 + 300 && msg.y > 75 && msg.y < 75 + 140) {
                flag = 1;
                EndBatchDraw();
            }
            else if (msg.message == WM_LBUTTONUP && flag) {
                return;
            }
        }
        EndBatchDraw();
    }
}
int main(void) {
    gameInit();
    //startUI();
    int timer = 0;
    bool flag = true;
 
    while (1) {
        userClick();
        timer += getDelay();
        if (timer > 20) {
            timer = 0;
            flag = true;
        }
        if (flag) {
            flag = false;
            updateWindow();
            updateGame();
        }
    }
        

    return 0;
}
