#ifndef __ETROBOCON2017__
#define __ETROBOCON2017__

#include "ev3api.h"
#include "Walker.h"
#include "TouchSensor.h"
#include "ColorSensor.h"
#include "SonarAlert.h"
#include "Lifter.h"
#include "Emoter.h"
#include "LeftNormalCourse.h"
#include "RightNormalCourse.h"
#include "SelfLocalization.h"


using namespace ev3api;

class EtRobocon2017 {
public:
    EtRobocon2017();
    void start( int );
    void waitStarter( int );
    void loop();

private:
	Walker walker;
    TouchSensor touchSensor;
    ColorSensor colorSensor;
    int8_t light_white;
    int8_t light_black;
    /* 自己位置推定 インスタンス 初期化*/
    SelfLocalization sl;
};

#endif
