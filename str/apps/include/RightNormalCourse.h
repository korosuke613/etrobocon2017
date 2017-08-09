#ifndef __RIGHTNORMALCOURSE__
#define __RIGHTNORMALCOURSE__

#include "NormalCourse.h"

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
   	bool runNormalCourse () ;
    bool statusCheck(int32_t countL, int32_t countR);

private:
    RightStatus status;
    RightStatus old_status;
};

#endif