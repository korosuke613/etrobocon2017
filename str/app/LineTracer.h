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
    void setForward(int8_t setValue);

private:
    Pid pid;
    ColorSensor colorSensor;
    Walker walker;
    int8_t forward;
};


#endif
