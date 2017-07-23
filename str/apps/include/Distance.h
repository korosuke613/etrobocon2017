/**
 * @file Distance.h
 * @brief タイヤの進んだ距離（回転角）に関するクラス
 * @author Futa HIRAKOBA
 */
#ifndef __DISTANCE__
#define __DISTANCE__

#include "Walker.h"

using namespace ev3api;

/**
* タイヤの進んだ距離（回転角）に関するクラス
*/
class Distance {
public:
	/** @return スタートしてからの回転角の合計 */
	int32_t getDistanceTotal( void );

	/** @return 最後のresetDistance()からの回転角の合計 */
	int32_t getDistanceCurrent( void );

	/** 相対的な回転角の現在地を0にする */
	void resetDistance( void );

private:
	/** Walkerクラスのインスタンス */
    Walker walker;
	/** 絶対的な回転角（右タイヤ） */
	int32_t leftMotorDegTotal;
	/** 絶対的な回転角（左タイヤ） */
	int32_t rightMotorDegTotal;	
	/** 相対的な回転角を計算するときに使う変数（右タイヤ） */
	int32_t leftMotorDegOld;
	/** 相対的な回転角を計算するときに使う変数（左タイヤ） */
	int32_t rightMotorDegOld;
} ;

#endif