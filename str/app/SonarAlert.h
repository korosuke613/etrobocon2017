#ifndef __SONARALERT__
#define __SONARALERT__

#include <SonarSensor.h>

using namespace ev3api;

class SonarAlert {
public:
    SonarAlert( int );
    int detectBarrier( int );

private:
    SonarSensor sonarSensor;
    unsigned int timeCounter;
    unsigned int secPerCycle;
};

#endif

