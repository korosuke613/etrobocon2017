/**
* example_Navigation.cpp
* このプログラムはNavigationクラスを使う時に参考にできる使用例です。
* 
* 【コンパイル・実行の仕方】
g++-7 -w ../src/Pid.cpp ../src/SpeedControl.cpp ../src/TurnControl.cpp ../src/LineTracerWalker.cpp ../src/SelfLocalization.cpp ../src/Navigation.cpp example_Navigation.cpp -I../include
* ./a.out
*/

/** インクルード */
#include <iostream>
#include <random>
#include <unistd.h>
#include "LineTracerWalker.h"
#include "Navigation.h"

// グローバル変数
int speed100ms;
int right_motor, left_motor;

// プロトタイプ宣言
void run(Navigation &navi, float goal_x, float goal_y, bool);
void calcVirtualWheels(int, int);

int main(){
    speed100ms = right_motor = left_motor = 0;
    
    /** １．コンストラクタを作成する */
    Navigation navi(0, 0);
   
    std::cout << "スピード(100ms), forword値, Target値, turn値, 前進値" << std::endl;
    run(navi, -100.0, 100.0, true);
    run(navi, -300.0, 80.0, true);
    run(navi, -150.0, 100.0, false);    
    run(navi, -150.0, 400.0, false);
    
    return 0;
}

void run(Navigation &navi, float goal_x, float goal_y, bool isBack){
    bool isEndAngle = false;
    int minus = 1;
    if(isBack == true)minus = -1;
    navi.turnControl.setPid(4.0, 0.5, 3.0, 0.0);
    navi.speedControl.setPid(2.0, 2.0, 0.024, 60.0 * minus); 

    navi.setLine(navi.sl.getPointX(), navi.sl.getPointY(), goal_x, goal_y);
    navi.getDiffLine(navi.sl.getPointX(), navi.sl.getPointY());
    navi.calculate_line_angle(isBack);
    navi.sl.init_normal_vector(navi.start_x, navi.start_y, navi.goal_x, navi.goal_y, navi.current_x, navi.current_y);
    while(!navi.sl.is_over_normal_vector(navi.current_x, navi.current_y)){
        if(! isEndAngle){
            isEndAngle = navi.calculateAngle(left_motor, right_motor, isBack);
        }else{
            navi.calculateValue(left_motor, right_motor, isBack);
        }
        speed100ms = navi.speedControl.getSpeed100ms();
        calcVirtualWheels(navi.getForward(), navi.getTurn());
        // 結果を画面に出力
        std::cout << navi.sl.getPointX() << ", " << navi.sl.getPointY() << std::endl;    
        //std::cout << "スピード(100ms) " << speed100ms << ", forword値 " << forword << ",Target値" << target << ", turn値 " << turn << ", 前進値" << (right_motor + left_motor) / 2 << std::endl;
        //std::cout << speed100ms << "," << forword << "," << target << "," << turn << "," << (right_motor + left_motor) / 2 << std::endl;                
    }  

}

// 仮想的なモータエンコーダです。
void calcVirtualWheels(int forward, int turn){
    // モータの前進にランダム性を持たせる
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<int> rand50(0,50); // 1~10の一様乱数
    double r_forword = rand50(mt) * 0.3;

    // 実際に進んだ距離とする
    left_motor += (speed100ms/15 - turn + forward + r_forword) * 0.1;
    right_motor += (speed100ms/15 + turn + forward + r_forword) * 0.1;
}