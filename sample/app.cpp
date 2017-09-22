/**
 * ファイル名 : app.c
 *
 * 概要 : ETロボコンのTOPPERS/HRP2用Cサンプルプログラム
 *
 * 注記 : Bluetooth通信リモートスタート機能付き
 */

#include <string>
#include "ev3api.h"
#include "app.h"
#include "util.h"
#include "ColorSensor.h"
#include "TouchSensor.h"
#include "SonarSensor.h"

using namespace ev3api;

#if defined(BUILD_MODULE)
#include "module_cfg.h"
#else
#include "kernel_cfg.h"
#endif

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

static int  g_bluetooth_command = 0; // Bluetoothコマンド 1:リモートスタート
static FILE *g_bluetooth = NULL;     // Bluetoothファイルハンドル

/* メインタスク */
void main_task( intptr_t unused )
{
    /* Open Bluetooth file */
    g_bluetooth = ev3_serial_open_file( EV3_SERIAL_BT );
    assert( g_bluetooth != NULL );

    /* Bluetooth通信タスクの起動 */
    act_tsk( BT_TASK );


    msg_f("Check Colors", 1);
    msg_f(" create from github.com/korosuke613/etrobocon2017", 2);
    ColorSensor colorSensor(PORT_3);
    TouchSensor touchSensor(PORT_1);
    SonarSensor sonarSensor(PORT_2);
    int time_count = 0;
    char msg[32];
    int color_num;
    std::string color_name[8] = {"NONE", "BLACK", "BLUE", "GREEN", "YELLOW", "RED", "WHITE", "BROWN"};
    rgb_raw_t rgb;
    while(1){
        color_num = (int)colorSensor.getColorNumber();
        colorSensor.getRawColor( rgb );
        sprintf ( msg, "LightValue: %d", colorSensor.getBrightness());
        msg_f ( msg, 4 ) ;
        
        sprintf ( msg, "ColorNumber: %s", color_name[color_num].c_str());
        msg_f ( msg, 5 ) ;
        sprintf ( msg, "    R:%3d G:%3d B:%3d", rgb.r, rgb.g, rgb.b);
        msg_f ( msg, 6 ) ;

        sprintf ( msg, "DistanceEye: %d", sonarSensor.getDistance());
        msg_f ( msg, 7 );

        if(sonarSensor.getDistance() < 10){
            time_count++;
        }

        sprintf ( msg, "DistanceTime: %d", time_count);
        msg_f ( msg, 8 );
        
        if ( touchSensor.isPressed()== 1)
        {
            break; /* タッチセンサが押された */
        }
        tslp_tsk ( 4 ) ;        
    }

    ter_tsk( BT_TASK );
    fclose( g_bluetooth );

    ext_tsk();
}

/**
 * 概要 : Bluetooth通信によるリモートスタート。
 *        Tera Termなどのターミナルソフトから、
 *        ASCIIコードで1を送信すると、リモートスタートする。
 * 引数 : unused
 * 返り値 : なし
 */
void bt_task( intptr_t unused )
{
    while( 1 )
    {
        uint8_t c = fgetc( g_bluetooth ); /* 受信 */
        switch( c )
        {
        case '1':
            g_bluetooth_command = 1;
            break;
        default:
            break;
        }
        fputc( c, g_bluetooth ); /* エコーバック */
    }
}
