/**
 * @file RightNormalCourse.h
 * @brief RコースのNormalCourseの処理を行うクラス
 * @author Futa HIRAKOBA
 */

#ifndef __RIGHTNORMALCOURSE__
#define __RIGHTNORMALCOURSE__

#include "NormalCourse.h"

/**
* 走行場所の状態を保持する列挙型
*/
enum struct RightStatus {
    STRAIGHT,
    CURVE_RIGHT,
    CURVE_LEFT,
    CURVE_LEFT_SHORT,
    STOP
};

/**
* RコースのNormalCourseの処理を行うクラス
*/
class RightNormalCourse : public NormalCourse{
public:
    /** コンストラクタ。 右エッジである設定をしている*/
    RightNormalCourse();
    
    /** 
    * 走行場所でのPID値を設定する 
    * @return Goalしたかどうか
    */
   	bool runNormalCourse () ;
    
    /**
    * 現在の走行場所の状態を設定する
    * @param[in] countL 左タイヤの回転角
    * @param[in] countR 右タイヤの回転角
    * @return 走行場所の状態が変わったかどうか
    */
    bool statusCheck(int32_t countL, int32_t countR);

    /**
    * 現在の走行場所の状態を取得する
    * @return 現在の走行場所の状態(int型)
    */
    int getStatus();
private:
    RightStatus status;
    RightStatus old_status;
};

#endif