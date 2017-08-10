#ifndef __RIGHT_COURSE__
#define __RIGHT_COURSE__

#include "ev3api.h"
#include "Walker.h"
#include "ColorSensor.h"
#include "RightNormalCourse.h"
#include "SelfLocalization.h"

using namespace ev3api;

class RightCourse {
public:
	RightCourse();
	void convertArea();
	void runNormalCourse();
private:
	Walker walker;
    ColorSensor colorSensor;
    /* 自己位置推定 インスタンス 初期化*/
    SelfLocalization sl;
};

#endif