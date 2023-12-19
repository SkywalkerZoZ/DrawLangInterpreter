#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "Parser.h"
#include "DrawEngine.h"

class Interpreter
{
private:
    Parser &parser;
    DrawEngine &draw_eng;
    double &param;
    double origin_x;
    double origin_y;
    double scale_x;
    double scale_y;
    double rot_agl;
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
    void calCoord(const NodePtr &h,const NodePtr &v,double &x,double &y);
    void draw();
    void run();
};


#endif //INTERPRETER_H