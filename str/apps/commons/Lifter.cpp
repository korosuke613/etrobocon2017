#include "Lifter.h"

Lifter::Lifter():
    liftHand(PORT_A) {
        liftHand.reset();
}

void Lifter::init() {
    init_f("Lifter");
}

void Lifter::terminate() {
    msg_f("Stopped.", 1);
    liftHand.stop();
}

void Lifter::reset() {
    liftHand.reset();
    liftHand.setBrake(true);
    liftHand.setBrake(false);
}

void Lifter::liftUp() {
    liftHand.setPWM(20);
    clock.sleep(1000);
    liftHand.setBrake(true);
}

void Lifter::liftDown() {
    liftHand.setPWM(-20);
    clock.sleep(1000);
    liftHand.setBrake(true);
}

void Lifter::changeDefault(int angle) {
    Lifter::defaultSet(angle);
    Lifter::reset();
}

void Lifter::defaultSet(int angle) {
    int i = 0;
    for(i = 0; i < 300; i++) {
        liftHand.setPWM(-((liftHand.getCount() - angle) % 360));
        clock.sleep(1);
    }
    liftHand.setPWM(0);
    liftHand.setBrake(true);
}
