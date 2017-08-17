/**
 * @file RightCourse.cpp
 * @brief RightCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "RightCourse.h"

RightCourse::RightCourse():
	 colorSensor( PORT_3 ), sonarSensor( PORT_2 ){}

/**
 *Rコースの走行範囲の切り替えを行う
 */
void RightCourse::convertArea(){
	//runNormalCourse();
    runShinkansen();
    //Park
}

void RightCourse::runShinkansen(){
    int16_t distance;    
    Shinkansen shinkansen;
    char msg[32];
    msg_f("Not passed", 4);            
    while(1){
        distance = sonarSensor.getDistance();
        sprintf(msg, "Distance: %d", distance); 
        msg_f(msg, 5);
        if(shinkansen.checkPass(distance)){
            ev3_speaker_play_tone (NOTE_FS6, 100);
            msg_f("Has Has Has passed", 4);                        
        }
        tslp_tsk(4); // 4msec周期起動      
    }
    //新幹線が通るまで待つ処理
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