#ifndef __LINETRACER__
#define __LINETRACER__

#include "TurnControl.h"
#include "SpeedControl.h"
#include "Walker.h"

using namespace ev3api;

class LineTracer {
public:
    LineTracer();
    void runLine();
    void setForward(int8_t setValue);
    int32_t getCountL();
    int32_t getCountR();
    void isLeftsideLine(bool b);
    TurnControl turnControl;
    SpeedControl speedControl;
    int8_t turn;
    
private:
    Walker walker;
    int8_t forward;
    int8_t minus;
};


#endif
