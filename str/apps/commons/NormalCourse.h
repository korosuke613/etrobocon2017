#ifndef __NORMALCOURSE__
#define __NORMALCOURSE__

#include "LineTracer.h"

using namespace ev3api ;

class NormalCourse {
public:
	void runNormalCourse ( void ) ;

protected:
	int32_t getDistanceTotal( void );
	int32_t getDistanceCurrent( void );
	void resetDistance( void );
	LineTracer lineTracer ;
	Walker walker ;
	// 自己位置格納用変数
	int32_t leftMotorDeg ;
	int32_t rightMotorDeg ;
	int32_t leftMotorDegTotal;
	int32_t rightMotorDegTotal;
	int32_t leftMotorDegOld;
	int32_t rightMotorDegOld;
} ;

#endif