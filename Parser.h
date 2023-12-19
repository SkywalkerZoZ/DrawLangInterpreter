#ifndef PARSER_H
#define PARSER_H

#include "Lexer.h"
#include <memory>
#include <cinttypes>

class ASTNode
{
public:
    virtual ~ASTNode() = default;
    // 纯虚函数，用于计算节点的值
    virtual double eval() const = 0;
};

using NodePtr = std::unique_ptr<ASTNode>;
class BinOpNode : public ASTNode
{
public:
    explicit BinOpNode(TokenType o, NodePtr l, NodePtr r)
        : left(std::move(l)), op(o), right(std::move(r)) {}
    double eval() const override
    {
        switch (op)
        {
        case PLUS:
            return left->eval() + right->eval();
        case MINUS:
            return left->eval() - right->eval();
        case MUL:
            return left->eval() * right->eval();
        case DIV:
            return left->eval() / right->eval();
        case POWER:
            return pow(left->eval(), right->eval());
        default:
            return 0.0;
        }
    }

private:
    TokenType op;
    NodePtr left;
    NodePtr right;
};

class ConstNode : public ASTNode
{
public:
    explicit ConstNode(double v) : val(v) {}
    double eval() const override
    {
        return val;
    }

private:
    double val;
};

class TNode : public ASTNode
{
public:
    static double param;
    double eval() const override
    {
        return param;
    }

};

class FuncNode : public ASTNode
{
public:
    FuncNode(MathFuncPtr f, NodePtr c) : func(f), child(std::move(c)) {}
    double eval() const override
    {
        return (*func)(child->eval());
    }

private:
    MathFuncPtr func;
    NodePtr child;
};

class Parser
{
private:
    Lexer &lexer;
    Token cur_token;
public:
    explicit Parser(Lexer &lex): lexer(lex){};
    enum class ErrorType
    {
        INVALID_TOKEN,
        NOT_EXP_TOKEN
    };
    TokenType getTokenType() const;
    // 通过词法分析器接口getToken获得一个记号
    void fetch();
    // 匹配当前记号
    void match(TokenType expected);
    void error(ErrorType error_type,TokenType expected=NONTOKEN);

    NodePtr parseExpression();
    NodePtr parseTerm();
    NodePtr parseFactor();
    NodePtr parseComponent();
    NodePtr parseAtom();
};
#endif // PARSER_H