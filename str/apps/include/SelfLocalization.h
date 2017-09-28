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
#include <cmath>

class MotorAngle{
public:
  std::int32_t current_angle;
  std::int32_t old_angle;
  std::int32_t rotation_angle;
  float moving_distance;
  float wheel_across;
  MotorAngle(std::int32_t degree){
    rotation_angle = 0;
    wheel_across = 8.2;
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
  bool  is_below_of_normal_border;
  float start_x, start_y, goal_x, goal_y;
  static FILE* fp;
  static bool isSave;
  bool is_below_normal_vector;


  //member methods
public:
  int current_angle_degree;
  SelfLocalization (std::int32_t left_motor_sl, std::int32_t right_motor_sl, bool save = true);
  void update (std::int32_t left_motor_sl, std::int32_t right_motor_sl);
  void writing_current_coordinates ();
  bool approached_target_coordinates (float target_x, float target_y, float target_radius);
  float getPointX();
  float getPointY();
  bool is_over_target_line_of_x (float target_x);
  bool is_over_target_line_of_y (float target_y);
  bool is_below_target_line_of_x(float target_x);
  bool is_below_target_line_of_y(float target_y);
  float calculate_between_ev3_and_border
  (float _start_x, float _start_y, float _goal_x, float _goal_y, float _current_x, float _current_y);
  void file_close();
  void init_normal_vector(float _start_x, float _start_y, float _goal_x, float _goal_y, float _current_x, float _current_y);
  bool is_over_normal_vector(float _current_x, float _current_y);
  void calculate_current_angle();
private:
  //残りのメソッドかな？
  
};

#endif
