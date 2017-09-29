/**
 * @file Shinkansen.h
 * @brief RコースのShinkansenの処理を行うクラス
 * @author Futa HIRAKOBA
 */

#ifndef __SHINKANSEN__
#define __SHINKANSEN__
  
#include <cstdint>
#include "Motor.h"
#include "Walker.h"
#include "ColorSensor.h"
#include "RightNormalCourse.h"
#include "Distance.h"
#include "Lifter.h"
#include "BasicWalker.h"

/**
* RコースのShinkansenの処理を行うクラス
*/
class Shinkansen{
public:
    /** コンストラクタ。 */
    Shinkansen();
    /** 新幹線が通過したか知らせる関数。 */
    bool checkPass(std::int16_t distance);
	/** 線上を前進する処理 **/
	void runForward(double speed, int32_t targetDistance);
	/** 線上を後進する処理 **/
	void runBackward(double speed, int32_t targetDistance);
	/** 黒を見つけるまで回転 **/
	void spinBlack(int8_t forward, int32_t reverseValue);
	/** 色を見つけるまで走る処理 **/
	void runColor();
	/** 色検知の処理 **/
	void colorDetection();
	/** 新幹線エリアの走行パターン1 **/
	void firstPattern();
	/** 新幹線エリアの走行パターン2 **/
	void secondPattern();
  
private:
    std::int16_t time_counter;
    bool isInFrontOf;
    const std::int16_t TO_PASS;
    const std::int8_t PASS_THRESHOLD;    
    const std::int8_t DISTANCE_THRESHOLD;
	LineTracerWalker lineTracer;
	Lifter lifter;
	BasicWalker basicWalker;
	Walker walker;
	ColorSensor colorSensor;
	Motor leftWheel;
	Motor rightWheel;
	Distance distance;
};

#endif