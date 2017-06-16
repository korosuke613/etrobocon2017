/**
 ******************************************************************************
 ** ファイル名 : app.c
 **
 ** 概要 : 2輪倒立振子ライントレースロボットのTOPPERS/HRP2用Cサンプルプログラム
 **
 ** 注記 : sample_c4 (sample_c3にBluetooth通信リモートスタート機能を追加)
 ******************************************************************************
 **/

#include "ev3api.h"
#include "app.h"
#include "app/Course.h"

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

static int  bluetooth_command = 0; // Bluetoothコマンド 1:リモートスタート
static FILE *bluetooth = NULL;     // Bluetoothファイルハンドル

/* メインタスク */
void main_task( intptr_t unused )
{
    /* Open Bluetooth file */
    bluetooth = ev3_serial_open_file( EV3_SERIAL_BT );
    assert( bluetooth != NULL );

    /* Bluetooth通信タスクの起動 */
    act_tsk( BT_TASK );

    Course course;
    course.start( bluetooth_command ); // HackEV起動

    ter_tsk( BT_TASK );
    fclose( bluetooth );

    ext_tsk();
}

//*****************************************************************************
// 関数名 : bt_task
// 引数 : unused
// 返り値 : なし
// 概要 : Bluetooth通信によるリモートスタート。 Tera Termなどのターミナルソフトから、
//       ASCIIコードで1を送信すると、リモートスタートする。
//*****************************************************************************
void bt_task( intptr_t unused )
{
    while( 1 )
    {
        uint8_t c = fgetc( bluetooth ); /* 受信 */
        switch( c )
        {
        case '1':
            bluetooth_command = 1;
            break;
        default:
            break;
        }
        fputc( c, bluetooth ); /* エコーバック */
    }
}
