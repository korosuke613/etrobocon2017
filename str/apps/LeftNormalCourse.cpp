#include "LeftNormalCourse.h"

LeftNormalCourse::LeftNormalCourse(){
    lineTracer.isLeftsideLine(true);
}

void LeftNormalCourse::runNormalCourse(void){
	while ( 1 ) {
        forward = lineTracer.speedControl.calculateSpeedForPid();
        statusCheck();
		switch(status){
            case LeftStatus::STRAIGHT: goStraight(forward); break;
            case LeftStatus::CURVE_RIGHT: goCurveRight(forward); break;

            default: goStraight(0);
        }
		lineTracer.runLine();
		if (ev3_button_is_pressed(BACK_BUTTON)) break;
	}
}

void LeftNormalCourse::statusCheck(){
    distanse_total = distance.getDistanceTotal();
    if(distanse_total < 3240)status = LeftStatus::STRAIGHT;
    else if(distanse_total < 10000)status = LeftStatus::CURVE_RIGHT;
    else if(distanse_total < 12000)status = LeftStatus::STRAIGHT;
    else status = LeftStatus::STRAIGHT;
}

void LeftNormalCourse::goStraight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.turnControl.changePidGain ( 0.5, 0.5, 0.012, 45.0 );
}

void LeftNormalCourse::goCurveRight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.turnControl.changePidGain ( 0.8, 1.2, 0.012, 30.0 );
}