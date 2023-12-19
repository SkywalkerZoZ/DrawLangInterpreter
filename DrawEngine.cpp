#include "DrawEngine.h"

// Ĭ��Ϊ��ɫ
DrawEngine::DrawEngine() : color(RGB(0, 0, 255))
{
    createWindow();
    // ���һ���豸���������ڻ�ͼ
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
    // ע�ᴰ����
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
        // ���ڱ���
        "Draw��ͼ����",
        // ������󻯰�ť�����ܸı䴰�ڴ�С
        WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, wc.hInstance, nullptr);

    if (!hwnd)
    {
        // �����������ͨ������һ��������Ϣ��
        MessageBoxW(nullptr, L"Failed to create window", L"Error", MB_OK);
        exit(EXIT_FAILURE);
    }

    ShowWindow(hwnd, SW_SHOW);
}

// ���ڴ����ڵ���Ϣ
// ���� WM_DESTROY ��Ϣ����Ӧ��������
// ����WM_PAINT ��Ϣ�������ͼ����
// ��������δ�������Ϣ���� DefWindowProc ��������
LRESULT DrawEngine::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        // ���������ﴦ���ͼ
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
