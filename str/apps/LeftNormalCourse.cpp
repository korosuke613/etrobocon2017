#include "LeftNormalCourse.h"

LeftNormalCourse::LeftNormalCourse(){
}

void LeftNormalCourse::runNormalCourse(void){
	while ( 1 ) {
        statusCheck();
		switch(status){
            case STRAIGHT: goStraight(50); break;
            case CURVE_RIGHT: goCurveRight(20); break;

            default: goStraight(0);
        }
        displayStatus();
		lineTracer.runLine();
		if (ev3_button_is_pressed(BACK_BUTTON)) break;
	}
}

void LeftNormalCourse::statusCheck(){
    distanse_total = getDistanceTotal();
    if(distanse_total < 3240)status = STRAIGHT;
    else if(distanse_total < 12000)status = CURVE_RIGHT;
    else status = STRAIGHT;
}

void LeftNormalCourse::goStraight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    sprintf(status_message, "Status: %s", "STRAIGHT"); 
    lineTracer.changePidGain ( 0.5, 0.5, 0.012, 45.0 );
}

void LeftNormalCourse::goCurveRight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    sprintf(status_message, "Status: %s", "CURVE_RIGHT"); 
    lineTracer.changePidGain ( 0.8, 1.2, 0.012, 30.0 );
}

void LeftNormalCourse::displayStatus(){
        sprintf(distanse_message, "Distanse: %ld", distanse_total); 
        msg_f(distanse_message, 3);
        msg_f(status_message, 4);
}