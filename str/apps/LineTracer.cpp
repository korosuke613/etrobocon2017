#include "LineTracer.h"

LineTracer::LineTracer():
    //pid(0.36, 1.2, 0.027, 30.0), colorSensor( PORT_3 ){
    pid(0.8, 1.2, 0.012, 30.0), colorSensor( PORT_3 ), forward(30){
}

void LineTracer::runLine(){
    int8_t turn;

    //while(1)
    //{
    //    if (ev3_button_is_pressed(BACK_BUTTON)) break;
        turn = calculateTurnForPid( forward );

        walker.run( forward, turn );

        tslp_tsk(4); // 4msec周期起動
    //}

}

void LineTracer::setForward(int8_t setValue){
    forward = setValue;
}

int8_t LineTracer::calculateTurnForPid( int8_t forward ) {
    double light_value = colorSensor.getBrightness();
    pid.calculate(light_value);
    double pid_value = pid.get_output();
    double forward_percent = (double)forward / 100;
    int8_t output = (int8_t)(pid_value * forward_percent);

    return output;
}

void LineTracer::changePidGain ( double p_gain, double i_gain, double d_gain, double target ) {
	pid.setPid( p_gain, i_gain, d_gain, target );
}