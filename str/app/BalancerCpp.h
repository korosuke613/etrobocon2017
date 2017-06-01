/******************************************************************************
 *  BalancerCpp.h (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class Balancer
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef EV3_UNIT_BALANCERCPP_H_
#define EV3_UNIT_BALANCERCPP_H_

#include "ev3api.h"

class Balancer {
public:
    Balancer();

    void init(int offset);
    void update(int angle, int rwEnc, int lwEnc, int battery);
    void setCommand(int forward, int turn);
    int8_t getPwmRight();
    int8_t getPwmLeft();

private:
    int mForward;
    int mTurn;
    int mOffset;
    int8_t mRightPwm;
    int8_t mLeftPwm;
};

#endif  // EV3_UNIT_BALANCERCPP_H_
