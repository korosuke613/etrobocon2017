#include "LeftNormalCourse.h"

LeftNormalCourse::LeftNormalCourse(){
    lineTracer.isLeftsideLine(true);
    status = old_status = LeftStatus::STRAIGHT;
}

bool LeftNormalCourse::runNormalCourse(){
    switch(status){
        case LeftStatus::STRAIGHT: 
            lineTracer.speedControl.setPid ( 2.0, 4.8, 0.024, 150.0 );
            lineTracer.turnControl.setPid ( 2.0, 1.0, 0.048, 40.0 );
            break;

        case LeftStatus::STRAIGHT_SLOW: 
            lineTracer.speedControl.setPid ( 2.0, 2.0, 0.024, 120.0 );
            lineTracer.turnControl.setPid ( 2.0, 1.0, 0.048, 40.0 );
            break;

        case LeftStatus::CURVE_RIGHT: 
            lineTracer.speedControl.setPid ( 4.0, 0.8, 0.08, 100.0 );
            lineTracer.turnControl.setPid ( 4.0, 2.0, 0.1, 35.0 );
            //lineTracer.turnControl.setPid ( 4.0, 2.0, 0.096, 40.0 );
            break;

        case LeftStatus::CURVE_LEFT_SHORT: 
            lineTracer.speedControl.setPid ( 4.0, 0.8, 0.1, 130.0 );
            lineTracer.turnControl.setPid ( 2.0, 0.5, 0.048, 35.0 );
            break;

        case LeftStatus::CURVE_LEFT: 
            lineTracer.speedControl.setPid ( 4.0, 0.8, 0.1, 100.0 );
            lineTracer.turnControl.setPid ( 4.0, 2.0, 0.096, 35.0 ); 
            break;

        case LeftStatus::STOP: stop(); break;
        default: stop();
    }
    if (status == LeftStatus::STOP) return false;
    return true;
}

bool LeftNormalCourse::statusCheck(int32_t countL, int32_t countR){
    distanse_total = distance.getDistanceTotal(countL, countR);
    old_status = status;
    if(distanse_total < 2740)status = LeftStatus::STRAIGHT;
    else if(distanse_total < 3240)status = LeftStatus::STRAIGHT_SLOW;
    else if(distanse_total < 5200)status = LeftStatus::CURVE_RIGHT;
    else if(distanse_total < 7500)status = LeftStatus::CURVE_LEFT_SHORT;
    else if(distanse_total < 11000)status = LeftStatus::CURVE_LEFT;
    else if(distanse_total < 12200)status = LeftStatus::CURVE_RIGHT;
    else if(distanse_total < 15500)status = LeftStatus::STRAIGHT;
    else status = LeftStatus::STOP;
    if(old_status != status) return true;
    return false;
}

int LeftNormalCourse::getStatus(){
    return (int)status;
}