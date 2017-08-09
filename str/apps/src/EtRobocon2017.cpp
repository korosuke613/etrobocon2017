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


EtRobocon2017::EtRobocon2017():
    touchSensor( PORT_1 ), colorSensor( PORT_3 )
{
    light_white = 60;
    light_black = 0;
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
    LeftNormalCourse leftNormalCourse;
    RightNormalCourse rightNormalCourse;
    Lifter lifter;
    Emoter emoter;
    bool isNormalCourse;
    // 左レーン時
	while ( 1 ) {
        isNormalCourse = leftNormalCourse.runNormalCourse(walker.get_count_L(), walker.get_count_R());
        //LeftNormalCourse.lineTracer.runLine();
        if(! isNormalCourse)break;
    }
    // 右レーン時
    //rightNormalCourse.runNormalCourse();
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
