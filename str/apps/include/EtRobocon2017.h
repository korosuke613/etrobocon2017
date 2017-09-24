/**
 * @file EtRobocon2017.h
 * @brief main的なクラス
 * @author Futa HIRAKOBA
 */
#ifndef __ETROBOCON2017__
#define __ETROBOCON2017__

#include "ev3api.h"
#include "TouchSensor.h"
#include "SonarAlert.h"
#include "Lifter.h"
#include "Emoter.h"
#include "UserInterface.h"
#include "LeftCourse.h"
#include "RightCourse.h"
#include "basicWalker.h"


using namespace ev3api;

/**
* main的なクラス
*/
class EtRobocon2017 {
public:
    /** コンストラクタ。各センサー等の初期化を行う */
    EtRobocon2017();
    /** タッチセンサが押されたときに行われる処理 */
    void start( int );
    /** スイッチを入れたときに行われる処理 */
    void waitStarter( int );
    /** 実際にマシンを動かすときの処理 */
    void loop();

private:
    TouchSensor touchSensor;
    int8_t light_white;
    int8_t light_black;
    int32_t firstCode;
    LeftCourse leftCourse;    
    RightCourse rightCourse;
    UserInterface ui;
};

#endif
