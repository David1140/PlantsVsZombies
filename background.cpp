#include "background.hpp"
IMAGE imgBg;//����
Windows_Screen::Windows_Screen() :Screen_width(WIN_WIDTH), Screen_height(WIN_HEIGHT), debug_flag(1) {
    initgraph(Screen_width, Screen_height,debug_flag);
    loadimage(&imgBg, "res/bg.jpg");
    // �������壺
    LOGFONT f;
    gettextstyle(&f);                     // ��ȡ��ǰ��������
    f.lfHeight = 30;                      // ��������߶�Ϊ 48
    f.lfWidth = 15;
    strcpy(f.lfFaceName, "Segoe UI Black");//��������������Ϊ "Segoe UI Black"
    f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
    settextstyle(&f);                     // ����������ʽ
    setbkmode(TRANSPARENT);//����������ģʽ����Ϊ͸�����������Ƶ����ֱ�������͸����ʾ��
    setcolor(BLACK);

    mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
    /*mciSendString ������һ�� Windows API ���������ڷ��Ͷ�ý�������ѡ�Ĳ��� repeat����ʾ�ڲ��Ž������Զ��ظ����š���Ȼ����֧�ֵ����ֹ play����������������� stop, pause, resume �ȵȣ���
������������� 0, 0, 0 �ֱ��ʾ�ص��������ص����ھ���Լ�������Ϣ��������ָ�롣����������У���Щ����������Ϊ�� 0����ʾ��ʹ����Щ���ԡ�
�� Windows API ������ֻ���� Windows ƽ̨��ʹ�á������Ĵ����ǿ�ƽ̨�ģ�����ʹ����������Ƶ����߿����ʵ�����ƵĹ��ܡ�
*/
}
Windows_Screen:: ~Windows_Screen() {
    closegraph();
}
//�ṩһ���ܹ���ȡ���Ψһ��ʵ���Ľӿ�
Windows_Screen& Windows_Screen::getScreen()
{
    return screen;
}
Windows_Screen Windows_Screen::screen;