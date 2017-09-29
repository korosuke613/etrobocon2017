/**
 * @file RightCourse.cpp
 * @brief RightCourseクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */
#include "RightCourse.h"

RightCourse::RightCourse():
     colorSensor( PORT_3 ), 
     sonarSensor( PORT_2 ),
     shinkansenStatus(ShinkansenStatus::BEFORE_FIRST_SHINKANSEN),
     sl(walker.get_count_L(), walker.get_count_R()){
}

/**
 *Rコースの走行範囲の切り替えを行う
 */
void RightCourse::run(){
	runNormalCourse();
    runShinkansen();
	//Park
}

void RightCourse::runShinkansen(){
    int16_t distance_shinkansen;    
    Shinkansen shinkansen;
    lineTracer.isLeftsideLine(false);
    while(1){
        distance_shinkansen = sonarSensor.getDistance();
        
        switch(shinkansenStatus){
            //新幹線が通るまで待つ処理
            case ShinkansenStatus::BEFORE_FIRST_SHINKANSEN:
                if(shinkansen.checkPass(distance_shinkansen)){
                    ev3_speaker_play_tone (NOTE_FS6, 100);
                    shinkansenStatus = ShinkansenStatus::FIRST_RAIL;
                }
                break;
            case ShinkansenStatus::FIRST_RAIL:
        		shinkansen.runForward(180.0, 500);
                shinkansenStatus = ShinkansenStatus::FIRST_LINE;
                ev3_speaker_play_tone (NOTE_FS6, 100);
                break;
            case ShinkansenStatus::FIRST_LINE:
        		shinkansen.firstPattern();
                ev3_speaker_play_tone (NOTE_FS6, 100);
                shinkansenStatus = ShinkansenStatus::SECOND_LINE;
                break;
            case ShinkansenStatus::SECOND_LINE:
        		shinkansen.secondPattern();
                ev3_speaker_play_tone (NOTE_FS6, 100);
                shinkansenStatus = ShinkansenStatus::BEFORE_SECOND_SHINKANSEN;
                break;
        	case ShinkansenStatus::BEFORE_SECOND_SHINKANSEN:
                if(shinkansen.checkPass(distance_shinkansen)){
                    ev3_speaker_play_tone (NOTE_FS6, 100);
                    shinkansenStatus = ShinkansenStatus::SECOND_RAIL;
                }
                break;
        	case ShinkansenStatus::SECOND_RAIL:
        		shinkansen.runForward(70.0, 500);
                shinkansenStatus = ShinkansenStatus::THIRD_LINE;
                ev3_speaker_play_tone (NOTE_FS6, 100);
                break;
        case ShinkansenStatus::THIRD_LINE:
        		shinkansen.firstPattern();
                ev3_speaker_play_tone (NOTE_FS6, 100);
                shinkansenStatus = ShinkansenStatus::FOURTH_LINE;
                break;
        	case ShinkansenStatus::FOURTH_LINE:
        		shinkansen.secondPattern();
                ev3_speaker_play_tone (NOTE_FS6, 100);
                shinkansenStatus = ShinkansenStatus::BEFORE_THIRD_SHINKANSEN;
                break;
        	case ShinkansenStatus::BEFORE_THIRD_SHINKANSEN:
                if(shinkansen.checkPass(distance_shinkansen)){
                    ev3_speaker_play_tone (NOTE_FS6, 100);
                    shinkansenStatus = ShinkansenStatus::PRIZE;
                }
                break;
        	case ShinkansenStatus::PRIZE:
        		basicWalker.backStraight(230);
        		basicWalker.spin(basicWalker.SPIN_RIGHT, 90);
            // 古いバージョン
        		//basicWalker.backStraight(10, 230);
        		//basicWalker.spin(10, basicWalker.SPIN_RIGHT, 90);
        		lifter.liftDown();
        		lifter.reset();
        		lifter.defaultSet(-10);
        		walker.reset();
        		walker.run(10, 0);
        		do{
        			distance_shinkansen = sonarSensor.getDistance();
        			tslp_tsk(4);
        		}while(distance_shinkansen > 10);
        		walker.run(0, 0);
        		basicWalker.goStraight(10, 100);
        		lifter.changeDefault(40);
        		lifter.defaultSet(40);
        		basicWalker.backStraight(400);
        		basicWalker.spin(basicWalker.SPIN_LEFT, 90);
            // 古いバージョン
        		//basicWalker.backStraight(10, 400);
        		//basicWalker.spin(10, basicWalker.SPIN_LEFT, 90);
        		basicWalker.goStraight(40, 800);
        		lifter.liftUp();
        		basicWalker.spin(basicWalker.SPIN_RIGHT, 90);
        		//basicWalker.spin(30, basicWalker.SPIN_RIGHT, 90);
				basicWalker.goStraight(10, 180);
        		lifter.changeDefault(-10);
        		basicWalker.backStraight(200);
        		//basicWalker.backStraight(10, 200);
        		shinkansen.spinBlack(30, basicWalker.SPIN_LEFT);
        		lifter.liftDown();
        		lifter.changeDefault(0);
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
}

void RightCourse::runNormalCourse(){
	RightNormalCourse normalCourse;
    bool isNormalCourse;
    // NormalCourseを抜けるまでループする
	while ( 1 ) {
        sl.update(walker.get_count_L(), walker.get_count_R());
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

void RightCourse::runParpendicularParking(){
    Parking parking;
    parking.runParpendicular();
}
