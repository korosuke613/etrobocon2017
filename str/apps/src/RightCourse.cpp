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

void RightCourse::runColor(){
	lineTracer.setForward(10);
	colorid_t lineColor = COLOR_NONE;
	lifter.liftDown();
    lifter.changeDefault(5);
    do{
    	lineTracer.speedControl.setPid ( 2.0, 4.8, 0.024, 100.0 );
    	lineTracer.turnControl.setPid ( 2.0, 1.0, 0.048, 18.0 );
    	lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness());
    	walker.run( lineTracer.getForward(), lineTracer.getTurn());
    	lineColor = colorSensor.getColorNumber();
    }while(lineColor != COLOR_BLUE && lineColor != COLOR_GREEN && lineColor != COLOR_YELLOW && lineColor != COLOR_RED);
	walker.run(0, 0);
	lineColor = COLOR_NONE;
}

void RightCourse::colorDetection(){
	colorid_t circleColor, blockColor;
	int8_t count = 0;
	while(1){
		circleColor = colorSensor.getColorNumber();
		if(circleColor == COLOR_BLUE || circleColor == COLOR_GREEN || circleColor == COLOR_YELLOW || circleColor == COLOR_RED){
			ev3_speaker_play_tone (NOTE_FS6, 100);
			basicWalker.backStraight(10, 50);
			lifter.changeDefault(60);
			blockColor = colorSensor.getColorNumber();
			lifter.changeDefault(15);
			while(blockColor == COLOR_BLACK || blockColor == COLOR_NONE){
				if(count > 5)break;
				basicWalker.goStraight(10, 10);
        		blockColor = colorSensor.getColorNumber();
				count++;
        	}
			lifter.changeDefault(-75);
			if(circleColor == blockColor){
				basicWalker.goStraight(10, 50);
				ev3_speaker_play_tone (NOTE_FS6, 100);
			}else{
				basicWalker.goStraight(10, 190 - 10 * count);
				basicWalker.backStraight(10, 140);
				ev3_speaker_play_tone (NOTE_FS6, 200);
				
			}
			break;
		}
	}
}

void RightCourse::runShinkansen(){
    int16_t distance_shinkansen;    
    Shinkansen shinkansen;
    lineTracer.isLeftsideLine(false);
	int32_t distance_total;
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
        		distance.resetDistance(walker.get_count_L(), walker.get_count_R());
                basicWalker.goStraight(40, 500);
                shinkansenStatus = ShinkansenStatus::FIRST_LINE;
                ev3_speaker_play_tone (NOTE_FS6, 100);
                break;
            case ShinkansenStatus::FIRST_LINE:
                basicWalker.spin(30, SPIN_RIGHT, 90);
        		runColor();
        		colorDetection();
        		basicWalker.spin(30, SPIN_RIGHT, 160);
        		runColor();
        		colorDetection();
        		basicWalker.spin(30, SPIN_LEFT, 170);
        		distance.resetDistance(walker.get_count_L(), walker.get_count_R());
        		do{
        			distance_total = distance.getDistanceCurrent(walker.get_count_L(), walker.get_count_R());
        			lineTracer.speedControl.setPid ( 2.0, 4.8, 0.024, 5.0 );
    				lineTracer.turnControl.setPid ( 2.0, 1.0, 0.048, 18.0 );
    				lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness());
    				walker.run( lineTracer.getForward(), lineTracer.getTurn());
        		}while(distance_total < 100);
        		walker.run(0, 0);
        		basicWalker.spin(30, SPIN_LEFT, 90);
        		basicWalker.goStraight(30, 400);
                ev3_speaker_play_tone (NOTE_FS6, 100);
                shinkansenStatus = ShinkansenStatus::FIRST_RIGHT_ANGLE;
                break;
            case ShinkansenStatus::FIRST_RIGHT_ANGLE:
                shinkansenStatus = ShinkansenStatus::PRIZE;
                break;
        	case ShinkansenStatus::PRIZE:
        		/*basicWalker.backStraight(10, 230);
        		basicWalker.spin(10, SPIN_RIGHT, 90);
        		lifter.liftDown();
        		lifter.changeDefault(-10);
        		basicWalker.goStraight(10, 400);
        		lifter.changeDefault(40);
        		lifter.changeDefault(40);
        		basicWalker.backStraight(10, 400);
        		basicWalker.spin(10, SPIN_LEFT, 90);
        		basicWalker.goStraight(10, 730);
        		basicWalker.spin(10, SPIN_RIGHT, 90);
				basicWalker.goStraight(10, 400);
        		lifter.changeDefault(-80);
        		basicWalker.backStraight(10, 400);
        		basicWalker.spin(10, SPIN_LEFT);*/
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