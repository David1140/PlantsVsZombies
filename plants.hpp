#ifndef __PLANTS_HPP__
#define __PLANTS_HPP__
#include <graphics.h>

enum { WAN_DOU, XIANG_RI_KUI, ZHI_WU_COUT };
struct zhiWu {
    int type;   // >=1  0:没有植物
    int frameIndex;
};
extern struct zhiWu  map[3][9];

extern IMAGE imgBar;//
extern IMAGE imgCards[ZHI_WU_COUT];//卡组
extern IMAGE* imgZhiWu[ZHI_WU_COUT][20];//植物类型（count*20帧）

class plants_IDcards {
    public:
        
    private:

};
void shoot();
void collisionCheck();
void updateBullets();
#endif // !__PLANTS_HPP__
