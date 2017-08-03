#include "LeftNormalCourse.h"

LeftNormalCourse::LeftNormalCourse(){
    lineTracer.isLeftsideLine(true);
    old_status = LeftStatus::STRAIGHT;

    ev3_speaker_set_volume(100);
    FILE *fp;

    if ((fp = fopen("test_left.csv", "w")) == NULL) {
            printf("file open error!!\n");
            return;
    }
    fprintf(fp, "light_value, speed, forward, turn, speedPid, TurnPid\n");
    fclose(fp);
}

void LeftNormalCourse::runNormalCourse(void){
    FILE *fp;
    if ((fp = fopen("test_left.csv", "a")) == NULL) {
        printf("file open error!!\n");
        return;
    }
	while ( 1 ) {
        sl.update();
        sl.writing_current_coordinates();
        forward = lineTracer.speedControl.calculateSpeedForPid(walker.get_count_L(), walker.get_count_R());
        statusCheck();
		switch(status){
            case LeftStatus::STRAIGHT: goStraight(forward); break;
            case LeftStatus::STRAIGHT_SLOW: goStraightSlow(forward); break;
            case LeftStatus::CURVE_RIGHT: goCurveRight(forward); break;
            case LeftStatus::CURVE_LEFT_SHORT: goCurveLeftShort(forward); break;
            case LeftStatus::CURVE_LEFT: goCurveLeft(forward); break;
            case LeftStatus::STOP: stop(); break;
            default: goStraight(0);
        }
		lineTracer.runLine();
		if (ev3_button_is_pressed(BACK_BUTTON)) break;
        if (status == LeftStatus::STOP) break;
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

void LeftNormalCourse::statusCheck(){
    distanse_total = distance.getDistanceTotal();
    if(distanse_total < 2740)status = LeftStatus::STRAIGHT;
    else if(distanse_total < 3240)status = LeftStatus::STRAIGHT_SLOW;
    else if(distanse_total < 5200)status = LeftStatus::CURVE_RIGHT;
    else if(distanse_total < 7500)status = LeftStatus::CURVE_LEFT_SHORT;
    else if(distanse_total < 11000)status = LeftStatus::CURVE_LEFT;
    else if(distanse_total < 12200)status = LeftStatus::CURVE_RIGHT;
    else if(distanse_total < 15500)status = LeftStatus::STRAIGHT;
    else status = LeftStatus::STOP;
    if(old_status != status) ev3_speaker_play_tone (NOTE_FS6, 100);
    old_status = status;
}

void LeftNormalCourse::goStraight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 2.0, 4.8, 0.024, 150.0 );
    lineTracer.turnControl.setPid ( 2.0, 1.0, 0.048, 40.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void LeftNormalCourse::goStraightSlow(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 2.0, 2.0, 0.024, 120.0 );
    lineTracer.turnControl.setPid ( 2.0, 1.0, 0.048, 40.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void LeftNormalCourse::goCurveRight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 4.0, 0.8, 0.08, 100.0 );
    lineTracer.turnControl.setPid ( 4.0, 2.0, 0.1, 35.0 );
    //lineTracer.turnControl.setPid ( 4.0, 2.0, 0.096, 40.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void LeftNormalCourse::goCurveLeftShort(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 4.0, 0.8, 0.1, 130.0 );
    lineTracer.turnControl.setPid ( 2.0, 0.5, 0.048, 35.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void LeftNormalCourse::goCurveLeft(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 4.0, 0.8, 0.1, 100.0 );
    lineTracer.turnControl.setPid ( 4.0, 2.0, 0.096, 35.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void LeftNormalCourse::stop(){
    lineTracer.setForward(0);
}