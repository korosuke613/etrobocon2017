#include "LineTracer.h"

LineTracer::LineTracer():
     forward(30), turn(0), minus(-1){
}

void LineTracer::runLine(int32_t countL, int32_t countR, int8_t light_value){
    forward = speedControl.calculateSpeedForPid(countL, countR);
    turn = turnControl.calculateTurnForPid( forward, light_value ) * minus;
}

void LineTracer::setForward(int8_t setValue){
    forward = setValue;
}

void LineTracer::setTurn(int8_t setValue){
    turn = setValue;
}

int8_t LineTracer::getForward(){
    return forward;
}

int8_t LineTracer::getTurn(){
    return turn;
}

void LineTracer::isLeftsideLine(bool b){
    // Trueのときは線の左側なので-1
    // Falseのときは線の右側なので+1
    minus = (b == true) ? -1 : 1;
}