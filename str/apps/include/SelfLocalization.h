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

#include <cstdio>
#include <cstdint>
#include <math.h>

class MotorAngle{
public:
  float current_angle;
  float old_angle;
  float rotation_angle;
  float moving_distance;
  float wheel_across;
  MotorAngle(std::int32_t degree){
    rotation_angle = 0;
    wheel_across = 8.0;
    moving_distance = 0;
    old_angle = current_angle = degree;
  }
  void update(std::int32_t update_degree){
    old_angle = current_angle;
    current_angle = update_degree;
    rotation_angle = current_angle - old_angle;
    moving_distance = wheel_across * M_PI * (rotation_angle / 360.0);
  }
};

class SelfLocalization {
private:
  MotorAngle left, right;
  float between_wheels;
  float moving_distance_mean;
  float turning_angle;
  float current_x, current_y, current_angle;
  static FILE* fp;

  //member methods
public:
  SelfLocalization (std::int32_t left_motor_sl, std::int32_t right_motor_sl);
  void update (std::int32_t left_motor_sl, std::int32_t right_motor_sl);
  void writing_current_coordinates ();
  bool approached_target_coordinates (float target_x, float target_y, float target_radius);
  float getPointX();
  float getPointY();
  
private:
  //残りのメソッドかな？
  
};

#endif
