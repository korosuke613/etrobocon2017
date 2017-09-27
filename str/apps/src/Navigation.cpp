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
    if(std::abs(current_x - goal_x) < 30.0){
        if(std::abs(current_y - goal_y) < 30.0){
            return true;
        }
    }
    return false;
}
void Navigation::calculate_line_angle(bool isBack){
    if(isBack == true){
        goal_angle = int(std::atan2(start_y - goal_y, start_x - goal_x)*180/3.14);        
    }else{
        goal_angle = int(std::atan2(goal_y - start_y, goal_x - start_x)*180/3.14);
    }
}

bool Navigation::calculateValue(std::int32_t left_degree, std::int32_t right_degree, bool isBack){
    int minus = 1;
    if(isBack == true)minus = -1;
    sl.update(left_degree, right_degree);
    diff_line = getDiffLine(sl.getPointX(), sl.getPointY()) * minus;
    forward = speedControl.calculateSpeedForPid(left_degree, right_degree);
    turn = turnControl.calculateTurnForPid(forward, diff_line);
    if(checkEndOfLine() == true){
        return false;
    }
    return true;
}

bool Navigation::calculateAngle(std::int32_t left_degree, std::int32_t right_degree, bool isBack){
    sl.update(left_degree, right_degree);
    sl.calculate_current_angle();
    forward = 0;
    if(goal_angle < sl.current_angle_degree )turn = -30;
    else turn = 30;
    if(goal_angle - 2 <= sl.current_angle_degree && goal_angle + 2 >= sl.current_angle_degree){
        return true;
    }
    return false;
}