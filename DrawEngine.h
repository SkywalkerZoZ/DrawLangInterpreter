#ifndef DRAWENGINE_H
#define DRAWENGINE_H

#include <Windows.h>
#include <cstdint>

//创建Windows窗口并向interpreter提供绘制接口
class DrawEngine {
public:
    DrawEngine();
    ~DrawEngine();
    void drawPixel(int x, int y, uint8_t size);
    void setColor(COLORREF c);
    void clearWindow();
private:
    // 绘制的窗口的句柄
    HWND hwnd;
    // 窗口的设备上下文
    HDC hdc;
    // 默认为黑色
    COLORREF color;
    void createWindow();
    // 处理窗口消息
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


#endif