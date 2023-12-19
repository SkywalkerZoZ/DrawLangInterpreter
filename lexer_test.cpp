#include "Lexer.h"

int main()
{
	Token token;
	FILE *fp;
	Lexer lexer("test.txt");
	printf("�Ǻ�����    �ַ���     ����ֵ     ����ָ��\n");
	printf("------------------------------------------\n");
	while (true)
	{
        //��üǺ�
		token = lexer.getToken();
        //��ӡ�Ǻ�����
		if (token.type != NONTOKEN)
			printf("%4d,%12s,%12f,%12x\n", token.type, token.name.c_str(), token.value, token.math_func);
		else break;
	}
	printf("------------------------------------------\n");
}