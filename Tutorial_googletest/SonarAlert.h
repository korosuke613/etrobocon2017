#ifndef __SONARALERT__
#define __SONARALERT__

class SonarAlert {
public:
    SonarAlert( int, int );
    int detectBarrier( int );
    int getDistanceBorder();

private:
    const signed int SONAR_ALERT_DISTANCE;
    unsigned int timeCounter;
    unsigned int secPerCycle;
};

#endif

