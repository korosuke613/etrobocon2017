/**
 * @file LeftCourse.cpp
 * @brief LeftCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "LeftCourse.h"

LeftCourse::LeftCourse():
#if IS_SHORT_CUT
    navi(walker.get_count_L(), walker.get_count_R())
#endif
    colorSensor( PORT_3 ), 
    sl(walker.get_count_L(), walker.get_count_R(), true){
}

void LeftCourse::setFirstCode( int32_t code ) {
    firstCode = code;
	codeConverter.setCode ( (int)firstCode ) ;
	codeConverter.resolvePositionCode();
	
	int colorPosition[5] ;
	colorPosition[0] = codeConverter.getPosition ( BlockColor::Black );
	colorPosition[1] = codeConverter.redToBlackPosition (codeConverter.getPosition ( BlockColor::Red ));
	colorPosition[2] = codeConverter.blueToBlackPosition (codeConverter.getPosition ( BlockColor::Blue ));
	colorPosition[3] = codeConverter.yellowToBlackPosition (codeConverter.getPosition ( BlockColor::Yellow ));
	colorPosition[4] = green ;
	
	targetFigure.set ( colorPosition ) ;
	targetFigure.evaluate () ;
	int targetAreaNum[5] ;
	targetAreaNum[0] = targetFigure.getTargetNum ( BlockColor::Black ) ;	
	targetAreaNum[1] = targetFigure.getTargetNum ( BlockColor::Red ) ;	
	targetAreaNum[2] = targetFigure.getTargetNum ( BlockColor::Blue ) ;	
	targetAreaNum[3] = targetFigure.getTargetNum ( BlockColor::Yellow ) ;	
	targetAreaNum[4] = targetFigure.getTargetNum ( BlockColor::Green ) ;	
	
	explorer.init(colorPosition);
	explorer.setTarget(targetAreaNum);
}

/**
 * Lコースの走行範囲の切り替えを行う
 */
void LeftCourse::run(){
    // Normal Area
    /* ショートカットする場合は外す
    //最初のまっすぐ
    runTyokusen(0.0, 0.0, -20.0, 1.0, true);
    //GATE2クリア
    runTyokusen(-20.0, 1.0, -80.0, 100.0, true);
    //GATE1クリア
    runTyokusen(-80.0, 100.0, -240.0, 101.0, true);
    //GATE1まっすぐ
    runTyokusen(-240.0, 101.0, -180.0, 100.0, false);
    //緑超え
    runTyokusen(-180.0, 100.0, -160.0, 180.0, false);
    //最後の直線
    runTyokusen(-141.0, 130.0, -160.0, 600.0, false);
    while(1){
        walker.run(10, 0);
        if(colorSensor.getBrightness() < 5)break;
    }
    */

	runNormalCourse();
    msg_f("Finished NormalArea", 3);
  
	// Puzzle
    runBlockRange();
    msg_f("Finished BlockRange", 3);
  
	// Park
    runParallelParking();
    msg_f("Finished ParallelParking", 3);
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

#if IS_SHORT_CUT
void LeftCourse::runTyokusen(float _start_x, float _start_y, float _goal_x, float _goal_y, bool _isBack){
    bool isEndAngle = false;
    int minus = 1;
    if(_isBack == true)minus = -1;
    
    navi.turnControl.wrapper_of_constructor(4.0, 0.5, 3.0, 0, 0, 0.0, 0); 
    navi.speedControl.wrapper_of_constructor(4.0, 2.0, 0.024, 0, 0, 210.0 * minus, 0);
    
    navi.setLine(_start_x, _start_y, _goal_x, _goal_y);
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
        navi.sl.update(walker.get_count_L(), walker.get_count_R());
        if(ev3_button_is_pressed(BACK_BUTTON)){
            walker.run(0, 0);
            break;
        }
        
        tslp_tsk(4); // 4msec周期起動
    }
    walker.run(0, 0);    
    tslp_tsk(100); // 4msec周期起動    
    ev3_speaker_play_tone (NOTE_FS6, 100);
}
#endif

void LeftCourse::runBlockRange(){
	PuzzleField puzzleField ;
	
	//puzzleField.testGame () ;
	puzzleField.runRoot () ;
}

void LeftCourse::runParallelParking(){
    Parking parking;
    parking.runParallel();
}
