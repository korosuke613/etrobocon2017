#include "NormalCourse.h"

void NormalCourse::runNormalCourse ( void ) {
	int8_t forward = 100 ;
	lineTracer.setForward(forward);
}

void NormalCourse::stop(){
    lineTracer.setForward(0);
}