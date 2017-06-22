#include "LineTracer.h"

LineTracer::LineTracer():
    pid(2.0, 0.0, 0.3, 30.0), colorSensor( PORT_3 ){
}

void LineTracer::runLine(){
    int8_t turn;
    int8_t forward = 30;


    while(1)
    {
        if (ev3_button_is_pressed(BACK_BUTTON)) break;
        turn = calculateTurnForPid( forward );

        walker.run( forward, turn );

        tslp_tsk(4); // 4msec周期起動
    }

}

int8_t LineTracer::calculateTurnForPid( int8_t forward ) {
    double light_value = colorSensor.getBrightness();
    pid.calculate(light_value);
    double output = static_cast<int8_t>(pid.get_output());

    return output;
}
