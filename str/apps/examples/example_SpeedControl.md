# SpeedControlクラスの使い方

SpeedControlクラスの仕様？については[こちら](https://korosuke613.github.io/etrobocon2017/dd/dc1/class_speed_control.html)をご覧ください。

## 概要
SpeedControlクラスはEV3をPID制御を用いて速度制御するためのクラスです。PIDクラスを継承しています。

## 使い方
### 1. インクルードする
```c++
#include "SpeedControl.h"
```

### 2. コンストラクタを作成する
```c++
SpeedControl sp;
```

### 3. PIDパラメータを設定する
```c++
sp.setPid(Kp, Ki, Kd, target);
```
[setPidメソッド](https://korosuke613.github.io/etrobocon2017/dc/de1/class_pid.html#aa8626402086bcd10cbb7f581c92300fb)でPIDパラメータを設定できます。
* Kp - 比例定数
* Ki - 積分定数
* Kd - 微分定数
* target - 目標値

### 4. PID計算をする
```c++
value = sp.calculateSpeedForPid(right_motor, left_motor);
```
[calculateSpeedForPidメソッド](https://korosuke613.github.io/etrobocon2017/dd/dc1/class_speed_control.html#a4dc24488ce1566fe7b2dc1ecaf1a7bc8)でPID計算ができます。
* value - 実際に計算された結果
* right_motor - 右モータの回転角
* left_motor - 左モータの回転角

**この計算は4msごとに実行してください。**

## 使用例
[ソースはこちら](https://gist.github.com/korosuke613/9b595f525988115c085337dc386d83e6)

今回はPIDパラメータを以下のように設定しています。
* Kp = 2.0
* Ki = 2.0
* Kd = 0.024
* 目標値 = 70.0

```c++
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
```
### コンパイル方法
```bash
g++ -w ../src/Pid.cpp ../src/SpeedControl.cpp example_SpeedControl.cpp -I../include
```

### 実行結果
最後から30行を抽出しています。
大体70[m/0.1s]近くをさまよっていることがわかります。
```bash
スピード(100ms) 72, PID値 26, 前進値5160
スピード(100ms) 70, PID値 23, 前進値5163
スピード(100ms) 72, PID値 26, 前進値5165
スピード(100ms) 70, PID値 23, 前進値5168
スピード(100ms) 72, PID値 26, 前進値5170
スピード(100ms) 70, PID値 25, 前進値5173
スピード(100ms) 70, PID値 23, 前進値5176
スピード(100ms) 72, PID値 26, 前進値5178
スピード(100ms) 70, PID値 23, 前進値5181
スピード(100ms) 72, PID値 24, 前進値5183
スピード(100ms) 72, PID値 24, 前進値5185
スピード(100ms) 72, PID値 26, 前進値5187
スピード(100ms) 70, PID値 23, 前進値5190
スピード(100ms) 72, PID値 24, 前進値5192
スピード(100ms) 72, PID値 24, 前進値5194
スピード(100ms) 72, PID値 26, 前進値5196
スピード(100ms) 70, PID値 26, 前進値5198
スピード(100ms) 68, PID値 25, 前進値5200
スピード(100ms) 68, PID値 25, 前進値5202
スピード(100ms) 68, PID値 25, 前進値5204
スピード(100ms) 68, PID値 27, 前進値5206
スピード(100ms) 66, PID値 24, 前進値5209
スピード(100ms) 68, PID値 25, 前進値5212
スピード(100ms) 68, PID値 25, 前進値5214
スピード(100ms) 68, PID値 27, 前進値5216
スピード(100ms) 66, PID値 26, 前進値5218
スピード(100ms) 66, PID値 27, 前進値5220
スピード(100ms) 64, PID値 24, 前進値5223
スピード(100ms) 66, PID値 27, 前進値5225
```