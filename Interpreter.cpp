#include "Interpreter.h"


void Interpreter::interpProgram()
{
    //匹配程序内多个语句
    while(parser.getTokenType()!=NONTOKEN)
    {
        interpStatement();
        //匹配分隔符
        parser.match(SEMICO);
    }
}
void Interpreter::interpStatement()
{
    switch(parser.getTokenType())
    {
        case ORIGIN:
            interpOrigin();
            break;
        case SCALE:
            interpScale();
            break;
        case ROT:
            interpRot();
            break;
        case FOR:
            interpFor();
            break;
        default:
            parser.error(Parser::ErrorType::NOT_EXP_TOKEN);
            break;
    }
}
void Interpreter::interpOrigin()
{
    parser.match(ORIGIN);
    parser.match(IS);
    parser.match(L_BRACKET);
    origin_x=parser.parseExpression()->eval();
    parser.match(COMMA);
    origin_y=parser.parseExpression()->eval();
    parser.match(R_BRACKET);
}
void Interpreter::interpScale()
{
    parser.match(SCALE);
    parser.match(IS);
    parser.match(L_BRACKET);
    scale_x=parser.parseExpression()->eval();
    parser.match(COMMA);
    scale_y=parser.parseExpression()->eval();
    parser.match(R_BRACKET);
}
void Interpreter::interpRot()
{
    parser.match(ROT);
    parser.match(IS);
    rot_agl=parser.parseExpression()->eval();
}
void Interpreter::interpFor()
{
    parser.match(FOR);
    parser.match(T);
    parser.match(FROM);
    start=parser.parseExpression()->eval();
    parser.match(TO);
    end=parser.parseExpression()->eval();
    parser.match(STEP);
    step=parser.parseExpression()->eval();
    parser.match(DRAW);
    parser.match(L_BRACKET);
    draw_x=parser.parseExpression();
    parser.match(COMMA);
    draw_y=parser.parseExpression();
    parser.match(R_BRACKET);
    draw();
}

// 图形的变换顺序总是：比例变换 -> 旋转变换 -> 平移变换 
void Interpreter::calCoord(const NodePtr &h,const NodePtr &v,double &x,double &y)
{
    x=h->eval();
    y=v->eval();
    //比例变换
    x*=scale_x;
    y*=scale_y;
    //旋转变换
    double tmp_x=x;
    x=x*cos(rot_agl)+y*sin(rot_agl);
    y=y*cos(rot_agl)-tmp_x*sin(rot_agl);
    //平移变换
    x+=origin_x;
    y+=origin_y;
}

void Interpreter::draw()
{
    double x=0,y=0;
    for(param=start;param<=end;param+=step)
    {
        calCoord(draw_x,draw_y,x,y);
        // printf("%lf %lf\n",x,y);
        draw_eng.drawPixel(x,y);
    }
}

void Interpreter::run()
{
    parser.fetch();
    interpProgram();
}