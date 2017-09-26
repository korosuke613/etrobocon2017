#ifndef __BASIC_WALKER__
#define __BASIC_WALKER__

#include "Motor.h"
#include "Clock.h"
#include "util.h"

#define SPIN_LEFT   1
#define SPIN_RIGHT -1 

using namespace ev3api ;

class basicWalker {
public:
	basicWalker () ;
	void parkingLeft ( void ) ;
	void spinRightAngle ( int32_t, int32_t ) ;
	void goStraight ( int32_t, int32_t ) ;
	void backStraight ( int32_t, int32_t ) ;
	
private:
  Motor leftWheel;
  Motor rightWheel;
  Clock clock;
  int32_t leftReverseValue ;
  int32_t rightReverseValue ;
	
} ;

#endif