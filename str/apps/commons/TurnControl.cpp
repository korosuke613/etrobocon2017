#include "TurnControl.h"

TurnControl::TurnControl():
    pid(0.8, 1.2, 0.012, 30.0), colorSensor( PORT_3 ){

}

int8_t TurnControl::calculateTurnForPid( int8_t forward ) {
    double light_value = colorSensor.getBrightness();
    pid.calculate(light_value);
    double pid_value = pid.get_output();
    double forward_percent = (double)forward / 100;
    int8_t output = (int8_t)(pid_value * forward_percent);

    return output;
}

void TurnControl::changePidGain ( double p_gain, double i_gain, double d_gain, double target ) {
	pid.setPid( p_gain, i_gain, d_gain, target );
}