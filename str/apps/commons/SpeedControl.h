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
    int16_t speed_value4_5;

private:
    int32_t forward;
    int32_t preAngleL;
    int32_t preAngleR;
	Walker walker;
    int16_t speed_value[5];
    uint8_t speedCount;
};


#endif
