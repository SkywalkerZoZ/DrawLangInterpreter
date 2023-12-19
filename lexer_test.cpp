#include "Lexer.h"

int main()
{
	Token token;
	FILE *fp;
	Lexer lexer("test.txt");
	printf("记号类型    字符串     常数值     函数指针\n");
	printf("------------------------------------------\n");
	while (true)
	{
        //获得记号
		token = lexer.getToken();
        //打印记号内容
		if (token.type != NONTOKEN)
			printf("%4d,%12s,%12f,%12x\n", token.type, token.name.c_str(), token.value, token.math_func);
		else break;
	}
	printf("------------------------------------------\n");
}