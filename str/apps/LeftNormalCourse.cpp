#include "LeftNormalCourse.h"

void LeftNormalCourse::runNormalCourse(void){
	int8_t forward = 100 ;
	lineTracer.setForward(forward);
	while ( 1 ) {
		if ( getDistanceTotal() >3240 ) {
			lineTracer.changePidGain ( 0.5, 0.5, 0.012, 45.0 ) ;
		} else {
			lineTracer.changePidGain ( 0.5, 0.6, 0.2, 45.0 ) ;
		}
		lineTracer.runLine();
		if (ev3_button_is_pressed(BACK_BUTTON)) break;
	}
}