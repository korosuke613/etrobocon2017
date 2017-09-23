/**
 * @file LeftCourse.cpp
 * @brief LeftCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "LeftCourse.h"

LeftCourse::LeftCourse():
    colorSensor( PORT_3 ), sl(walker.get_count_L(), walker.get_count_R(), true){
    
}

/**
 * Lコースの走行範囲の切り替えを行う
 */
void LeftCourse::run(){
    Navigation navi(walker.get_count_L(), walker.get_count_R());    
    runTyokusen(navi, 100.0, -100.0);
    runTyokusen(navi, 300.0, -110.0);
	//runNormalCourse();
  msg_f("Finish NormalCourse", 3);
	//Puzzle
  //PuzzleLineTracer puzzleLineTracer ;    
  //puzzleLineTracer.preparatePuzzle () ;
  //puzzleLineTracer.puzzleLineTrace ( 10, 0x00, 12 ) ;	// test
	//Park
}

void LeftCourse::runNormalCourse(){
   	LeftNormalCourse normalCourse;
	bool isNormalCourse;
    // NormalCourseを抜けるまでループする
	while ( 1 ) {
        sl.update(walker.get_count_L(), walker.get_count_R());
        if(normalCourse.statusCheck(walker.get_count_L(), walker.get_count_R())) ev3_speaker_play_tone (NOTE_FS6, 100);
        isNormalCourse = normalCourse.runNormalCourse(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness());
        
        if(normalCourse.lineTracerWalker.getForward() < 0){
            walker.run(0, 0);
        }else{
            walker.run( normalCourse.lineTracerWalker.getForward(), normalCourse.lineTracerWalker.getTurn());
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

void LeftCourse::runTyokusen(Navigation &navi, float _goal_x, float _goal_y){
    navi.turnControl.setPid(2.0, 0.0, 3.0, 0.0);    
    navi.setLine(navi.sl.getPointX(), navi.sl.getPointY(), _goal_x, _goal_y);
    // NormalCourseを抜けるまでループする
    while (navi.calculateValue(walker.get_count_L(), walker.get_count_R()) ) {
        //navi.calculateValue(walker.get_count_L(), walker.get_count_R());
        if(navi.getForward() < 0){
            walker.run(0, 0);
        }else{
            walker.run( navi.getForward(), navi.getTurn());
        }
        if(ev3_button_is_pressed(BACK_BUTTON)){
            walker.run(0, 0);
            navi.sl.file_close();
            break;
        }
        
        tslp_tsk(4); // 4msec周期起動
    }
    walker.run(0, 0);    
    ev3_speaker_play_tone (NOTE_FS6, 100);
}