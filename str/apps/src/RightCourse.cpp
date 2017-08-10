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

void RightCourse::runNormalCourse(){
	RightNormalCourse normalCourse;
	bool isNormalCourse;
    // 左レーン時
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