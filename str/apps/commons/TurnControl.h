#ifndef __TURNCONTROL__
#define __TURNCONTROL__

#include "Pid.h"
#include "ColorSensor.h"

using namespace ev3api;

class TurnControl: public Pid{
public:
    TurnControl();
    int8_t calculateTurnForPid( int8_t forward );
    int8_t getBrightness();
private:
    ColorSensor colorSensor;
};

#endif