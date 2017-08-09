#ifndef __LINETRACER__
#define __LINETRACER__

#include "TurnControl.h"
#include "SpeedControl.h"
#include "Walker.h"
#include "ColorSensor.h"

using namespace ev3api;

class LineTracer {
public:
    LineTracer();
    void runLine();
    void setForward(int8_t setValue);
    void setTurn(int8_t setValue);
    void isLeftsideLine(bool b);
    TurnControl turnControl;
    SpeedControl speedControl;
    
private:
    Walker walker;
    ColorSensor colorSensor;
    int8_t forward;
    int8_t turn;
    int8_t minus;
};


#endif
