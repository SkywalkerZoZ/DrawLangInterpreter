#include "Parser.h"

double TNode::param = 0;  // ��̬��Ա��������

TokenType Parser::getTokenType() const
{
    return cur_token.type;
}


void Parser::fetch()
{
    cur_token = lexer.getToken();
    if(cur_token.type == ERRTOKEN)
    {
        error(ErrorType::INVALID_TOKEN);
    }
}

void Parser::match(TokenType expected)
{
    if(cur_token.type != expected)
    {
        error(ErrorType::NOT_EXP_TOKEN,expected);
    }
    //��ȡ��һ���Ǻ�
    fetch();
}
void Parser::error(ErrorType error_type,TokenType expected)
{
    switch (error_type)
    {
    case ErrorType::INVALID_TOKEN:
        printf("line %" PRIu64 ": invalid token %s\n", lexer.getLineNo(), cur_token.name.c_str());
        break;
    case ErrorType::NOT_EXP_TOKEN:
        printf("line %" PRIu64 ": not expected token %s, expected %s\n", lexer.getLineNo(), cur_token.name.c_str(),token_name[expected].c_str());
        break;
    default:
        break;
    }
    exit(EXIT_FAILURE);
}
NodePtr Parser::parseExpression()
{
    NodePtr left,right;
    left = parseTerm();
    TokenType tk_tmp;
    while(cur_token.type == PLUS || cur_token.type == MINUS)
    {
        //��¼��ǰ�Ǻţ���Ϊmatch��ı�cur_token
        tk_tmp=cur_token.type;
        match(tk_tmp);
        right = parseTerm();
        left = std::make_unique<BinOpNode>(tk_tmp,std::move(left), std::move(right));
    }
    return left;
}
NodePtr Parser::parseTerm()
{
    NodePtr left,right;
    left = parseFactor();
    TokenType tk_tmp;
    while(cur_token.type == MUL || cur_token.type == DIV)
    {
        tk_tmp=cur_token.type;
        match(tk_tmp);
        right = parseFactor();
        left = std::make_unique<BinOpNode>(tk_tmp,std::move(left), std::move(right));
    }
    return left;
}
NodePtr Parser::parseFactor()
{
    NodePtr left,right;
    if (cur_token.type == PLUS)
	{
        //ƥ��һԪ������
		match(PLUS);
		right = parseFactor();
	}
	else if (cur_token.type == MINUS)
	{
		// һԪ������
		// -2 = 0 - 2
		match(MINUS);
		right = parseFactor();
        left=std::make_unique<ConstNode>(0.0);
		right = std::make_unique<BinOpNode>(MINUS, std::move(left), std::move(right));
	}
	else
    {
        //ƥ����ս��Component
        right = parseComponent();
    }
	return right;
}
NodePtr Parser::parseComponent()
{
    NodePtr left,right;
    left=parseAtom();
    if(cur_token.type==POWER)
    {
        match(POWER);
        right=parseComponent();
        left=std::make_unique<BinOpNode>(POWER,std::move(left), std::move(right));
    }
    return left;
}
NodePtr Parser::parseAtom()
{
    NodePtr ad;
    //��¼��ǰ�Ǻ�
    Token tk_tmp=cur_token;
    switch (cur_token.type)
    {
    case CONST_ID:
        match(CONST_ID);
        ad=std::make_unique<ConstNode>(tk_tmp.value);
        break;
    case T:
        match(T);
        //TODO
        ad=std::make_unique<TNode>();
        break;
    case FUNC:
        match(FUNC);
        match(L_BRACKET);
        ad=parseExpression();
        ad=std::make_unique<FuncNode>(tk_tmp.math_func,std::move(ad));
        match(R_BRACKET);
        break;
    case L_BRACKET:
        match(L_BRACKET);
        ad=parseExpression();
        match(R_BRACKET);
        break;
    default:
        error(ErrorType::NOT_EXP_TOKEN);
        break;
    }
    return ad;
}