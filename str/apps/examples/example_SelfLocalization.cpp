/**
* example_SpeedControl.cpp
* このプログラムはSpeedControlクラスを使う時に参考にできる使用例です。
* 
* 【コンパイル・実行の仕方】
* g++-7 -w ../src/Pid.cpp ../src/SpeedControl.cpp example_SpeedControl.cpp -I../include
* ./a.out
*/

#include <iostream>
#include <random>
#include <unistd.h>
/** インクルード */
#include "LineTracerWalker.h"
#include "SelfLocalization.h"

// グローバル変数
int speed100ms, forword, turn, target;
int right_motor, left_motor;

// プロトタイプ宣言
void calcVirtualWheels();

int main(){
    speed100ms = forword = right_motor = left_motor = turn = 0;
    
    /** １．コンストラクタを作成する */
    SelfLocalization sl(0, 0, true);
    LineTracerWalker lineTracer;

    /** ２．PIDパラメータの設定する 
    * 今回は以下のようにしています
    * Kp = 2.0
    * Ki = 2.0
    * Kd = 0.024
    * 目標値 = 70.0
    */
    float target_x = 500.0;
    float target_y = 500.0;
    float start_x = 0.0;
    float start_y = 0.0;
    lineTracer.speedControl.setPid(2.0, 2.0, 0.024, 30.0);
    lineTracer.turnControl.setPid(4.0, 0.0, 0.0, 0.0);
    lineTracer.isLeftsideLine(true);
    sl.update(0, 0);
    target = sl.calculate_between_ev3_and_border(0.0, 0.0, target_x, target_y, 0.0, 0.0);
    // 注）4msごとに実行されると仮定して2500回(10秒)回してます
    std::cout << "スピード(100ms), forword値, Target値, turn値, 前進値" << std::endl;
    while(sl.is_below_target_line_of_x(target_x) || sl.is_below_target_line_of_y(target_y)){
        speed100ms = lineTracer.speedControl.getSpeed100ms();
        calcVirtualWheels();
        /** ３．PID計算をする */
        forword = lineTracer.speedControl.calculateSpeedForPid(right_motor, left_motor);
        turn = lineTracer.turnControl.calculateTurnForPid(forword, target);        
        sl.update(left_motor, right_motor);
        target = sl.calculate_between_ev3_and_border(0.0, 0.0, target_x, target_y, sl.getPointX(), sl.getPointY());        
        // 結果を画面に出力
        //std::cout << "スピード(100ms) " << speed100ms << ", forword値 " << forword << ",Target値" << target << ", turn値 " << turn << ", 前進値" << (right_motor + left_motor) / 2 << std::endl;
        std::cout << speed100ms << "," << forword << "," << target << "," << turn << "," << (right_motor + left_motor) / 2 << std::endl;                
    }
    target_x = 1000.0;
    target_y = 750.0;
    start_x = sl.getPointX();
    start_y = sl.getPointY();
    target = sl.calculate_between_ev3_and_border(start_x, start_y, target_x, target_y, sl.getPointX(), sl.getPointY());
    while(sl.is_below_target_line_of_x(target_x) || sl.is_below_target_line_of_y(target_y)){
        speed100ms = lineTracer.speedControl.getSpeed100ms();
        calcVirtualWheels();
        /** ３．PID計算をする */
        forword = lineTracer.speedControl.calculateSpeedForPid(right_motor, left_motor);
        turn = lineTracer.turnControl.calculateTurnForPid(forword, target);        
        sl.update(left_motor, right_motor);
        target = sl.calculate_between_ev3_and_border(start_x, start_y, target_x, target_y, sl.getPointX(), sl.getPointY());        
        // 結果を画面に出力
        //std::cout << "スピード(100ms) " << speed100ms << ", forword値 " << forword << ",Target値" << target << ", turn値 " << turn << ", 前進値" << (right_motor + left_motor) / 2 << std::endl;
        std::cout << speed100ms << "," << forword << "," << target << "," << turn << "," << (right_motor + left_motor) / 2 << std::endl;                
    }
    target_x = 0.0;
    target_y = 0.0;
    start_x = sl.getPointX();
    start_y = sl.getPointY();
    target = sl.calculate_between_ev3_and_border(start_x, start_y, target_x, target_y, sl.getPointX(), sl.getPointY());
    while(sl.is_over_target_line_of_x(target_x) || sl.is_over_target_line_of_y(target_y)){
        speed100ms = lineTracer.speedControl.getSpeed100ms();
        calcVirtualWheels();
        /** ３．PID計算をする */
        forword = lineTracer.speedControl.calculateSpeedForPid(right_motor, left_motor);
        turn = lineTracer.turnControl.calculateTurnForPid(forword, target);        
        sl.update(left_motor, right_motor);
        target = sl.calculate_between_ev3_and_border(start_x, start_y, target_x, target_y, sl.getPointX(), sl.getPointY());        
        // 結果を画面に出力
        //std::cout << "スピード(100ms) " << speed100ms << ", forword値 " << forword << ",Target値" << target << ", turn値 " << turn << ", 前進値" << (right_motor + left_motor) / 2 << std::endl;
        std::cout << speed100ms << "," << forword << "," << target << "," << turn << "," << (right_motor + left_motor) / 2 << std::endl;        
    }
    return 0;
}

// 仮想的なモータエンコーダです。
void calcVirtualWheels(){
    // モータの前進にランダム性を持たせる
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<int> rand50(0,50); // 1~10の一様乱数
    double r_forword = rand50(mt) * 0.1;

    // 実際に進んだ距離とする
    left_motor += (speed100ms/25 - turn + forword + r_forword) * 0.1;
    right_motor += (speed100ms/25 + turn + forword + r_forword) * 0.1;
}