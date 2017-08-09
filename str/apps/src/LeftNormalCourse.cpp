#include "LeftNormalCourse.h"

LeftNormalCourse::LeftNormalCourse(){
    lineTracer.isLeftsideLine(true);
    old_status = LeftStatus::STRAIGHT;

    ev3_speaker_set_volume(100);
}

bool LeftNormalCourse::runNormalCourse(int32_t countL, int32_t countR){
    sl.update();
    sl.writing_current_coordinates();
    statusCheck(countL, countR);
    switch(status){
        case LeftStatus::STRAIGHT: goStraight(); break;
        case LeftStatus::STRAIGHT_SLOW: goStraightSlow(); break;
        case LeftStatus::CURVE_RIGHT: goCurveRight(); break;
        case LeftStatus::CURVE_LEFT_SHORT: goCurveLeftShort(); break;
        case LeftStatus::CURVE_LEFT: goCurveLeft(); break;
        case LeftStatus::STOP: stop(); break;
        default: stop();
    }
    if (ev3_button_is_pressed(BACK_BUTTON)) return false;
    if (status == LeftStatus::STOP) return false;
    return true;
}

void LeftNormalCourse::statusCheck(int32_t countL, int32_t countR){
    distanse_total = distance.getDistanceTotal(countL, countR);
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

void LeftNormalCourse::goStraight(){
    lineTracer.speedControl.setPid ( 2.0, 4.8, 0.024, 150.0 );
    lineTracer.turnControl.setPid ( 2.0, 1.0, 0.048, 40.0 );
}

void LeftNormalCourse::goStraightSlow(){
    lineTracer.speedControl.setPid ( 2.0, 2.0, 0.024, 120.0 );
    lineTracer.turnControl.setPid ( 2.0, 1.0, 0.048, 40.0 );
}

void LeftNormalCourse::goCurveRight(){
    lineTracer.speedControl.setPid ( 4.0, 0.8, 0.08, 100.0 );
    lineTracer.turnControl.setPid ( 4.0, 2.0, 0.1, 35.0 );
    //lineTracer.turnControl.setPid ( 4.0, 2.0, 0.096, 40.0 );
}

void LeftNormalCourse::goCurveLeftShort(){
    lineTracer.speedControl.setPid ( 4.0, 0.8, 0.1, 130.0 );
    lineTracer.turnControl.setPid ( 2.0, 0.5, 0.048, 35.0 );
}

void LeftNormalCourse::goCurveLeft(){
    lineTracer.speedControl.setPid ( 4.0, 0.8, 0.1, 100.0 );
    lineTracer.turnControl.setPid ( 4.0, 2.0, 0.096, 35.0 );
}

void LeftNormalCourse::stop(){
    lineTracer.setForward(0);
}