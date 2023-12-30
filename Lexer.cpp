#include "Lexer.h"

#include <cstdlib>
#include <cctype>

Lexer::Lexer(const std::string& src_file)
{
	fp = fopen(src_file.c_str(), "r");
	if (fp == nullptr)
	{
		printf("open file %s failed\n", src_file.c_str());
		exit(EXIT_FAILURE);
	}
	lineNo = 1;
}
Lexer::~Lexer()
{
	if (fp != nullptr)
	{
		fclose(fp);
	}

}
char Lexer::getCh()
{
	char ch = getc(fp);
	return toupper(ch);
}
void Lexer::addBuf(char ch)
{
	buf.push_back(ch);
}
void Lexer::backCh(char ch)
{
	if (ch != EOF)
	{
		ungetc(ch, fp);
	}
}

Token Lexer::checkToken(std::string n) {
	// 时间复杂度O(1)
	auto it = token_tbl.find(n);
	if (it != token_tbl.end())
	{
		// 如果找到了，返回对应的Token
		return it->second;
	}
	else
	{
		// 如果没找到，返回默认ERRORTOKEN
		return Token();
	}
}

Token Lexer::getToken()
{
	//默认ERRORTOKEN
	Token token;
	char ch;
	// 清空记号缓冲区
	buf.clear();
	// 过滤空白字符
	for (;;) // 此循环用来过滤掉源程序中的空格、TAB、回车等分隔符，文件结束返回空记号
	{
		ch = getCh();
		if (ch == EOF)
		{
			// 文件结束返回空记号
			token.type = NONTOKEN;
			return token;
		}
		if (ch == '\n')
		{
			// 行号+1
			lineNo++;
		}
		if (!isspace(ch))
		{
			// 遇到空白字符则表明已经读完该记号
			break;
		}
	}
	// 加入缓冲区
	addBuf(ch);
	// 匹配 函数、关键字、PI、E
	if (isalpha(ch))
	{
		for (;;)
		{
			ch = getCh();
			if (isalnum(ch))
			{
				// 如果是字母或数字
				addBuf(ch);
			}
			else
				break;
		}
		// 退回非字母数字字符
		backCh(ch);
		// 判断是否在符号表中
		token = checkToken(buf);
		token.name = buf;
		return token;
	}
	else if (isdigit(ch))
	{
		// 数字开头，匹配常量
		for (;;)
		{
			// 转为大写
			ch = getCh();
			if (isdigit(ch))
				addBuf(ch);
			else
				break;
		}
		if (ch == '.')
		{
			addBuf(ch);
			for (;;)
			{
				ch = getCh();
				if (isdigit(ch))
					addBuf(ch);
				else
					break;
			}
		}
		backCh(ch);
		token.type = CONST_ID;
		token.value = atof(buf.c_str());
		token.name = buf;
		return token;
	}
	else
	{
		// 如果是其他符号
		switch (ch)
		{
		case ';':
			token.type = SEMICO;
			break;
		case '(':
			token.type = L_BRACKET;
			break;
		case ')':
			token.type = R_BRACKET;
			break;
		case ',':
			token.type = COMMA;
			break;
		case '+':
			token.type = PLUS;
			break;
		case '-':
			ch = getCh();
			if (ch == '-')
			{
				// 检查是否是双减号注释

				while (ch != '\n' && ch != EOF)
				{
					// 一直读到下一行的第一个字符并将其退回
					ch = getCh();
				}
				return getToken();
			}
			else
			{
				backCh(ch);
				token.type = MINUS;
				break;
			}
		case '/':
			ch = getCh();
			if (ch == '/')
			{
				// 检查是否是双斜杠注释
				while (ch != '\n' && ch != EOF)
				{
					// 一直读到下一行的第一个字符并将其退回
					ch = getCh();
				}
				return getToken();
			}
			else
			{
				backCh(ch);
				token.type = DIV;
				break;
			}
		case '*':
			ch = getCh();
			if (ch == '*')
			{
				// 匹配幂运算符
				token.type = POWER;
				break;
			}
			else
			{
				// 匹配乘号
				backCh(ch);
				token.type = MUL;
				break;
			}
		default:
			token.type = ERRTOKEN;
			break;
		}
	}
	token.name = buf;
	return token;
}
uint64_t Lexer::getLineNo() const
{
	return lineNo;
}