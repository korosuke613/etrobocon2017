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
<<<<<<< HEAD
    void setForward(int8_t setValue);
=======
	void changePidGain ( double p_gain, double i_gain, double d_gain, double target ) ;
>>>>>>> dev_PidRun_NormalCourse

private:
    Pid pid;
    ColorSensor colorSensor;
    Walker walker;
    int8_t forward;
};


#endif
