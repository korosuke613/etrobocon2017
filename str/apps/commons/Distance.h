#ifndef __DISTANCE__
#define __DISTANCE__

#include "Walker.h"

using namespace ev3api;

class Distance {
public:
	int32_t getDistanceTotal( void );
	int32_t getDistanceCurrent( void );
	void resetDistance( void );

private:
    Walker walker;
	// 自己位置格納用変数
	int32_t leftMotorDeg;
	int32_t rightMotorDeg;
	int32_t leftMotorDegTotal;
	int32_t rightMotorDegTotal;
	int32_t leftMotorDegOld;
	int32_t rightMotorDegOld;
} ;

#endif