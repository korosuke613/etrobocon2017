#include "Navigation.h"

Navigation::Navigation(std::int32_t left_degree, std::int32_t right_degree):
    sl(left_degree, right_degree, true){
    speedControl.setPid(2.0, 2.0, 0.024, 30.0);
    turnControl.setPid(4.0, 0.0, 0.0, 0.0);
    isLeftsideLine(true);
    setLine(0.0, 0.0, 100.0, 100.0);
    diff_line = sl.calculate_between_ev3_and_border(start_x, start_y, goal_x, goal_y, 0.0, 0.0);    
}

bool Navigation::setLine(float _start_x, float _start_y, float _goal_x, float _goal_y){
    if((_start_x == _goal_x) && (_start_y == _goal_y)){
        return false;
    }
    start_x = _start_x;
    start_y = _start_y;
    goal_x = _goal_x;
    goal_y = _goal_y;

    return true;
}

float Navigation::getDiffLine(float _current_x, float _current_y){
    current_x = _current_x;
    current_y = _current_y;
    return sl.calculate_between_ev3_and_border(start_x, start_y, goal_x, goal_y, current_x, current_y);
}

bool Navigation::checkEndOfLine(){
    if(std::abs(current_x - goal_x) < 20.0){
        if(std::abs(current_y - goal_y) < 20.0){
            return true;
        }
    }
    return false;
}

bool Navigation::calculateValue(std::int32_t left_degree, std::int32_t right_degree){
    sl.update(left_degree, right_degree);
    diff_line = getDiffLine(sl.getPointX(), sl.getPointY());
    forward = speedControl.calculateSpeedForPid(left_degree, right_degree);
    turn = turnControl.calculateTurnForPid(forward, diff_line);
    if(checkEndOfLine() == true){
        return false;
    }
    return true;
}