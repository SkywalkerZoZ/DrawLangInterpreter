#ifndef LEXER_H
#define LEXER_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cstdint>
#include <string>
#include <unordered_map>


#define FOREACH_TOKEN(TOKEN) \
        TOKEN(ORIGIN)   \
        TOKEN(SCALE)    \
        TOKEN(ROT)      \
        TOKEN(IS)       \
        TOKEN(TO)       \
        TOKEN(STEP)     \
        TOKEN(DRAW)     \
        TOKEN(FOR)      \
        TOKEN(FROM)     \
        TOKEN(T)        \
        TOKEN(SEMICO)   \
        TOKEN(L_BRACKET)\
        TOKEN(R_BRACKET)\
        TOKEN(COMMA)    \
        TOKEN(PLUS)     \
        TOKEN(MINUS)    \
        TOKEN(MUL)      \
        TOKEN(DIV)      \
        TOKEN(POWER)    \
        TOKEN(FUNC)     \
        TOKEN(CONST_ID) \
        TOKEN(NONTOKEN) \
        TOKEN(ERRTOKEN)
// 生成枚举
#define GENERATE_ENUM(ENUM) ENUM,
enum TokenType {
    FOREACH_TOKEN(GENERATE_ENUM)
};

// 生成枚举对应的string数组
#define GENERATE_STRING(STRING) #STRING,
static std::string token_name[] = {
    FOREACH_TOKEN(GENERATE_STRING)
};


using MathFuncPtr = double(*)(double);


struct Token {
    TokenType type;
    std::string name;
    double value;
    //属性，函数指针，代表一个指向返回double值并带有一个double形参的函数的指针的类型
    MathFuncPtr math_func;
    Token() : type(ERRTOKEN),name("ERRTOKEN") ,value(0.0), math_func(nullptr) {}
    Token(TokenType t,std::string n,double v,MathFuncPtr f) : type(t),name(n) ,value(v), math_func(f) {}
    Token& operator=(const Token& other) {
        //不定义赋值操作符则构造Token会出错
        if (this != &other) {
            type = other.type;
            name = other.name;
            value = other.value;
            math_func = other.math_func;
        }
        return *this;
    }
};


//符号表
static std::unordered_map<std::string, Token> token_tbl = {
    {"PI",     {CONST_ID, "PI",    3.1415926, nullptr}},
    {"E",      {CONST_ID, "E",     2.71828,   nullptr}},
    {"T",      {T,        "T",     0.0,       nullptr}},
    {"SIN",    {FUNC,     "SIN",   0.0,       std::sin}},
    {"COS",    {FUNC,     "COS",   0.0,       std::cos}},
    {"TAN",    {FUNC,     "TAN",   0.0,       std::tan}},
    {"LN",     {FUNC,     "LN",    0.0,       std::log}},
    {"EXP",    {FUNC,     "EXP",   0.0,       std::exp}},
    {"SQRT",   {FUNC,     "SQRT",  0.0,       std::sqrt}},
    {"ORIGIN", {ORIGIN,   "ORIGIN",0.0,       nullptr}},
    {"SCALE",  {SCALE,    "SCALE", 0.0,       nullptr}},
    {"ROT",    {ROT,      "ROT",   0.0,       nullptr}},
    {"IS",     {IS,       "IS",    0.0,       nullptr}},
    {"FOR",    {FOR,      "FOR",   0.0,       nullptr}},
    {"FROM",   {FROM,     "FROM",  0.0,       nullptr}},
    {"TO",     {TO,       "TO",    0.0,       nullptr}},
    {"STEP",   {STEP,     "STEP",  0.0,       nullptr}},
    {"DRAW",   {DRAW,     "DRAW",  0.0,       nullptr}}
};


class Lexer {
public:
    explicit Lexer(const std::string& src_file);
    ~Lexer();
    char getCh();

    void addBuf(char ch);
    void backCh(char ch);
    Token checkToken(std::string n);
    Token getToken();
    uint64_t getLineNo() const;
private:
    //行号
    uint64_t lineNo = 1;
    FILE *fp;
    std::string buf;

};

#endif // LEXER_H