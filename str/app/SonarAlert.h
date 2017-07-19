#ifndef __SONARALERT__
#define __SONARALERT__

#include <SonarSensor.h>

class SonarAlert {
public:
    SonarAlert( int, int );
    SonarAlert( int, int, SonarSensor& );
    ~SonarAlert();
    int detectBarrier();
    int getDistanceBorder();

private:
    const signed int SONAR_ALERT_DISTANCE;
    SonarSensor* sonarSensor;
    unsigned int timeCounter;
    unsigned int secPerCycle;
};

#endif

