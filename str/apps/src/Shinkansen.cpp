/**
 * @file Shinkansen.cpp
 * @brief Shinkansenクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "Shinkansen.h"

Shinkansen::Shinkansen():
    time_counter(0),
    isInFrontOf(false), 
    TO_PASS(200),
    PASS_THRESHOLD(TO_PASS/10),
    DISTANCE_THRESHOLD(30){

}

bool Shinkansen::checkPass(std::int16_t distance)
{
    if(isInFrontOf){
        time_counter++;
        // 新幹線を検知してからTO_PASS + PASS_THRESHOLD
        if(time_counter > TO_PASS + PASS_THRESHOLD){
            time_counter = 0;            
            isInFrontOf = false;
            return true;
        }
    }else{
        // 新幹線をDISTANCE_THRESHOLD連続で検知するとtime_counterを増やす
        if(distance <= DISTANCE_THRESHOLD){
            time_counter++;            
        }else{
            time_counter = 0;
        }
        // time_counterがPASS_THRESHOLDを超えると、新幹線がいると判断する
        if(time_counter > PASS_THRESHOLD){
            time_counter = 0;            
            isInFrontOf = true;            
        }
    }
    return false;    
}