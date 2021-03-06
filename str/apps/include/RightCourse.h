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
#include "Parking.h"

using namespace ev3api;

/**
* 走行場所の状態を保持する列挙型
*/
enum struct ShinkansenStatus {
    BEFORE_FIRST_SHINKANSEN,
    FIRST_RAIL,
	FIRST_LINE,
	SECOND_LINE,
	BEFORE_SECOND_SHINKANSEN,
	SECOND_RAIL,
	THIRD_LINE,
	FOURTH_LINE,
	BEFORE_THIRD_SHINKANSEN,
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
	void run();
	/** NormalCourseエリアの処理 **/
	void runNormalCourse();
	/** Shinkansenエリアの処理 */
	void runShinkansen();
    /**
     * 直角駐車エリアの処理を行う。
     * Parkingクラスに依存する
     */
    void runParpendicularParking();

private:
	LineTracerWalker lineTracer;
	Lifter lifter;
	BasicWalker basicWalker;
	Walker walker;
	ColorSensor colorSensor;
	SonarSensor sonarSensor;
	ShinkansenStatus shinkansenStatus;
	SelfLocalization sl;	
};

#endif
