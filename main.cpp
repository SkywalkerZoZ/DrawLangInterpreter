#include "Interpreter.h"

int main()
{
    Lexer lx("test.txt");
    Parser ps(lx);
    DrawEngine de;
    Interpreter itp(ps,de);
    itp.run();
    // 运行消息循环
    // hWnd为nullptr，表示获取所有线程的消息
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        //获取并分发系统消息
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
}