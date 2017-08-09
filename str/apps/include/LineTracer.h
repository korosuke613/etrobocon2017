#ifndef __LINETRACER__
#define __LINETRACER__

#include "TurnControl.h"
#include "SpeedControl.h"

class LineTracer {
public:
    LineTracer();
    void runLine(int32_t countL, int32_t countR, int8_t light_value);
    void setForward(int8_t setValue);
    void setTurn(int8_t setValue);
    int8_t getForward();
    int8_t getTurn();
    void isLeftsideLine(bool b);
    TurnControl turnControl;
    SpeedControl speedControl;
    int8_t minus;
private:
    int8_t forward;
    int8_t turn;
};


#endif
