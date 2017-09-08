/**
 * @file TurnControl.cpp
 * @brief TurnControlクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "TurnControl.h"

TurnControl::TurnControl():
    Pid(0.8, 1.2, 0.012, 30.0), turn(0.0){

}

std::int8_t TurnControl::calculateTurnForPid( std::int8_t forward, std::int8_t light_value ) {
    calculate((double)light_value);
    double pid_value = get_output();
    double forward_percent = ((double)forward) / 100.0;
    pid_value *= forward_percent;
    turn += (pid_value - pid_value_old) / 2;
    pid_value_old = pid_value;
    return (int)limitOutput(turn);
}
