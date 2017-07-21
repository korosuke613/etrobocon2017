#ifndef __ETROBOCON2017__
#define __ETROBOCON2017__

#include "ev3api.h"
#include "TouchSensor.h"
#include "SonarAlert.h"
#include "Lifter.h"
#include "Emoter.h"
#include "LineTracer.h"
#include "NormalCourse.h"
#include "LeftNormalCourse.h"
#include "RightNormalCourse.h"

using namespace ev3api;

class EtRobocon2017 {
public:
    EtRobocon2017();
    void start( int );
    void waitStarter( int );
    void loop();

private:
    TouchSensor touchSensor;
    int8_t light_white;
    int8_t light_black;

};

#endif
