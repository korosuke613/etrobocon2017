#include "RightNormalCourse.h"

RightNormalCourse::RightNormalCourse(){
    lineTracer.isLeftsideLine(false);
    old_status = RightStatus::STRAIGHT;

    ev3_speaker_set_volume(100);
    FILE *fp;

    if ((fp = fopen("test.csv", "w")) == NULL) {
            printf("file open error!!\n");
            return;
    }
    fprintf(fp, "light_value, speed, forward, turn, speedPid, TurnPid\n");
    fclose(fp);
}

void RightNormalCourse::runNormalCourse(void){
    FILE *fp;
    if ((fp = fopen("test.csv", "a")) == NULL) {
        printf("file open error!!\n");
        return;
    }
	while ( 1 ) {
        sl.update();
        sl.writing_current_coordinates();
        forward = lineTracer.speedControl.calculateSpeedForPid(walker.get_count_L(), walker.get_count_R());
        statusCheck();
		switch(status){
            case RightStatus::STRAIGHT: goStraight(forward); break;
            case RightStatus::CURVE_RIGHT: goCurveRight(forward); break;
            case RightStatus::CURVE_LEFT_SHORT: goCurveLeftShort(forward); break;
            case RightStatus::CURVE_LEFT: goCurveLeft(forward); break;
            case RightStatus::STOP: stop(); break;

            default: goStraight(0);
        }
		lineTracer.runLine();
		if (ev3_button_is_pressed(BACK_BUTTON)) break;
        if (status == RightStatus::STOP) break;
        fprintf(fp, "%d, %d, %d, %d, %d\n",
        lineTracer.speedControl.speed_value_all, 
        forward,
        lineTracer.turn,
        (int)lineTracer.speedControl.get_output(),
        (int)lineTracer.turnControl.get_output()
        );
	}

    fclose(fp);
}

void RightNormalCourse::statusCheck(){
    distanse_total = distance.getDistanceTotal(walker.get_count_L(), walker.get_count_R());
    if(distanse_total < 3240)status = RightStatus::STRAIGHT;
    else if(distanse_total < 7500)status = RightStatus::CURVE_RIGHT;
    else if(distanse_total < 9200)status = RightStatus::CURVE_LEFT_SHORT;
    else if(distanse_total < 10800)status = RightStatus::CURVE_LEFT;
    else if(distanse_total < 12800)status = RightStatus::CURVE_RIGHT;
    else if(distanse_total < 16000)status = RightStatus::STRAIGHT;
    else status = RightStatus::STOP;
    if(old_status != status) ev3_speaker_play_tone (NOTE_FS6, 100);
    old_status = status;
}

void RightNormalCourse::goStraight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 2.0, 4.8, 0.024, 150.0 );
    lineTracer.turnControl.setPid ( 2.0, 1.0, 0.048, 40.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void RightNormalCourse::goCurveRight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 2.0, 4.8, 0.024, 150.0 );
    lineTracer.turnControl.setPid ( 4.0, 2.0, 0.09, 40.0 );
    //lineTracer.turnControl.setPid ( 4.0, 2.0, 0.096, 40.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void RightNormalCourse::goCurveLeftShort(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 4.0, 0.8, 0.1, 130.0 );
    lineTracer.turnControl.setPid ( 2.0, 0.5, 0.048, 35.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void RightNormalCourse::goCurveLeft(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 4.0, 0.8, 0.1, 100.0 );
    lineTracer.turnControl.setPid ( 4.0, 2.0, 0.096, 35.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void RightNormalCourse::stop(){
    lineTracer.setForward(0);
}
