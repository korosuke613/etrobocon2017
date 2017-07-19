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


//要らないかも？
#include "common_definition.h"


// //strcture for self_localization
// typedef struct self_localization_structure {
//   float right_motor_current_angle, right_motor_old_angle,right_motor_rotation_angle;
//   float left_motor_current_angle, left_motor_old_angle, left_motor_rotation_angle;
//   float wheel_across;
//   float between_wheels;
//   float right_wheel_moving_distance, left_wheel_moving_distance;
//   float moving_distance;
//   float turning_angle;
//   float current_x, current_y, current_angle;
//   float old_x, old_y, old_angle;
// } self_localization;
//
//  ↓
//
class Self_localization {

  //member variables
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
  void set_target_coordinates(float target_x, float target_y, float target_radius, float ev3_radius);
  bool approached_target_coordinates(float target_x, float target_y,float target_radius, float ev3_radius);
private:
  //残りのメソッドかな？
};




//constructor. self_localization_make is used in self_localization_constructor
self_localization* self_localization_constructor(void);
self_localization* self_localization_make(void);

//destructor. self_localization_free is used in self_localization_destructor
void self_localization_destructor(void);
void self_localization_free(self_localization*);

//updating of current coordinates
void self_localization_update(self_localization *);

//display of current coordinates
void self_localization_display_coordinates(self_localization*);

//decision in or out of the circle.
int self_localization_near_target_coordinates(float target_x, float target_y, float target_radius,
					     float ev3_radius, self_localization* sl);

//writing data of self localization
void self_localization_writing_current_coordinates(FILE*, self_localization*);



int wheel_angle_of_rotation_to_direction(int right);
float navi_pid(float distance);
float self_localization_navi(int px, int py);
void get_new_place_information(float *next_x,float *next_y,int *next_direction);
int direction_to_wheel_angle_of_rotation(int angle);



#endif
