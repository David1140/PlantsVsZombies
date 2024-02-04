#ifndef __BACKGROUND_HPP__
#define __BACKGROUND_HPP__
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define WIN_WIDTH    900
#define WIN_HEIGHT    600
extern IMAGE imgBg;//背景
class Windows_Screen {
	public:
		~Windows_Screen();
		static Windows_Screen& getScreen();
	private:
		Windows_Screen(); 
		Windows_Screen(const Windows_Screen&) = delete;
		//使用静态成员对象作为这个类的唯一实例(只要包含这个类,就能实例化一个对象)
		//静态成员在使用前必须进行初始化,且必须是在类外进行初始化
		static Windows_Screen screen;
		
		int Screen_width;
		int Screen_height;
		int debug_flag;
};

#endif // !__BACKGROUND_HPP__
