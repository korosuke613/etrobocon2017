#ifndef __LEFTNORMALCOURSE__
#define __LEFTNORMALCOURSE__

#include "NormalCourse.h"
#include "SelfLocalization.h"

enum struct LeftStatus {
    STRAIGHT,
    STRAIGHT_SLOW,
    CURVE_RIGHT,
    CURVE_LEFT,
    CURVE_LEFT_SHORT,
    STOP
};

class LeftNormalCourse : public NormalCourse{
public:
    LeftNormalCourse();
   	bool runNormalCourse (int32_t countL, int32_t countR);

private:
    void goStraight();
    void goStraightSlow();
    void goCurveRight();
    void goCurveLeft();
    void goCurveLeftShort();
    void stop();
    void statusCheck(int32_t countL, int32_t countR);
    LeftStatus status;
    LeftStatus old_status;
    /* 自己位置推定 インスタンス 初期化*/
    SelfLocalization sl;
};

#endif