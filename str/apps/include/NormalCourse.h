#ifndef __NORMALCOURSE__
#define __NORMALCOURSE__

#include "LineTracer.h"
#include "Distance.h"

class NormalCourse {
public:
	void runNormalCourse ( void ) ;
	LineTracer lineTracer;

protected:
	Distance distance;
	int8_t forward;
	int8_t turn;
    int32_t distanse_total;
} ;

#endif