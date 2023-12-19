#include "DrawEngine.h"

// 默认为蓝色
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

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = CLASS_NAME;
    if (!RegisterClass(&wc))
    {
        MessageBoxW(nullptr, L"Failed to register window class", L"Error", MB_OK);
        exit(EXIT_FAILURE);
    }

    hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        // 窗口标题
        "Draw绘图解释",
        // 禁用最大化按钮，不能改变窗口大小
        WS_SYSMENU | WS_MINIMIZEBOX,
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

// 用于处理窗口的消息
// 处理 WM_DESTROY 消息来响应窗口销毁
// 处理WM_PAINT 消息来处理绘图请求
// 处理其他未处理的消息将由 DefWindowProc 函数处理
LRESULT DrawEngine::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        // 可以在这里处理绘图
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
