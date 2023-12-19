#include "Interpreter.h"

int main()
{
    Lexer lx("test.txt");
    Parser ps(lx);
    DrawEngine de;
    // ��ɫ
    de.setColor(RGB(0, 0, 0));
    Interpreter itp(ps,de);
    itp.run();
    // ������Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
}