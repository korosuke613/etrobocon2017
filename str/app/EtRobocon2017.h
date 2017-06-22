#ifndef __ETROBOCON2017__
#define __ETROBOCON2017__

#include "ev3api.h"
#include "TouchSensor.h"
#include "ColorSensor.h"
#include "SonarAlert.h"
#include "Walker.h"
#include "Lifter.h"
#include "Emoter.h"

using namespace ev3api;

class EtRobocon2017 {
public:
    EtRobocon2017();
    void start( int );
    void waitStarter( int );
    void loop();

private:
    TouchSensor touchSensor;
    ColorSensor colorSensor;
    int8_t light_white;
    int8_t light_black;

};

#endif

