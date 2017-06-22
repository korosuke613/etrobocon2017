#ifndef __LINETRACER__
#define __LINETRACER__

#include "pid.h"
#include "ColorSensor.h"
#include "Walker.h"

using namespace ev3api;

class LineTracer {
public:
    LineTracer();
    void runLine();
    int8_t calculateTurnForPid( int8_t forward );

private:
    Pid pid;
    ColorSensor colorSensor;
    Walker walker;
};


#endif
