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
	//colorDetection();
	//Park
}

void RightCourse::colorDetection(){
	Lifter lifter;
	colorid_t circleColor, blockColor;
	while(1){
		circleColor = colorSensor.getColorNumber();
		if(circleColor == COLOR_BLUE || circleColor == COLOR_GREEN || circleColor == COLOR_YELLOW || circleColor == COLOR_RED){
			ev3_speaker_play_tone (NOTE_FS6, 100);
			basicwalker.backStraight(-10, -35);
			lifter.changeDefault(60);
			blockColor = colorSensor.getColorNumber();
			lifter.changeDefault(-60);
			if(circleColor == blockColor){
				ev3_speaker_play_tone (NOTE_FS6, 100);
			}else{
				ev3_speaker_play_tone (NOTE_FS6, 200);
				
			}
			break;
		}
	}
}

void RightCourse::runShinkansen(){
    int16_t distance_shinkansen;    
    Shinkansen shinkansen;
	LineTracerWalker lineTracer;
    lineTracer.isLeftsideLine(false);
    int16_t time_count = 0;
	colorid_t lineColor = COLOR_NONE;
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
                //basicwalker.goStraight(40, 500);
                shinkansenStatus = ShinkansenStatus::FIRST_LINE;
                //ev3_speaker_play_tone (NOTE_FS6, 100);
                //distance.resetDistance(walker.get_count_L(), walker.get_count_R());
                break;
            case ShinkansenStatus::FIRST_LINE:
                /*basicwalker.spinRightAngle(30, SPIN_LEFT);
        		//do{
        			basicwalker.goStraight(30, 200);
        			lineColor = colorSensor.getColorNumber();
        		//}while(lineColor != COLOR_BLUE && lineColor != COLOR_GREEN && lineColor != COLOR_YELLOW && lineColor != COLOR_RED);
        		lineColor = COLOR_NONE;
        		basicwalker.spinRightAngle(30, SPIN_LEFT);
        		basicwalker.spinRightAngle(30, SPIN_LEFT);
        		//do{
        			basicwalker.goStraight(30, 400);
        			lineColor = colorSensor.getColorNumber();
        		//}while(lineColor != COLOR_BLUE && lineColor != COLOR_GREEN && lineColor != COLOR_YELLOW && lineColor != COLOR_RED);
        		lineColor = COLOR_NONE;
        		basicwalker.spinRightAngle(30, SPIN_RIGHT);
        		basicwalker.spinRightAngle(30, SPIN_RIGHT);*/
        		basicwalker.goStraight(30, 200);
        		basicwalker.spinRightAngle(30, SPIN_RIGHT);
        		basicwalker.goStraight(30, 400);
                ev3_speaker_play_tone (NOTE_FS6, 100);
                shinkansenStatus = ShinkansenStatus::FIRST_RIGHT_ANGLE;
                break;
            case ShinkansenStatus::FIRST_RIGHT_ANGLE:
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
        normalCourse.lineTracerWalker.runLine(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness());
        
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