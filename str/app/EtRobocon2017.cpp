#include "EtRobocon2017.h"

/*
 * touch_sensor = EV3_PORT_4;
 * sonar_sensor = EV3_PORT_3;
 * color_sensor = EV3_PORT_2;
 * gyro_sensor  = EV3_PORT_1;
 *
 * left_motor   = EV3_PORT_C;
 * right_motor  = EV3_PORT_B;
 * lift_motor   = EV3_PORT_A;
 * tail_motor   = EV3_PORT_D;
 */


EtRobocon2017::EtRobocon2017():
    touchSensor( PORT_4 ), colorSensor( PORT_2 )
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
    Walker walker;
    Lifter lifter;
    Emoter emoter;
    int8_t forward = 0;      /* 前後進命令 */
    int8_t turn = 0;         /* 旋回命令 */

    // bool isUpped = false;

    /**
    * Main loop for the self-balance control algorithm
    */
    while(1)
    {
        if (ev3_button_is_pressed(BACK_BUTTON)) break;

        if ( sonarAlert.detectBarrier( 20 ) == 1 ) // 障害物検知
        {
            forward = turn = 0; // 障害物を検知したら停止
        }
        else
        {
            forward = 30; // 前進命令
            if ( colorSensor.getBrightness() >= (light_white + light_black)/2)
            {
                turn =  10; // 左旋回命令
            }
            else
            {
                turn = -10; // 右旋回命令
            }
        }

        walker.run( forward, turn );

        // if( isUpped ) {
        //     lifter.liftDown();
        //     isUpped = false;
        // } else {
        //     lifter.liftUp();
        //     isUpped = true;
        // }

        tslp_tsk(4); // 4msec周期起動
    }
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
