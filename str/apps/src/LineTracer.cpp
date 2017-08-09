#include "LineTracer.h"

LineTracer::LineTracer():
     colorSensor(PORT_3), forward(30), turn(0), minus(-1){
}

void LineTracer::runLine(){
    turn = turnControl.calculateTurnForPid( forward, colorSensor.getBrightness() );
    if(forward < 0){
        walker.run(0, 0);
    }else{
        walker.run( forward, turn * minus);
    }
    tslp_tsk(4); // 4msec周期起動
}

void LineTracer::setForward(int8_t setValue){
    forward = setValue;
}

void LineTracer::setTurn(int8_t setValue){
    turn = setValue;
}

void LineTracer::isLeftsideLine(bool b){
    // Trueのときは線の左側なので-1
    // Falseのときは線の右側なので+1
    minus = (b == true) ? -1 : 1;
}