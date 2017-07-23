#ifndef __LEFTNORMALCOURSE__
#define __LEFTNORMALCOURSE__

#include "NormalCourse.h"
#include "SelfLocalization.h"

using namespace ev3api;

enum struct LeftStatus {
    STRAIGHT,
    CURVE_RIGHT,
    CURVE_LEFT,
    CURVE_LEFT_SHORT,
    STOP
};

class LeftNormalCourse : public NormalCourse{
public:
    LeftNormalCourse();
   	void runNormalCourse ( void ) ;

private:
    void goStraight(int8_t forward_value);
    void goCurveRight(int8_t forward_value);
    void goCurveLeft(int8_t forward_value);
    void goCurveLeftShort(int8_t forward_value);
    void stop();
    void statusCheck();
    LeftStatus status;
    LeftStatus old_status;
    /* 自己位置推定 インスタンス 初期化*/
    SelfLocalization sl;
};

#endif