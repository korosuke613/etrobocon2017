#ifndef __LEFTNORMALCOURSE__
#define __LEFTNORMALCOURSE__

#include "NormalCourse.h"

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
   	bool runNormalCourse ();
    bool statusCheck(int32_t countL, int32_t countR);

private:
    LeftStatus status;
    LeftStatus old_status;
};

#endif