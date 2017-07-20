#ifndef __LEFTNORMALCOURSE__
#define __LEFTNORMALCOURSE__

#include "NormalCourse.h"
#include "SpeedControl.h"

using namespace ev3api;

#define STR(var) #var   //引数にした変数を変数名を示す文字列リテラルとして返すマクロ関数

class LeftNormalCourse : public NormalCourse{
public:
    LeftNormalCourse();
   	void runNormalCourse ( void ) ;

private:
    enum Status {
        STRAIGHT,
        CURVE_RIGHT
    };
    void goStraight(int8_t forward_value);
    void goCurveRight(int8_t forward_value);
    void statusCheck();
    void displayStatus();
    SpeedControl speedControl;
    Status status;
    char status_message[32];
    char distanse_message[32];
    int32_t distanse_total;
};

#endif