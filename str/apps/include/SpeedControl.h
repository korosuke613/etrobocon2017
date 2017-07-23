/**
 * @file SpeedControl.h
 * @brief PID制御による速度制御クラス
 * @author Futa HIRAKOBA
 */
#ifndef __SPEEDCONTROL__
#define __SPEEDCONTROL__

#include "Walker.h"
#include "Pid.h"
#include <array>

/**
* PID制御による速度制御クラス
*/
class SpeedControl: public Pid {
public:
    /** コンストラクタ */
    SpeedControl();
    
    /** 速度制御をするための前進値(forward)を計算する
    * @return 前進値(forward) */
    int32_t calculateSpeedForPid();

    /** 4ms間の移動距離を取得する
    * @return 進んだ距離[mm/4ms] */
    int8_t calcDistance4ms();

    /** 0.1sで進んだ距離[mm/0.1s] */    
    int16_t speed_value_all;

private:
    /** Walkerクラスのインスタンス</br>
    * モータの回転角度を取得するために必要
    */
	Walker walker;
    /** 前進値(forward) */    
    double forward;
    /** 左モータの回転角度の過去値 */
    int32_t preAngleL;
    /** 右モータの回転角度の過去値 */
    int32_t preAngleR;
    /** 4msごとの進んだ距離 * 25(つまり総和は0.1s) */
    std::array<int16_t, 25> speed_value;
    /** speed_value変数を回すための変数 */
    uint8_t speedCount;
    /** 4ms前のPID値 */
    double pid_value_old;
    /** 4ms進んだ距離[mm/4ms] */    
    int8_t distance4ms;
};


#endif
