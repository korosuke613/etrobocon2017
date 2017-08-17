/**
 * @file RightCourse.cpp
 * @brief RightCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "RightCourse.h"

RightCourse::RightCourse():
	 colorSensor( PORT_3 ){}

/**
 *Rコースの走行範囲の切り替えを行う
 */
void RightCourse::convertArea(){
	runNormalCourse();
	//Sinkansen
	//Park
}

void RightCourse::runShinkansen(){
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