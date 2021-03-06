/**
 * @file Shinkansen.cpp
 * @brief Shinkansenクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "Shinkansen.h"

Shinkansen::Shinkansen():
    time_counter(0),
    isInFrontOf(false), 
    TO_PASS(200),
    PASS_THRESHOLD(8),
    DISTANCE_THRESHOLD(30),
    colorSensor( PORT_3 ),
    leftWheel( PORT_C ),
    rightWheel( PORT_B ){

}

bool Shinkansen::checkPass(std::int16_t distance)
{
    if(isInFrontOf){
        time_counter++;
        // 新幹線を検知してからTO_PASS + PASS_THRESHOLD
        if(time_counter > TO_PASS + PASS_THRESHOLD){
            time_counter = 0;            
            isInFrontOf = false;
            return true;
        }
    }else{
        // 新幹線をDISTANCE_THRESHOLD連続で検知するとtime_counterを増やす
        if(distance <= DISTANCE_THRESHOLD){
            time_counter++;            
        }else{
            time_counter = 0;
        }
        // time_counterがPASS_THRESHOLDを超えると、新幹線がいると判断する
        if(time_counter > PASS_THRESHOLD){
            time_counter = 0;            
            isInFrontOf = true;            
        }
    }
    return false;    
}

void Shinkansen::runForward(double speed, int32_t targetDistance){
	int32_t distance_total;
	lineTracer.isLeftsideLine(false);
	lineTracer.setForward(30);
	distance.resetDistance(walker.get_count_L(), walker.get_count_R());
	lineTracer.speedControl.setPid ( 2.0, 1.0, 0.024, speed );
	lineTracer.turnControl.setPid ( 4.0, 2.0, 0.09, 20.0 );
	do{
		distance_total = distance.getDistanceCurrent(walker.get_count_L(), walker.get_count_R());
		lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness());
		walker.run( lineTracer.getForward(), lineTracer.getTurn());
		tslp_tsk(4);
	}while(distance_total < targetDistance);
	walker.run(0, 0);
}

void Shinkansen::runBackward(double speed, int32_t targetDistance){
	int32_t distance_total;
	lineTracer.isLeftsideLine(true);
	lineTracer.setForward(-30);
	distance.resetDistance(walker.get_count_L(), walker.get_count_R());
	lineTracer.speedControl.setPid ( 2.0, 1.0, 0.024, speed );
	lineTracer.turnControl.setPid ( 1.0, 1.0, 0.048, 10.0 );
	do{
		distance_total = distance.getDistanceCurrent(walker.get_count_L(), walker.get_count_R());
		lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness());
		walker.run( lineTracer.getForward(), lineTracer.getTurn());
		tslp_tsk(4);
	}while(distance_total > targetDistance);
	walker.run(0, 0);
}

void Shinkansen::spinBlack(int8_t forward, bool rotationalDirection){
	int32_t leftReverseValue, rightReverseValue;
	colorid_t lineColor = COLOR_NONE;
	basicWalker.spin(rotationalDirection, 45);
  // 古いバージョン
	// basicWalker.spin(forward, reverseValue, 45);
    int8_t reverseValue = rotationalDirection == basicWalker.SPIN_RIGHT
        ? -1
        :  1;
	int8_t value = reverseValue * -1;
	leftWheel.reset();
	rightWheel.reset();
	tslp_tsk(100);
	msg_f("Spin...", 2);
	leftWheel.setBrake(false);
	rightWheel.setBrake(false);
	leftReverseValue = value;
	rightReverseValue = value * -1;
	while(1){
		leftWheel.setPWM(forward * leftReverseValue);
		rightWheel.setPWM(forward * rightReverseValue);
		lineColor = colorSensor.getColorNumber();
		if(lineColor == COLOR_BLACK) break;
		tslp_tsk(2);
	}
	leftWheel.setPWM(0);
	rightWheel.setPWM(0);	
}

void Shinkansen::runColor(){
	lineTracer.isLeftsideLine(false);
	lineTracer.setForward(30);
	colorid_t lineColor = COLOR_NONE;
	lifter.liftDown();
	lifter.changeDefault(0);
	lineTracer.speedControl.setPid ( 2.0, 1.0, 0.024, 50.0 );
    lineTracer.turnControl.setPid ( 4.0, 1.0, 0.09, 20.0 );
    do{
    	lineTracer.runLine(walker.get_count_L(), walker.get_count_R(), colorSensor.getBrightness());
    	walker.run( lineTracer.getForward(), lineTracer.getTurn());
    	lineColor = colorSensor.getColorNumber();
    }while(lineColor != COLOR_BLUE && lineColor != COLOR_GREEN && lineColor != COLOR_YELLOW && lineColor != COLOR_RED);
	walker.run(0, 0);
	lineColor = COLOR_NONE;
}

void Shinkansen::colorDetection(){
	colorid_t circleColor, blockColor;
	int8_t count = 0;
	while(1){
		circleColor = colorSensor.getColorNumber();
		if(circleColor == COLOR_BLUE || circleColor == COLOR_GREEN || circleColor == COLOR_YELLOW || circleColor == COLOR_RED){
			ev3_speaker_play_tone (NOTE_FS6, 100);
			basicWalker.backStraight(50);
			lifter.changeDefault(60);
			blockColor = colorSensor.getColorNumber();
			while(blockColor != COLOR_BLUE && blockColor != COLOR_GREEN && blockColor != COLOR_YELLOW && blockColor != COLOR_RED){
				if(count > 10)break;
				basicWalker.goStraight(10, 10);
        		blockColor = colorSensor.getColorNumber();
				count++;
        	}
			lifter.changeDefault(-60);
			if(circleColor == blockColor){
				basicWalker.goStraight(10, 50);
				ev3_speaker_play_tone (NOTE_FS6, 100);
			}else{
				basicWalker.goStraight(10, 230 - 10 * count);
				basicWalker.backStraight(100);
        // 古いバージョン
				// basicWalker.backStraight(10, 100);
				ev3_speaker_play_tone (NOTE_FS6, 200);
				
			}
			lifter.liftDown();
    		lifter.changeDefault(0);
			break;
		}
	}
}

void Shinkansen::firstPattern(){
	spinBlack(30, basicWalker.SPIN_RIGHT);
	runColor();
	colorDetection();
	spinBlack(30, basicWalker.SPIN_RIGHT);
	runColor();
	colorDetection();
	spinBlack(30, basicWalker.SPIN_LEFT);
	runForward(10.0, 240);
	spinBlack(30, basicWalker.SPIN_LEFT);
	runForward(10.0, 440);
}

void Shinkansen::secondPattern(){
	spinBlack(30, basicWalker.SPIN_RIGHT);
	runColor();
	colorDetection();
	spinBlack(30, basicWalker.SPIN_LEFT);
	runColor();
	colorDetection();
	spinBlack(30, basicWalker.SPIN_RIGHT);
	runForward(10.0, 240);
	spinBlack(30, basicWalker.SPIN_LEFT);
}
