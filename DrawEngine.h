#ifndef DRAWENGINE_H
#define DRAWENGINE_H

#include <Windows.h>
#include <tchar.h>
class DrawEngine {
public:
    DrawEngine();

    ~DrawEngine();

    void drawPixel(int x, int y);
    void setColor(COLORREF c);
private:
    // 绘制的窗口的句柄
    HWND hwnd;
    // 窗口的设备上下文
    HDC hdc;
    COLORREF color;
    void createWindow() ;

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


#endif