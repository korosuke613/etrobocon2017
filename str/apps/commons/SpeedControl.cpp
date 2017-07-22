#include "SpeedControl.h"

SpeedControl::SpeedControl():
    //pid(0.36, 1.2, 0.027, 30.0), colorSensor( PORT_3 ){
    Pid(0.2, 0.5, 0.0, 30.0), forward(30), preAngleL(0), preAngleR(0){
    for(int i=0; i<5; i++)speed_value[i] = 0;
    speedCount = 0;
    //150のときいい感じ pid(0.8, 1.2, 0.0, 30.0), forward(30){
}

void SpeedControl::setForward(int8_t setValue){
    forward = setValue;
}

int32_t SpeedControl::calculateSpeedForPid() {
    speed_value[ speedCount ] = getDistance4ms();
    speed_value4_5 = 0;
    for( int16_t value : speed_value ) {
        speed_value4_5 += value;
    }
    calculate((double)speed_value4_5);
    double pid_value = - limitOutput(get_output());
    speedCount++;
    if( speedCount >= 5 ) speedCount = 0;
    return (int)pid_value;
}

/* 距離更新（4ms間の移動距離を毎回加算している） */
int8_t SpeedControl::getDistance4ms(){
    int32_t curAngleL = walker.get_count_L ();
	int32_t curAngleR = walker.get_count_R ();

    float distance4msFloat = 0.0;        //4msの距離

    // 4ms間の走行距離 = ((円周率 * タイヤの直径) / 360) * (モータ角度過去値　- モータ角度現在値)
    float distance4msL = ((2 * 3.14 * 81) / 360.0) * (float)(curAngleL - preAngleL);  // 4ms間の左モータ距離
    float distance4msR = ((2 * 3.14 * 81) / 360.0) * (float)(curAngleR - preAngleR);  // 4ms間の右モータ距離
    distance4msFloat = (distance4msL + distance4msR) / 2.0; //左右タイヤの走行距離を足して割る

    //モータの回転角度の過去値を更新
    preAngleL = curAngleL;
    preAngleR = curAngleR;

    distance4ms = (int)distance4msFloat;
    // 単位はmm
    return distance4ms;
}