#include "Walker.h"

Walker::Walker():
    leftWheel(PORT_C), rightWheel(PORT_B) {
        reset();
}

void Walker::init() {
    init_f("Walker");
}

void Walker::terminate() {
    msg_f("Stopped.", 1);
    leftWheel.stop();
    rightWheel.stop();
}

void Walker::reset() {
    leftWheel.reset();
    rightWheel.reset();
}

void Walker::stop() {
    run(0, 0);

    msg_f("stopping...", 1);
    leftWheel.reset();
    rightWheel.reset();
}

void Walker::run(int8_t pwm, int8_t turn) {
    msg_f("running...", 1);
    setBrakeMotor(false);
    /* left = p-t, right = p+t -> 右 */
    /* left = p+t, right = p-t -> 左 */
    // pwmは int型の -100 ~ 100
    leftWheel.setPWM(pwm - turn);
    rightWheel.setPWM(pwm + turn);
}

void Walker::setBrakeMotor(bool brake){
    //0でフロート
    //1でブレーク
    leftWheel.setBrake(brake);
    rightWheel.setBrake(brake);
}

int32_t Walker::get_count_L() {
    return leftWheel.getCount();
}

int32_t Walker::get_count_R() {
    return rightWheel.getCount();
}

int Walker::edgeChange() {
    if(leftRight == 1) {
        run(10, 5);
        clock.sleep(10);
        leftRight = -1;
    } else {
        run(10, 5);
        clock.sleep(10);
        leftRight = 1;
    }

    return leftRight;
}

/*
 * 車輪の回転角分だけ進む
 */
void Walker::moveAngle(int8_t pwm, int angle) {

    leftWheel.reset();
    rightWheel.reset();

    leftWheel.setPWM(pwm);
    rightWheel.setPWM(pwm);

    while(1){
        if(leftWheel.getCount() >= angle && rightWheel.getCount() >= angle ) break;
        clock.sleep(4);
    }

    leftWheel.reset();
    rightWheel.reset();
}

/*
 * 主機能:45度単位で回転
 * rotation = 1 -> 反時計回り, rotation = -1 -> 時計回り
 *
 * beta機能:5度単位で回転
 * 精度はあまりよろしくない
 */
void Walker::angleChange(int angle, int rotation) {
    int32_t defaultAngleL;
    int8_t dAngle = 75; // 45度におけるモーター回転数（床材によって変わる？）

    if(rotation >= 0) {
        if(leftRight == 1) {
            rotation = 1;
        } else {
            rotation = -1;
        }
    } else {
        if(leftRight == 1) {
            rotation = -1;
        } else {
            rotation = 1;
        }
    }

    /*
     * 本来は45度単位だから、angleは45で割る
     * ベータ機能として5度単位でも曲がれるようにしている
     * そのため、もしangleが5度単位である場合はdAngleを9分割する
     */
    if(angle % 5 == 0 && angle % 45 != 0) {
        dAngle = 8;
        angle /= 5;
    } else {
        angle -= angle % 45;
        angle /= 45;
    }

    defaultAngleL = leftWheel.getCount();

    while(1) {
        run(0, 10 * rotation);
        if(rotation >= 0) {
            if(leftWheel.getCount() - defaultAngleL < -dAngle * angle * rotation ||
                leftWheel.getCount() - defaultAngleL > dAngle * angle * rotation) {
                break;
            }
        } else {
            if(leftWheel.getCount() - defaultAngleL > -dAngle * angle * rotation ||
                leftWheel.getCount() - defaultAngleL < dAngle * angle * rotation) {
                break;
            }
        }
        clock.sleep(4);
    }
    stop();
}
