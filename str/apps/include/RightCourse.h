/**
 * @file RightCourse.h
 * @brief Rコースを走らせるときに呼び出されるクラス
 * @author Futa HIRAKOBA
 */

#ifndef __RIGHT_COURSE__
#define __RIGHT_COURSE__

#include "ev3api.h"
#include "Walker.h"
#include "ColorSensor.h"
#include "RightNormalCourse.h"
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
private:
	Walker walker;
    ColorSensor colorSensor;
    /** 自己位置推定 インスタンス 初期化*/
    SelfLocalization sl;
};

#endif