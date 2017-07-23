#ifndef __RIGHTNORMALCOURSE__
#define __RIGHTNORMALCOURSE__

#include "NormalCourse.h"
#include "SelfLocalization.h"

using namespace ev3api;

enum struct RightStatus {
    STRAIGHT,
    CURVE_RIGHT,
    CURVE_LEFT,
    CURVE_LEFT_SHORT,
    STOP
};

class RightNormalCourse : public NormalCourse{
public:
    RightNormalCourse();
   	void runNormalCourse ( void ) ;

private:
    void goStraight(int8_t forward_value);
    void goCurveRight(int8_t forward_value);
    void goCurveLeft(int8_t forward_value);
    void goCurveLeftShort(int8_t forward_value);
    void stop();
    void statusCheck();
    RightStatus status;
    RightStatus old_status;
    /* 自己位置推定 インスタンス 初期化*/
    SelfLocalization sl;
};

#endif