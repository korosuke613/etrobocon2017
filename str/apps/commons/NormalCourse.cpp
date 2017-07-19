#include "NormalCourse.h"

void NormalCourse::runNormalCourse ( void ) {
	int8_t turn = 0 ;
	int8_t forward = 100 ;
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

int32_t NormalCourse::getDistanceTotal(){
	leftMotorDegTotal = walker.get_count_L () ;
	rightMotorDegTotal = walker.get_count_R () ;
	return (leftMotorDegTotal + rightMotorDegTotal) / 2;
}

int32_t NormalCourse::getDistanceCurrent(){
	leftMotorDeg = walker.get_count_L () - leftMotorDegOld;
	rightMotorDeg = walker.get_count_R () - rightMotorDegOld;

	return (leftMotorDeg + rightMotorDeg) / 2;
}

void NormalCourse::resetDistance(){
	getDistanceTotal();
	leftMotorDegOld = leftMotorDegTotal;
	rightMotorDegOld = rightMotorDegTotal;
}