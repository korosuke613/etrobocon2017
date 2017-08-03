#ifndef __TURNCONTROL__
#define __TURNCONTROL__

#include "Pid.h"
#include <cstdint>

class TurnControl: public Pid{
public:
    TurnControl();
    std::int8_t calculateTurnForPid( std::int8_t forward, std::int8_t light_value );
private:
    double turn;
    double pid_value_old;
};

#endif