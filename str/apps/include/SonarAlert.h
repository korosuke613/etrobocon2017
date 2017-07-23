#ifndef __SONARALERT__
#define __SONARALERT__

#include <SonarSensor.h>

using namespace ev3api;

class SonarAlert {
public:
    SonarAlert( int );
    SonarAlert( int, int, SonarSensor& );
    ~SonarAlert();
    int detectBarrier();
    int getDistanceBorder();

private:
    signed int SONAR_ALERT_DISTANCE;
    SonarSensor* sonarSensor;
    unsigned int timeCounter;
    unsigned int secPerCycle;
};

#endif

