/**
 * @file LeftCourse.cpp
 * @brief LeftCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "LeftCourse.h"

LeftCourse::LeftCourse():
	 colorSensor( PORT_3 ){}

/**
 * Lコースの走行範囲の切り替えを行う
 */
void LeftCourse::convertArea(){
	runNormalCourse();
	//Puzzle
	//Park
}

void LeftCourse::runNormalCourse(){
   	LeftNormalCourse normalCourse;
	bool isNormalCourse;
    // NormalCourseを抜けるまでループする
	while ( 1 ) {
        sl.update();
        sl.writing_current_coordinates();
        if(normalCourse.statusCheck(walker.get_count_L(), walker.get_count_R())) ev3_speaker_play_tone (NOTE_FS6, 100);
        isNormalCourse = normalCourse.runNormalCourse(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness());
        
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