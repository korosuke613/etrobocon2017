/**
 * @file TurnControl.h
 * @brief PID制御によるターン制御クラス
 * @author Futa HIRAKOBA
 */
#ifndef __TURNCONTROL__
#define __TURNCONTROL__

#include "Pid.h"
#include <cstdint>

/**
* PID制御によるターン制御クラス
*/
class TurnControl: public Pid{
public:
    /** コンストラクタ */
    TurnControl();
    /** ターン制御をするためのターン値(turn)を計算する
    * @return ターン値(turn) */
    std::int8_t calculateTurnForPid( std::int8_t forward, std::int8_t light_value );
private:
    double turn;
    double pid_value_old;
};

#endif