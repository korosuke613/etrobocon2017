#include "SpeedControl.h"

SpeedControl::SpeedControl():
    //pid(0.36, 1.2, 0.027, 30.0), colorSensor( PORT_3 ){
    pid(0.8, 1.2, 0.012, 30.0), forward(30){
}

void SpeedControl::setForward(int8_t setValue){
    forward = setValue;
}

int8_t SpeedControl::calculateSpeedForPid( int8_t forward ) {
    double speed_value = getDistance4ms();
    pid.calculate(speed_value);
    double pid_value = pid.get_output();
    double forward_percent = (double)forward / 100;
    int8_t output = (int8_t)(pid_value * forward_percent);

    return output;
}

void SpeedControl::changePidGain ( double p_gain, double i_gain, double d_gain, double target ) {
	pid.setPid( p_gain, i_gain, d_gain, target );
}

/* 距離更新（4ms間の移動距離を毎回加算している） */
int8_t SpeedControl::getDistance4ms(){
    int32_t curAngleL = walker.get_count_L ();
	int32_t curAngleR = walker.get_count_R ();

    float distance4ms = 0.0;        //4msの距離

    // 4ms間の走行距離 = ((円周率 * タイヤの直径) / 360) * (モータ角度過去値　- モータ角度現在値)
    float distance4msL = ((2 * 3.14 * 81) / 360.0) * (float)(curAngleL - preAngleL);  // 4ms間の左モータ距離
    float distance4msR = ((2 * 3.14 * 81) / 360.0) * (float)(curAngleR - preAngleR);  // 4ms間の右モータ距離
    distance4ms = (distance4msL + distance4msR) / 2.0; //左右タイヤの走行距離を足して割る

    //モータの回転角度の過去値を更新
    preAngleL = curAngleL;
    preAngleR = curAngleR;

    return (int)distance4ms;
}