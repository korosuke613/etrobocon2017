/**
 * @file RightNormalCourse.cpp
 * @brief RightNormalCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "RightNormalCourse.h"

RightNormalCourse::RightNormalCourse(){
    lineTracerWalker.isLeftsideLine(false);
    status = old_status = RightStatus::STRAIGHT;
}

bool RightNormalCourse::runNormalCourse(){
    switch(status){
        case RightStatus::STRAIGHT:
            lineTracerWalker.speedControl.setPid ( 2.0, 4.8, 0.024, 150.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 1.0, 0.048, 40.0 );
            break;
        
        case RightStatus::CURVE_RIGHT:
            lineTracerWalker.speedControl.setPid ( 2.0, 4.8, 0.024, 150.0 );
            lineTracerWalker.turnControl.setPid ( 4.0, 2.0, 0.09, 40.0 );
            //lineTracerWalker.turnControl.setPid ( 4.0, 2.0, 0.096, 40.0 );
            break;

        case RightStatus::CURVE_LEFT_SHORT: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.1, 130.0 );
            lineTracerWalker.turnControl.setPid ( 2.0, 0.5, 0.048, 35.0 );
            break;

        case RightStatus::CURVE_LEFT: 
            lineTracerWalker.speedControl.setPid ( 4.0, 0.8, 0.1, 100.0 );
            lineTracerWalker.turnControl.setPid ( 4.0, 2.0, 0.096, 35.0 );
            break;
            
        case RightStatus::STOP: stop(); break;
        default: stop();
    }
    if (status == RightStatus::STOP) return false;
    return true;
}

bool RightNormalCourse::statusCheck(int32_t countL, int32_t countR){
    distanse_total = distance.getDistanceTotal(countL, countR);
    old_status = status;
    if(distanse_total < 3240)status = RightStatus::STRAIGHT;
    else if(distanse_total < 7500)status = RightStatus::CURVE_RIGHT;
    else if(distanse_total < 9200)status = RightStatus::CURVE_LEFT_SHORT;
    else if(distanse_total < 10800)status = RightStatus::CURVE_LEFT;
    else if(distanse_total < 12800)status = RightStatus::CURVE_RIGHT;
    else if(distanse_total < 16000)status = RightStatus::STRAIGHT;
    else status = RightStatus::STOP;
    if(old_status != status) return true;
    return false;
}

int RightNormalCourse::getStatus(){
    return (int)status;
}