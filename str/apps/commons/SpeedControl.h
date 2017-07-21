#ifndef __SPEEDCONTROL__
#define __SPEEDCONTROL__

#include "Walker.h"
#include "Pid.h"

class SpeedControl: public Pid {
public:
    SpeedControl();
    int32_t calculateSpeedForPid();
    void setForward(int8_t setValue);
    int8_t getDistance4ms();
    int8_t distance4ms;

private:
    int32_t forward;
    int32_t preAngleL;
    int32_t preAngleR;
	Walker walker;
};


#endif
