/******************************************************************************
 *  BalancerCpp.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Class Balancer
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "balancer.h"

#include "BalancerCpp.h"

/**
 * コンストラクタ
 */
Balancer::Balancer()
    : mForward(0),
      mTurn(0),
      mOffset(0),
      mRightPwm(0),
      mLeftPwm(0) {
}

/**
 * バランサを初期化する
 * @param offset ジャイロセンサオフセット値
 */
void Balancer::init(int offset) {
    mOffset = offset;
    balance_init();  // 倒立振子制御初期化
}

/**
 * バランサの値を更新する
 * @param angle   角速度
 * @param rwEnc   右車輪エンコーダ値
 * @param lwEnc   左車輪エンコーダ値
 * @param battety バッテリ電圧値
 */
void Balancer::update(int angle, int rwEnc, int lwEnc, int battery) {
    // 倒立振子制御APIを呼び出し、倒立走行するための
    // 左右モータ出力値を得る
    balance_control(
        static_cast<float>(mForward),
        static_cast<float>(mTurn),
        static_cast<float>(angle),
        static_cast<float>(mOffset),
        static_cast<float>(lwEnc),
        static_cast<float>(rwEnc),
        static_cast<float>(battery),
        &mLeftPwm,
        &mRightPwm);
}

/**
 * 前進値、旋回値を設定する
 * @param forward 前進値
 * @param turn    旋回値
 */
void Balancer::setCommand(int forward, int turn) {
    mForward = forward;
    mTurn    = turn;
}

/**
 * 右車輪のPWM値を取得する
 * @return 右車輪のPWM値
 */
int8_t Balancer::getPwmRight() {
    return mRightPwm;
}

/**
 * 左車輪のPWM値を取得する
 * @return 左車輪のPWM値
 */
int8_t Balancer::getPwmLeft() {
    return mLeftPwm;
}
