#include "TurnControl.h"

TurnControl::TurnControl():
    Pid(0.8, 1.2, 0.012, 30.0), colorSensor( PORT_3 ){

}

int8_t TurnControl::calculateTurnForPid( int8_t forward ) {
    double light_value = colorSensor.getBrightness();
    calculate(light_value);
    double pid_value = get_output();
    double forward_percent = (double)forward / 100;
    int8_t output = (int8_t)(pid_value * forward_percent);

    return output;
}