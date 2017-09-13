#include "EtRobocon2017.h"

/*! \mainpage EtRobocon2017のドキュメント
 *
 * \section intro_sec こんにちは！
 * @b このページは片山研究所モデルベース開発推進事業部が開発している、ETロボコン2017アドバンスドクラス用のプログラムのドキュメントです！
 */

/*
 * touch_sensor = EV3_PORT_1;
 * sonar_sensor = EV3_PORT_2;
 * color_sensor = EV3_PORT_3;
 * gyro_sensor  = EV3_PORT_4;
 *
 * left_motor   = EV3_PORT_C;
 * right_motor  = EV3_PORT_B;
 * lift_motor   = EV3_PORT_A;
 * tail_motor   = EV3_PORT_D;
 */

/**
 * @file Etrobocon2017.cpp
 * @brief Etrobocon2017クラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

EtRobocon2017::EtRobocon2017():
    touchSensor( PORT_1 )
{
    light_white = 60;
    light_black = 0;
    /** TODO Courseクラスに移す */
    ev3_speaker_set_volume(100);
}

void EtRobocon2017::start( int bluetooth_command )
{
    waitStarter( bluetooth_command );

    ev3_led_set_color(LED_GREEN); /* スタート通知 */

    loop();
}

void EtRobocon2017::loop()
{
    SonarAlert sonarAlert( 4 );
    Lifter lifter;
    Emoter emoter;

// Rコースを走らせるときは1, Lコースを走らせるときは0
#if 1
    RightCourse rightCourse;
    rightCourse.convertArea();
#elif 0
    LeftCourse leftCourse;
    leftCourse.convertArea();
#endif
}

void EtRobocon2017::waitStarter( int bluetooth_command )
{
    /* スタート待機 */
    while(1)
    {
        if (bluetooth_command == 1)
        {
            break; /* リモートスタート */
        }

        if ( touchSensor.isPressed()== 1)
        {
            tslp_tsk(500);
            break; /* タッチセンサが押された */
        }

        tslp_tsk(10); /* 10msecウェイト */
    }
}
