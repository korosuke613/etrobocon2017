#ifndef __COMMON_DEFINITION__
#define __COMMON_DEFINITION__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



#define DRIVING_POWER		30
/* 下記のマクロは個体/環境に合わせて変更する必要があります */
#define GYRO_OFFSET           0  /* ジャイロセンサオフセット値(角速度0[deg/sec]時) */
#define LIGHT_WHITE          40  /* 白色の光センサ値 */
#define LIGHT_BLACK           0  /* 黒色の光センサ値 */
#define SONAR_ALERT_DISTANCE 30  /* 超音波センサによる障害物検知距離[cm] */
#define TAIL_ANGLE_STAND_UP  93  /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      3  /* バランス走行時の角度[度] */
#define P_GAIN             2.5F  /* 完全停止用モータ制御比例係数 */
#define PWM_ABS_MAX          60  /* 完全停止用モータ制御PWM絶対最大値 */
//#define DEVICE_NAME     "ET0"  /* Bluetooth名 hrp2/target/ev3.h BLUETOOTH_LOCAL_NAMEで設定 */
//#define PASS_KEY        "1234" /* パスキー    hrp2/target/ev3.h BLUETOOTH_PIN_CODEで設定 */
#define CMD_START         '1'    /* リモートスタートコマンド */
#define BLACK  2
#define WHITE 47
#define GREY (BLACK+WHITE)/2

/* LCDフォントサイズ */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

#define DRIVE_L	   EV3_PORT_C
#define DRIVE_R	   EV3_PORT_B
#define ARM        EV3_PORT_A
#define TAIL       EV3_PORT_D
#define ULTRASONIC EV3_PORT_3
#define TOUCH	   EV3_PORT_1
#define IR	   EV3_PORT_2
#define GYRO       EV3_PORT_4
#define DEL 0.004

#endif

