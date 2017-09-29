/**
 * @file SpeedControl.cpp
 * @brief SpeedControlクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "SpeedControl.h"

SpeedControl::SpeedControl():
    //pid(0.36, 1.2, 0.027, 30.0), colorSensor( PORT_3 ){
    Pid(0.2, 0.5, 0.0, 30.0), forward(0), preAngleL(0), preAngleR(0){
    for(int i=0; i<25; i++)speed_value[i] = 0;
    speedCount = 0;
    speed_value_all = 0;
    pid_value_old = 0.0;
    distance4ms = 0.0;
    //150のときいい感じ pid(0.8, 1.2, 0.0, 30.0), forward(30){
}

std::int8_t SpeedControl::calculateSpeedForPid(std::int32_t curAngleL, std::int32_t curAngleR) {
    int8_t speed_value_thistime = calcDistance4ms(curAngleL, curAngleR);
    speed_value_all += (speed_value_thistime - speed_value[ speedCount ]);
    speed_value[ speedCount ] = speed_value_thistime;
    calculate((double)speed_value_all);
    double pid_value = - get_output();
    speedCount++;
    if( speedCount >= 25 ) speedCount = 0;
    forward += (pid_value - pid_value_old) / 10; 
    pid_value_old = pid_value;
    return (int)limitOutput(forward);
}

/* 距離更新（4ms間の移動距離を毎回加算している） */
std::int8_t SpeedControl::calcDistance4ms(std::int32_t curAngleL, std::int32_t curAngleR){

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

std::int16_t SpeedControl::getSpeed100ms(){
    return speed_value_all;
}