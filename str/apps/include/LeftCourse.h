/**
 * @file LeftCourse.h
 * @brief Lコースを走らせるときに呼び出されるクラス
 * @author Futa HIRAKOBA
 */

#ifndef __LEFT_COURSE__
#define __LEFT_COURSE__

#include "Walker.h"
#include "ColorSensor.h"
#include "LeftNormalCourse.h"
#include "SelfLocalization.h"
#include "PuzzleField.h"
#include "PuzzleLineTracer.h"
#include "Navigation.h"

using namespace ev3api;

/**
* Lコースを走らせるときに呼び出されるクラス
*/
class LeftCourse {
public:
	/** コンストラクタ。センサ類の初期化を行う */
	LeftCourse();
	/** 各エリアの処理を呼び出す */
	void run();
	/** NormalCourseエリアの処理 */
	void runNormalCourse();
	void runTyokusen(float, float, float, float, bool);
private:
	Walker walker;
    ColorSensor colorSensor;
    /** 自己位置推定 インスタンス 初期化*/
	SelfLocalization sl;
	Navigation navi;    	
};

#endif