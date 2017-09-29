#ifndef __BASIC_WALKER__
#define __BASIC_WALKER__

#include "Motor.h"
#include "Clock.h"
#include "util.h"

using namespace ev3api ;

class BasicWalker {
public:
	BasicWalker () ;
	void spin ( int32_t, bool, int32_t ) ;
	void goStraight ( int32_t, int32_t ) ;
	void backStraight ( int32_t, int32_t ) ;

    const bool SPIN_LEFT = false;
    const bool SPIN_RIGHT = true; 
	
private:
    Motor leftWheel;
    Motor rightWheel;
    Clock clock;
    int32_t leftReverseValue ;
    int32_t rightReverseValue ;
	
} ;

#endif
