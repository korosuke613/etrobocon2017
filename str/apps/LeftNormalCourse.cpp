#include "LeftNormalCourse.h"

LeftNormalCourse::LeftNormalCourse(){
    lineTracer.isLeftsideLine(false);
}

void LeftNormalCourse::runNormalCourse(void){
	while ( 1 ) {
        current_speed = lineTracer.speedControl.calculateSpeedForPid();
        statusCheck();
		switch(status){
            case Status::STRAIGHT: goStraight(current_speed); break;
            case Status::CURVE_RIGHT: goCurveRight(current_speed); break;

            default: goStraight(0);
        }
		lineTracer.runLine();
		if (ev3_button_is_pressed(BACK_BUTTON)) break;
	}
}

void LeftNormalCourse::statusCheck(){
    distanse_total = distance.getDistanceTotal();
    if(distanse_total < 3240)status = Status::STRAIGHT;
    else if(distanse_total < 10000)status = Status::CURVE_RIGHT;
    else if(distanse_total < 12000)status = Status::STRAIGHT;
    else status = Status::STRAIGHT;
}

void LeftNormalCourse::goStraight(int32_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.turnControl.changePidGain ( 0.5, 0.5, 0.012, 45.0 );
}

void LeftNormalCourse::goCurveRight(int32_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.turnControl.changePidGain ( 0.8, 1.2, 0.012, 30.0 );
}