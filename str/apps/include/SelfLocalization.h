/*****************************
 * self_localization.h
 *
 * Author Hiroki Tachiyama
 * Katayama Laboratory
 * Department of Computer Secience and Systems Engineering
 * Faculty of Engineering, University of Miyazaki
 *
 * Created at: Fri Jul 7 23:07:58 JST 2017
 *
 * Coryrights (c) 2017 Katayama Laboratory
 *
 *****************************/
#ifndef __SELF_LOCALIZATION__
#define __SELF_LOCALIZATION__

#include "ev3api.h"
#include "app.h"
#include <math.h>

static motor_port_t
  left_motor_sl  = EV3_PORT_C,
  right_motor_sl = EV3_PORT_B;
static FILE* fp;

class SelfLocalization {
private:
  float right_motor_current_angle, right_motor_old_angle, right_motor_rotation_angle;
  float left_motor_current_angle, left_motor_old_angle, left_motor_rotation_angle;
  float wheel_across;
  float between_wheels;
  float right_wheel_moving_distance, left_wheel_moving_distance;
  float moving_distance;
  float turning_angle;
  float current_x, current_y, current_angle;
  float old_x, old_y, old_angle;

  //member methods
public:
  SelfLocalization ();
  void update ();
  void writing_current_coordinates ();
  bool approached_target_coordinates (float target_x, float target_y, float target_radius);
  bool over_target_line_of_x (float target_x);
  bool over_target_line_of_y (float target_y);
  bool below_target_line_of_x(float target_x);
  bool below_target_line_of_y(float target_y);
private:
  //残りのメソッドかな？
  
};



#endif
