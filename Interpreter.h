#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Parser.h"
#include "DrawEngine.h"

// 将parser提供的语法分析树进行语义分析，并使用draw_eng进行绘制
class Interpreter
{
private:
    Parser &parser;
    DrawEngine &draw_eng;
    // T
    double &param;
    // ORIGIN IS ($origin_x, $origin_y); 
    double origin_x;
    double origin_y;
    // SCALE IS ($scale_x, $scale_y);
    double scale_x;
    double scale_y;
    // ROT IS $rot_agl;
    double rot_agl;
    // FOR T FROM $start TO $end STEP $step DRAW ($draw_x, $draw_y);
    double start;
    double end;
    double step;
    NodePtr draw_x;
    NodePtr draw_y;
public:
    explicit Interpreter(Parser &p,DrawEngine &de) 
    : parser(p),draw_eng(de), 
    param(TNode::param),origin_x(0),origin_y(0),scale_x(1),scale_y(1),
    rot_agl(0),start(0),end(0),step(0),draw_x(nullptr),draw_y(nullptr){}
    void interpProgram();
    void interpStatement();
    void interpOrigin();
    void interpScale();
    void interpRot();
    void interpFor();
    //根据计算坐标
    void calCoord(const NodePtr &h,const NodePtr &v,double &x,double &y);
    //根据计算的坐标使用draw_eng进行绘制
    void draw();
    //运行解释器
    void run();
};


#endif //INTERPRETER_H