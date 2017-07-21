#ifndef __LEFTNORMALCOURSE__
#define __LEFTNORMALCOURSE__

#include "NormalCourse.h"

using namespace ev3api;

enum struct LeftStatus {
    STRAIGHT,
    CURVE_RIGHT,
    STOP
};

class LeftNormalCourse : public NormalCourse{
public:
    LeftNormalCourse();
   	void runNormalCourse ( void ) ;

private:
    void goStraight(int32_t forward_value);
    void goCurveRight(int32_t forward_value);
    void statusCheck();
    LeftStatus status;
};

#endif