#ifndef __LEFT_COURSE__
#define __LEFT_COURSE__

#include "ev3api.h"
#include "Walker.h"
#include "ColorSensor.h"
#include "LeftNormalCourse.h"
#include "SelfLocalization.h"

using namespace ev3api;

class LeftCourse {
public:
	LeftCourse();
	void convertArea();
	void runNormalCourse();
private:
	Walker walker;
    ColorSensor colorSensor;
    /* 自己位置推定 インスタンス 初期化*/
    SelfLocalization sl;
};

#endif