#ifndef __LEFTNORMALCOURSE__
#define __LEFTNORMALCOURSE__

#include "NormalCourse.h"

using namespace ev3api;

class LeftNormalCourse : public NormalCourse{
public:
    LeftNormalCourse();
   	void runNormalCourse ( void ) ;

private:
    enum struct Status {
        STRAIGHT,
        CURVE_RIGHT
    };
    void goStraight(int32_t forward_value);
    void goCurveRight(int32_t forward_value);
    void statusCheck();
    void displayStatus();
    Status status;
    int32_t current_speed;
    int32_t distanse_total;

    char status_message[32];
    char distanse_message[32];
};

#endif