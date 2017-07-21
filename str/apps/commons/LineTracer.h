#ifndef __LINETRACER__
#define __LINETRACER__

#include "TurnControl.h"
#include "Walker.h"

using namespace ev3api;

class LineTracer {
public:
    LineTracer();
    void runLine();
    void setForward(int8_t setValue);
    int32_t getCountL();
    int32_t getCountR();
    TurnControl turnControl;
    
private:
    Walker walker;
    int8_t forward;
};


#endif
