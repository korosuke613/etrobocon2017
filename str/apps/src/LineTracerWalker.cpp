#include "LineTracerWalker.h"

LineTracerWalker::LineTracerWalker():
    minus(-1), forward(30), turn(0){
}

void LineTracerWalker::runLine(int32_t countL, int32_t countR, int8_t light_value){
    forward = speedControl.calculateSpeedForPid(countL, countR);
    turn = turnControl.calculateTurnForPid( forward, light_value ) * minus;
}

void LineTracerWalker::setForward(int8_t setValue){
    forward = setValue;
}

void LineTracerWalker::setTurn(int8_t setValue){
    turn = setValue;
}

int8_t LineTracerWalker::getForward(){
    return forward;
}

int8_t LineTracerWalker::getTurn(){
    return turn;
}

void LineTracerWalker::isLeftsideLine(bool b){
    // Trueのときは線の左側なので-1
    // Falseのときは線の右側なので+1
    minus = (b == true) ? -1 : 1;
}