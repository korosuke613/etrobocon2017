/**
 * ファイル名 : app.c
 *
 * 概要 : ETロボコンのTOPPERS/HRP2用Cサンプルプログラム
 *
 * 注記 : Bluetooth通信リモートスタート機能付き
 */

#include "ev3api.h"
#include "app.h"
#include "util.h"
#include "EtRobocon2017.h" // ETロボコン2017
#include "SelfLocalization.h"

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


    msg_f("ET-Robocon2017 Hirakobasample", 1);
    msg_f(" create from github.com/korosuke613/etrobocon2017", 2);

    EtRobocon2017 etrobocon;
    etrobocon.start( g_bluetooth_command );



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
