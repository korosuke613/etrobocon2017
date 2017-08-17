/**
 * @file RightCourse.cpp
 * @brief RightCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "RightCourse.h"

RightCourse::RightCourse():
     colorSensor( PORT_3 ), 
     sonarSensor( PORT_2 ),
     shinkansenStatus(ShinkansenStatus::BEFORE_SHINKANSEN){
}

/**
 *Rコースの走行範囲の切り替えを行う
 */
void RightCourse::convertArea(){
	//runNormalCourse();
    runShinkansen();
    //Park
}

void RightCourse::runShinkansen(){
    int16_t distance_shinkansen;    
    Shinkansen shinkansen;
    LineTracer lineTracer;
    lineTracer.isLeftsideLine(false);
    int16_t time_count = 0;
    while(1){
        distance_shinkansen = sonarSensor.getDistance();
        
        switch(shinkansenStatus){
            //新幹線が通るまで待つ処理
            case ShinkansenStatus::BEFORE_SHINKANSEN:
                if(shinkansen.checkPass(distance_shinkansen)){
                    ev3_speaker_play_tone (NOTE_FS6, 100);
                    shinkansenStatus = ShinkansenStatus::FIRST_RAIL;
                }
                break;
            case ShinkansenStatus::FIRST_RAIL:
                walker.moveAngle(10, 200);
                shinkansenStatus = ShinkansenStatus::FIRST_LINE;
                ev3_speaker_play_tone (NOTE_FS6, 100);
                distance.resetDistance(walker.get_count_L(), walker.get_count_R());
                break;
            case ShinkansenStatus::FIRST_LINE:
                lineTracer.speedControl.setPid ( 4.0, 0.8, 0.1, 20.0 );
                lineTracer.turnControl.setPid ( 2.0, 1.0, 0.048, 20.0 );
                lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness());
                lineTracer.setTurn(lineTracer.turnControl.calculateTurnForPid(50, colorSensor.getBrightness())*lineTracer.minus);
                if(lineTracer.getForward() < 0){
                    walker.run(0, 0);
                }else{
                    walker.run( lineTracer.getForward(), lineTracer.getTurn());
                }
                if(distance.getDistanceCurrent(walker.get_count_L(), walker.get_count_R()) > 300){
                    ev3_speaker_play_tone (NOTE_FS6, 100);                
                    shinkansenStatus = ShinkansenStatus::FIRST_RIGHT_ANGLE;
                }
                time_count++;
                break;
            case ShinkansenStatus::FIRST_RIGHT_ANGLE:
                walker.angleChange(90, -1);
                shinkansenStatus = ShinkansenStatus::STOP;
                break;
            case ShinkansenStatus::STOP:
                break;
            default:
                break;
        }

        if(ev3_button_is_pressed(BACK_BUTTON) || shinkansenStatus == ShinkansenStatus::STOP){
            walker.run(0, 0);
            break;
        }
        tslp_tsk(4); // 4msec周期起動      
    }
    //新幹線が通った後クロスのところまで行く処理
    //90度回転させる処理
    //腕を少し上げる処理
    //進む処理
    //ブロックの手前で止まる処理
    //色を見る処理
}

void RightCourse::runNormalCourse(){
	RightNormalCourse normalCourse;
    bool isNormalCourse;
    /** 自己位置推定 インスタンス 初期化*/
    SelfLocalization sl;
    // NormalCourseを抜けるまでループする
	while ( 1 ) {
        sl.update();
        sl.writing_current_coordinates();
        if(normalCourse.statusCheck(walker.get_count_L(), walker.get_count_R())) ev3_speaker_play_tone (NOTE_FS6, 100);
        isNormalCourse = normalCourse.runNormalCourse();
        normalCourse.lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness());
        
        if(normalCourse.lineTracer.getForward() < 0){
            walker.run(0, 0);
        }else{
            walker.run( normalCourse.lineTracer.getForward(), normalCourse.lineTracer.getTurn());
        }
        if(! isNormalCourse){
            walker.run(0, 0);
            break;
        }
        if(ev3_button_is_pressed(BACK_BUTTON)){
            walker.run(0, 0);
            break;
        }
        
        tslp_tsk(4); // 4msec周期起動
    }
}