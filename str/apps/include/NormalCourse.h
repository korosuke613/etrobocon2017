#ifndef __NORMALCOURSE__
#define __NORMALCOURSE__

#include "LineTracer.h"
#include "Distance.h"

using namespace ev3api;

class NormalCourse {
public:
	void runNormalCourse ( void ) ;

protected:
	LineTracer lineTracer;
	Distance distance;
	int8_t forward;
    int32_t distanse_total;
} ;

#endif