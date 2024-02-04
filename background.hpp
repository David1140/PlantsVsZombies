#ifndef __BACKGROUND_HPP__
#define __BACKGROUND_HPP__
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define WIN_WIDTH    900
#define WIN_HEIGHT    600
extern IMAGE imgBg;//����
class Windows_Screen {
	public:
		~Windows_Screen();
		static Windows_Screen& getScreen();
	private:
		Windows_Screen(); 
		Windows_Screen(const Windows_Screen&) = delete;
		//ʹ�þ�̬��Ա������Ϊ������Ψһʵ��(ֻҪ���������,����ʵ����һ������)
		//��̬��Ա��ʹ��ǰ������г�ʼ��,�ұ�������������г�ʼ��
		static Windows_Screen screen;
		
		int Screen_width;
		int Screen_height;
		int debug_flag;
};

#endif // !__BACKGROUND_HPP__
