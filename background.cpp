#include "background.hpp"
IMAGE imgBg;//背景
Windows_Screen::Windows_Screen() :Screen_width(WIN_WIDTH), Screen_height(WIN_HEIGHT), debug_flag(1) {
    initgraph(Screen_width, Screen_height,debug_flag);
    loadimage(&imgBg, "res/bg.jpg");
    // 设置字体：
    LOGFONT f;
    gettextstyle(&f);                     // 获取当前字体设置
    f.lfHeight = 30;                      // 设置字体高度为 48
    f.lfWidth = 15;
    strcpy(f.lfFaceName, "Segoe UI Black");//将字体名称设置为 "Segoe UI Black"
    f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
    settextstyle(&f);                     // 设置字体样式
    setbkmode(TRANSPARENT);//将背景绘制模式设置为透明，这样绘制的文字背景将会透明显示。
    setcolor(BLACK);

    mciSendString("play res/bg.mp3 repeat", 0, 0, 0);
    /*mciSendString 函数是一个 Windows API 函数，用于发送多媒体命令。可选的参数 repeat，表示在播放结束后自动重复播放。当然，这支持的命令不止 play，还有其他命令（例如 stop, pause, resume 等等）。
后面的三个参数 0, 0, 0 分别表示回调函数、回调窗口句柄以及返回信息缓冲区的指针。在这个例子中，这些参数都设置为了 0，表示不使用这些特性。
个 Windows API 函数，只能在 Windows 平台上使用。如果你的代码是跨平台的，建议使用其他的音频库或者框架来实现类似的功能。
*/
}
Windows_Screen:: ~Windows_Screen() {
    closegraph();
}
//提供一个能够获取这个唯一的实例的接口
Windows_Screen& Windows_Screen::getScreen()
{
    return screen;
}
Windows_Screen Windows_Screen::screen;