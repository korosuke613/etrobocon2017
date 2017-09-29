#ifndef __BASIC_WALKER__
#define __BASIC_WALKER__

#include "Clock.h"
#include "util.h"
#include "Walker.h"
#include "SpeedControl.h"

using namespace ev3api ;

class BasicWalker {
public:
	BasicWalker () ;
	void reset ( void ) ;
	void parkingLeft ( void ) ;
	void setPidWithoutTarget ( double, double, double ) ;
	void spin ( bool, int32_t ) ;
	void goStraight ( int32_t, int32_t ) ;
	void backStraight ( int32_t, int32_t ) ;
    const bool SPIN_LEFT = false;
    const bool SPIN_RIGHT = true; 

private:
	Clock clock ;
	Walker walker ;
	SpeedControl speedControl ;
	int8_t forward ;
	int32_t leftReverseValue ;
	int32_t rightReverseValue ;
	double p_value ;
	double i_value ;
	double d_value ;
	
} ;

#endif
