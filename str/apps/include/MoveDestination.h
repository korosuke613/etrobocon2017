/**
 * @file MoveDestination.h
 * @brief 2点間を結ぶ仮想直線をライントレースするクラスのヘッダファイル
 * @author Futa HIRAKOBA
 */
 #ifndef __MOVEDESTINATION__
 #define __MOVEDESTINATION__
 
 #include <cmath>
 #include "LineTracerWalker.h"
 #include "SelfLocalization.h"
 
 
 /*! @class MoveDestination MoveDestination.h "MoveDestination.h"
  *  @brief 2点間を結ぶ仮想直線をライントレースするクラス
  *
  * このクラスはLineTracerWalkerクラスを継承しています。
  */
 class MoveDestination: public LineTracerWalker {
 public:
     /** コンストラクタ */
     MoveDestination();
     
     /** 仮想線を定義する
     * @param curAngleL 左モータ回転角
     * @param curAngleR 右モータ回転角
     * @return forward 前進値 */
    bool setLine(float, float, float, float);
    float getDiffLine(float, float);
    bool checkEndOfLine();
    bool calculateValue(std::int32_t, std::int32_t);
         
     /** 0.1sで進んだ距離[mm/0.1s] */    
 
 private:
    SelfLocalization sl;
    /** スタートの座標 */
    float start_x, start_y;
    /** ゴールの座標 */    
    float goal_x, goal_y;
    /** 現在の座標 */
    float current_x, current_y;
    float diff_line;
 };
 
 
 #endif
 