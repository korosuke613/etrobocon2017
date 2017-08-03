/*****************************
 * self_localization.cpp
 *
 * Author Hiroki Tachiyama
 * Katayama Laboratory
 * Department of Computer Secience and Systems Engineering
 * Faculty of Engineering, University of Miyazaki
 *
 * Created at: Mon Jul 10 3:34:25 JST 2017
 *
 * Coryrights (c) 2017 Katayama Laboratory
 *
 *****************************/
#include "SelfLocalization.h"

SelfLocalization::SelfLocalization () {
  //車輪モーターのカウントの初期化は、
  //他の場所に影響を与える可能性があるので、コメントアウト
  //本当はした方が良い？
  //ev3_motor_reset_counts(left_motor_sl);
  //ev3_motor_reset_counts(right_motor_sl);

  //メンバ変数の初期化 基本的に0
  left_motor_current_angle  = ev3_motor_get_counts(left_motor_sl);
  right_motor_current_angle = ev3_motor_get_counts(right_motor_sl);
  left_motor_old_angle = left_motor_current_angle;
  right_motor_old_angle = right_motor_current_angle;
  left_motor_rotation_angle = right_motor_rotation_angle = 0;
  wheel_across = 8.0; //need check of actual value
  between_wheels = 16.0;
  moving_distance = 0;
  turning_angle = 0;
  left_wheel_moving_distance = right_wheel_moving_distance = 0;
  current_x = current_y = current_angle = 0;
  old_x = old_y = old_angle = 0;


  /* 地図を作らない時はFILE関連は消しとくこと！ ヘッダファイル含めて！*/
  if (( fp = fopen("sl.data", "w")) != NULL) {
    ev3_lcd_draw_string("SelfLoc file error!", 0, 5);
  }

  ev3_led_set_color(LED_GREEN); /* 初期化完了通知 */
  tslp_tsk(10); /* 10msecウェイト */
  ev3_led_set_color(LED_ORANGE); /* 初期化完了通知 */
  tslp_tsk(10); /* 10msecウェイト */
  ev3_led_set_color(LED_GREEN); /* 初期化完了通知 */
  tslp_tsk(10); /* 10msecウェイト */
  ev3_led_set_color(LED_ORANGE); /* 初期化完了通知 */
  tslp_tsk(10); /* 10msecウェイト */


  

}


void SelfLocalization::update () {

  //左車輪の回転角
  left_motor_old_angle = left_motor_current_angle;
  left_motor_current_angle = ev3_motor_get_counts(left_motor_sl);
  left_motor_rotation_angle =
    left_motor_current_angle - left_motor_old_angle;
  left_wheel_moving_distance =
    wheel_across * M_PI * (left_motor_rotation_angle / 360.0);

  //右車輪の回転角
  old_x = current_x;
  old_y = current_y;
  old_angle = current_angle;

  right_motor_old_angle = right_motor_current_angle;
  right_motor_current_angle = ev3_motor_get_counts(right_motor_sl);
  right_motor_rotation_angle =
    right_motor_current_angle - right_motor_old_angle;
  right_wheel_moving_distance =
    wheel_across * M_PI * (right_motor_rotation_angle / 360.0);

  //移動距離と、車体の回転角
  moving_distance =
    (right_wheel_moving_distance + left_wheel_moving_distance) / 2;
  turning_angle = (right_wheel_moving_distance - left_wheel_moving_distance)
    / between_wheels;

  //座標
  current_x = old_x + (moving_distance * cos(old_angle + (turning_angle/2)));
  current_y = old_y + (moving_distance * sin(old_angle + (turning_angle/2)));
  current_angle = old_angle + turning_angle;

}

void SelfLocalization::writing_current_coordinates() {

  fprintf(fp, "%f %f\n", current_x, current_y);

  return;
}