#include "NormalCourse.h"

void NormalCourse::runNormalCourse ( void ) {
	int8_t turn = 0 ;
	int8_t forward = 100 ;
	while ( 1 ) {
		// 自己位置を取得
		leftMotorDeg = walker.get_count_L () ;
		rightMotorDeg = walker.get_count_R () ;
		if ( checkCurveLine ( leftMotorDeg, rightMotorDeg ) ) {
			lineTracer.runLine () ;
		} else {
			lineTracer.runLine () ;
			//walker.run ( forward, turn ) ;
		}
		if (ev3_button_is_pressed(BACK_BUTTON)) break;
	}
}

int NormalCourse::checkCurveLine ( int32_t leftMotorDeg, int32_t rightMotorDeg ) {
	if ( leftMotorDeg > 3240 && rightMotorDeg > 3240 ) {
		lineTracer.changePidGain ( 0.5, 0.5, 0.012, 45.0 ) ;
		return 1 ;
	} else {
		lineTracer.changePidGain ( 0.5, 0.6, 0.2, 45.0 ) ;
		return 0 ;
	}
}

/*
void NormalCourse::runNormalCourse ( void ) {
	int8_t turn = 0 ;
	int8_t forward = 100 ;
	
	while ( 1 ) {
		leftMotorDeg = walker.get_count_L () ;
		rightMotorDeg = walker.get_count_R () ;
		checkCurveLine ( leftMotorDeg, rightMotorDeg, turn ) ;
		walker.run ( forward, turn ) ;
		if (ev3_button_is_pressed(BACK_BUTTON)) break;
	}
}

int NormalCourse::checkCurveLine ( int32_t leftMotorDeg, int32_t rightMotorDeg, int8_t turn ) {
	if ( leftMotorDeg > 3600 && rightMotorDeg > 3600 ) {
		turn = 60 ;
		return 0 ;
	}
	return 0 ;
}
*/