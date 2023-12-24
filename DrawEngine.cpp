#include "DrawEngine.h"

DrawEngine::DrawEngine() : color(RGB(0, 0, 255))
{
    createWindow();
    // 获得一个设备上下文用于绘图
    hdc = GetDC(hwnd);
}

DrawEngine::~DrawEngine()
{
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);
}

void DrawEngine::setColor(COLORREF c)
{
    color = c;
}

void DrawEngine::drawPixel(int x, int y)
{
    SetPixel(hdc, x, y, color);
}

void DrawEngine::createWindow()
{
    // 注册窗口类
    const char *CLASS_NAME = "DrawEngineWindowClass";

    // 窗口的属性
    WNDCLASS wc = {};
    // 处理窗口消息的函数
    wc.lpfnWndProc = WindowProc;
    // 获取当前执行的模块实例的句柄
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = CLASS_NAME;
    if (!RegisterClass(&wc))
    {
        MessageBoxW(nullptr, L"Failed to register window class", L"Error", MB_OK);
        exit(EXIT_FAILURE);
    }
    // 创建一个窗口
    hwnd = CreateWindowEx(
        0,//扩展样式
        CLASS_NAME,//窗口类名
        "Draw",// 窗口标题
        WS_SYSMENU | WS_MINIMIZEBOX,// 禁用最大化按钮，不能改变窗口大小
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, wc.hInstance, nullptr);

    if (!hwnd)
    {
        // 处理错误，例如通过弹出一个错误消息框
        MessageBoxW(nullptr, L"Failed to create window", L"Error", MB_OK);
        exit(EXIT_FAILURE);
    }

    ShowWindow(hwnd, SW_SHOW);
}


LRESULT DrawEngine::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        // 响应窗口销毁
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        // 处理绘图
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
