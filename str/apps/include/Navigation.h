/**
 * @file Navigation.h
 * @brief 2点間を結ぶ仮想直線をライントレースするクラスのヘッダファイル
 * @author Futa HIRAKOBA
 */
 #ifndef __NAVIGATION__
 #define __NAVIGATION__
 
 #include <cmath>
 #include "LineTracerWalker.h"
 #include "SelfLocalization.h"
 
 
 /*! @class Navigation Navigation.h "Navigation.h"
  *  @brief 2点間を結ぶ仮想直線をライントレースするクラス
  *
  * このクラスはLineTracerWalkerクラスを継承しています。
  */
 class Navigation: public LineTracerWalker {
 public:
     /** コンストラクタ */
     Navigation(std::int32_t, std::int32_t);
     
    /** 仮想線を定義する関数
    * @param スタートのX座標
    * @param スタートのY座標
    * @param ゴールのX座標
    * @param ゴールのY座標
    * @return 正常にラインを引けたか */
    bool setLine(float, float, float, float);
    /** 走行体から仮想線までの最短距離を取得する関数
    * @param 現在地のX座標
    * @param 現在地のY座標
    * @return  走行体から仮想線までの最短距離 */
    float getDiffLine(float, float);
    /** 仮想線を走破したかどうかをチェックする */
    bool checkEndOfLine();
    bool calculateValue(std::int32_t, std::int32_t);
    SelfLocalization sl;
    
     /** 0.1sで進んだ距離[mm/0.1s] */    
 
 public:
    /** スタートの座標 */
    float start_x, start_y;
    /** ゴールの座標 */    
    float goal_x, goal_y;
    /** 現在の座標 */
    float current_x, current_y;
    float diff_line;
 };
 
 
 #endif
 