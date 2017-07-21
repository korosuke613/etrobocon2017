#ifndef __RIGHTNORMALCOURSE__
#define __RIGHTNORMALCOURSE__

#include "NormalCourse.h"

using namespace ev3api;

enum struct RightStatus {
    STRAIGHT,
    CURVE_RIGHT,
    STOP
};

class RightNormalCourse : public NormalCourse{
public:
    RightNormalCourse();
   	void runNormalCourse ( void ) ;

private:
    void goStraight(int32_t forward_value);
    void goCurveRight(int32_t forward_value);
    void statusCheck();
    RightStatus status;
    int32_t current_speed;
    int32_t distanse_total;
};

#endif