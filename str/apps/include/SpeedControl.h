/**
 * @file SpeedControl.h
 * @brief PID制御による速度制御クラス
 * @author Futa HIRAKOBA
 */
#ifndef __SPEEDCONTROL__
#define __SPEEDCONTROL__

#include "Pid.h"
#include <array>
#include <cstdint>

/*! @class SpeedControl SpeedControl.h "SpeedControl.h"
 *  @brief PID制御による速度制御クラス
 *
 * このクラスはPidクラスを継承しています。
 */
class SpeedControl: public Pid {
public:
    /** コンストラクタ */
    SpeedControl();
    
    /** 速度制御をするための前進値(forward)を計算する
    * @param curAngleL 左モータ回転角
    * @param curAngleR 右モータ回転角
    * @return forward 前進値 */
    std::int8_t calculateSpeedForPid(std::int32_t curAngleL, std::int32_t curAngleR);
    std::int16_t getSpeed100ms();
        
    /** 0.1sで進んだ距離[mm/0.1s] */    
    std::int16_t speed_value_all;

protected:
    /** 4ms間の移動距離を取得する
    * @param curAngleL 左モータ回転角
    * @param curAngleR 右モータ回転角
    * @return 進んだ距離[mm/4ms] */
    std::int8_t calcDistance4ms(std::int32_t curAngleL, std::int32_t curAngleR);

private:
    /** 前進値(forward) */    
    double forward;
    /** 左モータの回転角度の過去値 */
    std::int32_t preAngleL;
    /** 右モータの回転角度の過去値 */
    std::int32_t preAngleR;
    /** 4msごとの進んだ距離 * 25(つまり総和は0.1s) */
    std::array<std::int16_t, 25> speed_value;
    /** speed_value変数を回すための変数 */
    std::uint8_t speedCount;
    /** 4ms前のPID値 */
    double pid_value_old;
    /** 4ms進んだ距離[mm/4ms] */    
    std::int8_t distance4ms;
};


#endif
