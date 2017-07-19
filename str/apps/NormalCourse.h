#ifndef __NORMALCOURSE__
#define __NORMALCOURSE__

#include "LineTracer.h"

using namespace ev3api ;

class NormalCourse {
public :
	void runNormalCourse ( void ) ;
private :
	LineTracer lineTracer ;
	Walker walker ;
	// 自己位置格納用変数
	int32_t leftMotorDeg ;
	int32_t rightMotorDeg ;
	int checkCurveLine ( int32_t, int32_t ) ;
} ;

#endif