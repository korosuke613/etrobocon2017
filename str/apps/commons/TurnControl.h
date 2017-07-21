#ifndef __TURNCONTROL__
#define __TURNCONTROL__

#include "Pid.h"
#include "ColorSensor.h"

using namespace ev3api;

class TurnControl{
public:
    TurnControl();
    int8_t calculateTurnForPid( int8_t forward );
	void changePidGain ( double p_gain, double i_gain, double d_gain, double target ) ;

private:
    Pid pid;
    ColorSensor colorSensor;
};

#endif