#ifndef __SPEEDCONTROL__
#define __SPEEDCONTROL__

#include "Walker.h"
#include "Pid.h"

class SpeedControl {
public:
    SpeedControl();
    int8_t calculateSpeedForPid( int8_t forward );
    void setForward(int8_t setValue);
	void changePidGain ( double p_gain, double i_gain, double d_gain, double target ) ;
    int8_t getDistance4ms();

private:
    Pid pid;
    int32_t forward;
    int32_t preAngleL;
    int32_t preAngleR;
	Walker walker;
};


#endif
