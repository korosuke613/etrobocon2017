/**
 * @file RightCourse.h
 * @brief Rコースを走らせるときに呼び出されるクラス
 * @author Futa HIRAKOBA
 */

#ifndef __RIGHT_COURSE__
#define __RIGHT_COURSE__

#include "ev3api.h"
#include "util.h"
#include "Walker.h"
#include "ColorSensor.h"
#include "SonarSensor.h"
#include "RightNormalCourse.h"
#include "Shinkansen.h"
#include "Distance.h"
#include "SelfLocalization.h"
#include "Lifter.h"
#include "BasicWalker.h"

using namespace ev3api;

/**
* 走行場所の状態を保持する列挙型
*/
enum struct ShinkansenStatus {
    BEFORE_SHINKANSEN,
    FIRST_RAIL,
	FIRST_LINE,
	FIRST_RIGHT_ANGLE,
	PRIZE,
    STOP
};

/**
* Rコースを走らせるときに呼び出されるクラス
*/
class RightCourse {
public:
	/** コンストラクタ。センサ類の初期化を行う **/
	RightCourse();
	/** 各エリアの処理を呼び出す **/
	void convertArea();
	/** NormalCourseエリアの処理 **/
	void runNormalCourse();
	/** Shinkansenエリアの処理 */
	void runShinkansen();
	/** 色を見つけるまで走る処理 **/
	void runColor();
	/** 色検知の処理 **/
	void colorDetection();
private:
	LineTracerWalker lineTracer;
	Lifter lifter;
	BasicWalker basicWalker;
	Walker walker;
	ColorSensor colorSensor;
	SonarSensor sonarSensor;
	ShinkansenStatus shinkansenStatus;
	Distance distance;
};

#endif