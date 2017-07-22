#ifndef __SPEEDCONTROL__
#define __SPEEDCONTROL__

#include "Walker.h"
#include "Pid.h"

class SpeedControl: public Pid {
public:
    SpeedControl();
    int32_t calculateSpeedForPid();
    int8_t getDistance4ms();
    int8_t distance4ms;
    int16_t speed_value_all;

private:
    double forward;
    int32_t preAngleL;
    int32_t preAngleR;
	Walker walker;
    int16_t speed_value[25];
    uint8_t speedCount;
    double pid_value_old;
};


#endif
