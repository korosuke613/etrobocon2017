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
#include "SpeedControl.h"

// グローバル変数
int speed100ms, value;
int right_motor, left_motor;

// プロトタイプ宣言
void calcVirtualWheels();

int main(){
    speed100ms = value = right_motor = left_motor = 0;
    
    /** １．コンストラクタを作成する */
    SpeedControl sp;

    /** ２．PIDパラメータの設定する 
    * 今回は以下のようにしています
    * Kp = 2.0
    * Ki = 2.0
    * Kd = 0.024
    * 目標値 = 70.0
    */
    sp.setPid(2.0, 2.0, 0.024, 70.0);

    // 注）4msごとに実行されると仮定して2500回(10秒)回してます
    for(int i=0; i<2500; i++){
        speed100ms = sp.getSpeed100ms();
        calcVirtualWheels();
        /** ３．PID計算をする */
        value = sp.calculateSpeedForPid(right_motor, left_motor);
        // 結果を画面に出力
        std::cout << "スピード(100ms) " << speed100ms << ", PID値 " << value << ", 前進値" << (right_motor + left_motor) / 2 << std::endl;
        usleep(4000);
    }
    return 0;
}

// 仮想的なモータエンコーダです。
void calcVirtualWheels(){
    // モータの前進にランダム性を持たせる
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<int> rand50(0,50); // 1~10の一様乱数
    double r_value = rand50(mt) * 0.1;

    // 実際に進んだ距離とする
    left_motor = right_motor += (speed100ms/25 + value + r_value) * 0.1;
}