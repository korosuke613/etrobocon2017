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

private:
    TouchSensor touchSensor;
    ColorSensor colorSensor;
    int8_t light_white;
    int8_t light_black;
static const sensor_port_t
    touch_sensor = EV3_PORT_4,
    sonar_sensor = EV3_PORT_3,
    color_sensor = EV3_PORT_2,
    gyro_sensor  = EV3_PORT_1;

static const motor_port_t
    left_motor   = EV3_PORT_C,
    right_motor  = EV3_PORT_B,
    lifter       = EV3_PORT_A,
    emoter       = EV3_PORT_D;

};

#endif

