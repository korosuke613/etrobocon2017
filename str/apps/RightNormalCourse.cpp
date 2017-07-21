#include "RightNormalCourse.h"

RightNormalCourse::RightNormalCourse(){
    lineTracer.isLeftsideLine(false);
}

void RightNormalCourse::runNormalCourse(void){
	while ( 1 ) {
        forward = lineTracer.speedControl.calculateSpeedForPid();
        statusCheck();
		switch(status){
            case RightStatus::STRAIGHT: goStraight(forward); break;
            case RightStatus::CURVE_RIGHT: goCurveRight(forward); break;

            default: goStraight(0);
        }
		lineTracer.runLine();
		if (ev3_button_is_pressed(BACK_BUTTON)) break;
	}
}

void RightNormalCourse::statusCheck(){
    distanse_total = distance.getDistanceTotal();
    if(distanse_total < 3240)status = RightStatus::STRAIGHT;
    else if(distanse_total < 10000)status = RightStatus::CURVE_RIGHT;
    else if(distanse_total < 12000)status = RightStatus::STRAIGHT;
    else status = RightStatus::STRAIGHT;
}

void RightNormalCourse::goStraight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.turnControl.setPid ( 0.5, 0.5, 0.012, 45.0 );
}

void RightNormalCourse::goCurveRight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.turnControl.setPid ( 0.8, 1.2, 0.012, 30.0 );
}
