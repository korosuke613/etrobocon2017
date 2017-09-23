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
#include "Navigation.h"

// グローバル変数
int speed100ms, forword, turn, target;
int right_motor, left_motor;

// プロトタイプ宣言
void calcVirtualWheels();

int main(){
    speed100ms = forword = right_motor = left_motor = turn = 0;
    
    /** １．コンストラクタを作成する */
    Navigation navi(0, 0);

    /** ２．PIDパラメータの設定する 
    * 今回は以下のようにしています
    * Kp = 2.0
    * Ki = 2.0
    * Kd = 0.024
    * 目標値 = 70.0
    */
    navi.setLine(0.0, 0.0, 500.0, 500.0);
    // 注）4msごとに実行されると仮定して2500回(10秒)回してます
    std::cout << "スピード(100ms), forword値, Target値, turn値, 前進値" << std::endl;
    while(navi.calculateValue(left_motor, right_motor)){
        speed100ms = navi.speedControl.getSpeed100ms();
        calcVirtualWheels();
        /** ３．PID計算をする */
        target = navi.getDiffLine(navi.sl.getPointX(), navi.sl.getPointY());        
        forword = navi.getForward();
        turn = navi.getTurn();
        // 結果を画面に出力
        //std::cout << "スピード(100ms) " << speed100ms << ", forword値 " << forword << ",Target値" << target << ", turn値 " << turn << ", 前進値" << (right_motor + left_motor) / 2 << std::endl;
        std::cout << speed100ms << "," << forword << "," << target << "," << turn << "," << (right_motor + left_motor) / 2 << std::endl;                
    }
    navi.setLine(500.0, 500.0, 1000.0, 750.0);    
    while(navi.calculateValue(left_motor, right_motor)){
        speed100ms = navi.speedControl.getSpeed100ms();
        calcVirtualWheels();
        /** ３．PID計算をする */
        target = navi.getDiffLine(navi.sl.getPointX(), navi.sl.getPointY());        
        forword = navi.getForward();
        turn = navi.getTurn();
        // 結果を画面に出力
        //std::cout << "スピード(100ms) " << speed100ms << ", forword値 " << forword << ",Target値" << target << ", turn値 " << turn << ", 前進値" << (right_motor + left_motor) / 2 << std::endl;
        std::cout << speed100ms << "," << forword << "," << target << "," << turn << "," << (right_motor + left_motor) / 2 << std::endl;                
    }
    navi.setLine(1000.0, 750.0, 0.0, 0.0);    
    while(navi.calculateValue(left_motor, right_motor)){
        speed100ms = navi.speedControl.getSpeed100ms();
        calcVirtualWheels();
        /** ３．PID計算をする */
        target = navi.getDiffLine(navi.sl.getPointX(), navi.sl.getPointY());        
        forword = navi.getForward();
        turn = navi.getTurn();
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