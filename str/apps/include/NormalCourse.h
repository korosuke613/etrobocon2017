#ifndef __NORMALCOURSE__
#define __NORMALCOURSE__

#include "LineTracerWalker.h"
#include "Distance.h"

class NormalCourse {
public:
	void stop();
	LineTracerWalker lineTracerWalker;

protected:
	Distance distance;
	int8_t forward;
	int8_t turn;
    int32_t distanse_total;
};

#endif