#include "Emoter.h"

Emoter::Emoter():
    tailHand(PORT_D) {
}

void Emoter::init() {
    init_f("Emoter");
}

void Emoter::terminate() {
    msg_f("Stopped.", 1);
    tailHand.stop();
}

void Emoter::reset() {
    tailHand.reset();
    tailHand.setBrake(true);
    tailHand.setBrake(false);
}

void Emoter::turn(int8_t pwm) {
    tailHand.setPWM(pwm);
}

void Emoter::wipe(int8_t pwm, int maxChange, int angle) {
    int i;

    if(angle < 10) {
        angle = 10;
    }
    angle /= 2;

    Emoter::defaultSet(0);

    tailHand.setPWM(pwm);
    for(i = 0; i < maxChange; i++) {
        while(1) {
            if(tailHand.getCount() > angle || tailHand.getCount() < -angle) {
                pwm = -pwm;
                tailHand.setPWM(pwm);
                clock.sleep(100);
                break;
            }
            clock.sleep(1);
        }
    }
    tailHand.setPWM(0);
    Emoter::defaultSet(0);
}

void Emoter::changeDefault(int angle) {
    Emoter::defaultSet(angle);
    Emoter::reset();
}

void Emoter::defaultSet(int angle) {
    int i = 0;
    for(i = 0; i < 300; i++) {
        tailHand.setPWM(-((tailHand.getCount() - angle) % 360));
        clock.sleep(1);
    }
    tailHand.setPWM(0);
    tailHand.setBrake(true);
}
