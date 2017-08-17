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
#include "SelfLocalization.h"

using namespace ev3api;

/**
* Rコースを走らせるときに呼び出されるクラス
*/
class RightCourse {
public:
	/** コンストラクタ。センサ類の初期化を行う */
	RightCourse();
	/** 各エリアの処理を呼び出す */
	void convertArea();
	/** NormalCourseエリアの処理 */
	void runNormalCourse();
	/** Shinkansenエリアの処理 */
	void runShinkansen();
private:
	Walker walker;
	ColorSensor colorSensor;
	SonarSensor sonarSensor;
	ShinkansenStatus shinkansenStatus;
};

#endif