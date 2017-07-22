#include "TurnControl.h"

TurnControl::TurnControl():
    Pid(0.8, 1.2, 0.012, 30.0), colorSensor( PORT_3 ), turn(0.0){

}

int8_t TurnControl::calculateTurnForPid( int8_t forward ) {
    double light_value = (double)colorSensor.getBrightness();
    calculate(light_value);
    double pid_value = get_output();
    double forward_percent = ((double)forward) / 100.0;
    pid_value *= forward_percent;
    turn += (pid_value - pid_value_old) / 2;
    pid_value_old = pid_value;
    return (int)limitOutput(turn);
}

int8_t TurnControl::getBrightness(){
    return colorSensor.getBrightness();
}