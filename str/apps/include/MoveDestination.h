/**
 * @file MoveDestination.h
 * @brief 2点間を結ぶ仮想直線をライントレースするクラスのヘッダファイル
 * @author Futa HIRAKOBA
 */
 #ifndef __MOVEDESTINATION__
 #define __MOVEDESTINATION__
 
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
     
     /** 速度制御をするための前進値(forward)を計算する
     * @param curAngleL 左モータ回転角
     * @param curAngleR 右モータ回転角
     * @return forward 前進値 */

         
     /** 0.1sで進んだ距離[mm/0.1s] */    
 
 protected:
     /** 4ms間の移動距離を取得する
     * @param curAngleL 左モータ回転角
     * @param curAngleR 右モータ回転角
     * @return 進んだ距離[mm/4ms] */
 
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
 