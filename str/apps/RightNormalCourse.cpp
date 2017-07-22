#include "RightNormalCourse.h"

RightNormalCourse::RightNormalCourse(){
    lineTracer.isLeftsideLine(false);
    FILE *fp;

    if ((fp = fopen("test.csv", "w")) == NULL) {
            printf("file open error!!\n");
            return;
    }
    fprintf(fp, "light_value, speed, forward, turn\n");
    fclose(fp);
}

void RightNormalCourse::runNormalCourse(void){
    FILE *fp;
    if ((fp = fopen("test.csv", "a")) == NULL) {
        printf("file open error!!\n");
        return;
    }
	while ( 1 ) {

        forward = lineTracer.speedControl.calculateSpeedForPid();
        statusCheck();
		switch(status){
            case RightStatus::STRAIGHT: goStraight(forward); break;
            case RightStatus::CURVE_RIGHT: goCurveRight(forward); break;
            case RightStatus::STOP: stop(); break;

            default: goStraight(0);
        }
		lineTracer.runLine();
		if (ev3_button_is_pressed(BACK_BUTTON)) break;
        if (status == RightStatus::STOP) break;
        fprintf(fp, "%d, %d, %d, %d, %d\n",
        lineTracer.turnControl.getBrightness(),
        lineTracer.speedControl.speed_value_all, 
        forward,
        lineTracer.turn,
        (int)lineTracer.speedControl.get_output()
        );
	}

    fclose(fp);
}

void RightNormalCourse::statusCheck(){
    distanse_total = distance.getDistanceTotal();
    if(distanse_total < 3240)status = RightStatus::STRAIGHT;
    //else if(distanse_total < 6000)status = RightStatus::CURVE_RIGHT;
    //else if(distanse_total < 12000)status = RightStatus::STRAIGHT;
    else status = RightStatus::STOP;
}

void RightNormalCourse::goStraight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 2.0, 4.8, 0.024, 150.0 );
    lineTracer.turnControl.setPid ( 2.0, 0.5, 0.024, 40.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void RightNormalCourse::goCurveRight(int8_t forward_value){
    lineTracer.setForward(forward_value);
    lineTracer.speedControl.setPid ( 5.0, 0.5, 0.0, 150.0 );
    lineTracer.turnControl.setPid ( 2.0, 0.5, 0.024, 40.0 );
    char msg[32];
    sprintf(msg, "Speed_cm/s: %d", lineTracer.speedControl.speed_value_all); 
    msg_f(msg, 4);
}

void RightNormalCourse::stop(){
    lineTracer.setForward(0);
    char msg[32];
    sprintf(msg, "Brightness/s: %d", lineTracer.turnControl.getBrightness()); 
    msg_f(msg, 5);
}
