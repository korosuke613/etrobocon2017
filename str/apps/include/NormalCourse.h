#ifndef __NORMALCOURSE__
#define __NORMALCOURSE__

#include "LineTracer.h"
#include "Distance.h"
#include "Walker.h"

class NormalCourse {
public:
	void runNormalCourse ( void ) ;

protected:
	Walker walker;
	LineTracer lineTracer;
	Distance distance;
	int8_t forward;
    int32_t distanse_total;
} ;

#endif