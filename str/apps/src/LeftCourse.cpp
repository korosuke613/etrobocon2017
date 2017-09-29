/**
 * @file LeftCourse.cpp
 * @brief LeftCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "LeftCourse.h"

LeftCourse::LeftCourse():
    colorSensor( PORT_3 ), 
    sl(walker.get_count_L(), walker.get_count_R(), true),
    navi(walker.get_count_L(), walker.get_count_R()){
    
}

/**
 * Lコースの走行範囲の切り替えを行う
 */
void LeftCourse::run(){
    /*runTyokusen(-80.0, 90.0, true);
    runTyokusen(-270.0, 60.0, true);
    runTyokusen(-200.0, 70.0, false);
    runTyokusen(-180.0, 100.0, false);
    runTyokusen(-120.0, 400.0, false);
    */
	runNormalCourse();
    msg_f("Finish NormalCourse", 3);
	//Puzzle
    PuzzleLineTracer puzzleLineTracer ;    
    puzzleLineTracer.preparatePuzzle () ;
    puzzleLineTracer.puzzleLineTrace ( 10, 0x00, 12 ) ;	// test
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

void LeftCourse::runTyokusen(float _goal_x, float _goal_y, bool _isBack){
    bool isEndAngle = false;
    int minus = 1;
    if(_isBack == true)minus = -1;
    
    navi.turnControl.wrapper_of_constructor(4.0, 0.5, 3.0, 0, 0, 0.0, 0); 
    navi.speedControl.wrapper_of_constructor(4.0, 2.0, 0.024, 0, 0, 210.0 * minus, 0);
    
    navi.setLine(navi.sl.getPointX(), navi.sl.getPointY(), _goal_x, _goal_y);
    navi.getDiffLine(navi.sl.getPointX(), navi.sl.getPointY());    
    navi.calculate_line_angle(_isBack);
    navi.sl.init_normal_vector(navi.start_x, navi.start_y, navi.goal_x, navi.goal_y, navi.current_x, navi.current_y);    
    // NormalCourseを抜けるまでループする
    while (!navi.sl.is_over_normal_vector(navi.current_x, navi.current_y)) {
        //navi.calculateValue(walker.get_count_L(), walker.get_count_R());
        if(! isEndAngle){
            isEndAngle = navi.calculateAngle(walker.get_count_L(), walker.get_count_R(), _isBack);
        }else{
            navi.calculateValue(walker.get_count_L(), walker.get_count_R(), _isBack);
        }
        walker.run(navi.getForward(), navi.getTurn());
        if(ev3_button_is_pressed(BACK_BUTTON)){
            walker.run(0, 0);
            break;
        }
        
        tslp_tsk(4); // 4msec周期起動
    }
    walker.run(0, 0);    
    ev3_speaker_play_tone (NOTE_FS6, 100);
}