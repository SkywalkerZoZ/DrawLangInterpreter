#include "Lexer.h"

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
    auto it = token_tbl.find(n);
    if (it != token_tbl.end()) {
        // ����ҵ��ˣ����ض�Ӧ��Token
        return it->second;
    } 
	else
	{
        // ���û�ҵ�������Ĭ��ERRORTOKEN
        return Token();
    }
}

Token Lexer::getToken()
{
	//Ĭ��ERRORTOKEN
	Token token;
	char ch;
	// ��ռǺŻ�����
	buf.clear();
	// ���˿հ��ַ�
	for (;;) // ��ѭ���������˵�Դ�����еĿո�TAB���س��ȷָ������ļ��������ؿռǺ�
	{
		ch = getCh();
		if (ch == EOF)
		{
			// �ļ��������ؿռǺ�
			token.type = NONTOKEN;
			return token;
		}
		if (ch == '\n')
		{
			// �к�+1
			lineNo++;
		}
		if (!isspace(ch))
		{
			// �����հ��ַ�������Ѿ�����üǺ�
			break;
		}
	}
	// ���뻺����
	addBuf(ch);
	// ƥ�� �������ؼ��֡�PI��E
	if (isalpha(ch))
	{
		for (;;)
		{
			ch = getCh();
			if (isalnum(ch))
			{
				// �������ĸ������
				addBuf(ch);
			}
			else
				break;
		}
		// �˻ط���ĸ�����ַ�
		backCh(ch);
		// �ж��Ƿ��ڷ��ű���
		token = checkToken(buf);
		token.name = buf;
		return token;
	}
	else if (isdigit(ch))
	{
		// ���ֿ�ͷ��ƥ�䳣��
		for (;;)
		{
			// תΪ��д
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
		// �������������
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
				// ����Ƿ���˫����ע��

				while (ch != '\n' && ch != EOF)
				{
					// һֱ������һ�еĵ�һ���ַ��������˻�
					ch = getCh();
				}
				backCh(ch);
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
				// ����Ƿ���˫б��ע��
				while (ch != '\n' && ch != EOF)
				{
					// һֱ������һ�еĵ�һ���ַ��������˻�
					ch = getCh();
				}
				backCh(ch);
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
				// ƥ���������
				token.type = POWER;
				break;
			}
			else
			{
				// ƥ��˺�
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