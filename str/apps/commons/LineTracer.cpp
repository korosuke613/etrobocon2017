#include "LineTracer.h"

LineTracer::LineTracer():
    forward(30), minus(-1){
}

void LineTracer::runLine(){
    turn = turnControl.calculateTurnForPid( forward );
    if(forward < 0){
        walker.run(0, 0);
    }else{
        walker.run( forward, turn * minus);
    }
    tslp_tsk(4); // 4msec周期起動
}

int32_t LineTracer::getCountL(){
    return walker.get_count_L();
}

int32_t LineTracer::getCountR(){
    return walker.get_count_R();
}


void LineTracer::setForward(int8_t setValue){
    forward = setValue;
}

void LineTracer::isLeftsideLine(bool b){
    // Trueのときは線の左側なので-1
    // Falseのときは線の右側なので+1
    minus = (b == true) ? -1 : 1;
}