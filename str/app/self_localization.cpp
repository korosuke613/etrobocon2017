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
#include "self_localization.h"
#include "common_definition.h"

static int direction;
static float x;
static float y;
static int last_angle[2];
static float integral;
static signed long diff[2];
#define KP 0.45
#define KI 0.06
#define KD 0.04

#define CYCLE_ANGLE 40
#define RADIUS 40
#define VEHICLE_WIDTH 160


void test_ev3_motor_rotate() {
  //setting sensor value of radius to 0
  ev3_motor_reset_counts(right_motor); //right motor
  ev3_motor_reset_counts(left_motor); //left motor
  char str[5];
  while(1){
    ev3_motor_rotate(right_motor, 1, 5, true);
    sprintf(str, "%d", (int)ev3_motor_get_counts(right_motor));
    ev3_lcd_draw_string(str, 0, 20);
    ev3_motor_rotate(left_motor, 1, 5, true);
    sprintf(str, "%d", (int)ev3_motor_get_counts(left_motor));
    ev3_lcd_draw_string(str, 0, 40);

  }
}

//constructor
self_localization* self_localization_constructor(){
  //setting sensor value of radius to 0
  ev3_motor_reset_counts(right_motor); //right motor
  ev3_motor_reset_counts(left_motor); //left motor
  return self_localization_make();
}

self_localization *self_localization_make(void) {
  self_localization *new_self_localization =
    (self_localization*)malloc(sizeof(self_localization));
  new_self_localization->right_motor_current_angle = ev3_motor_get_counts(right_motor);
  new_self_localization->left_motor_current_angle = ev3_motor_get_counts(left_motor);
  new_self_localization->right_motor_old_angle = 0;
  new_self_localization->left_motor_old_angle  = 0;
  new_self_localization->right_motor_rotation_angle = 0;
  new_self_localization->left_motor_rotation_angle = 0;
  new_self_localization->wheel_across = 8.0;
  //  new_self_localization->between_wheels = 15.9;
  new_self_localization->between_wheels = 16.0;
  new_self_localization->moving_distance = 0;
  new_self_localization->turning_angle = 0;
  new_self_localization->right_wheel_moving_distance = 0;
  new_self_localization->left_wheel_moving_distance  = 0;
  new_self_localization->current_x = 0;
  new_self_localization->current_y = 0;
  new_self_localization->current_angle = 0;
  new_self_localization->old_x = 0;
  new_self_localization->old_y = 0;
  new_self_localization->old_angle = 0;
  return new_self_localization;
}

void self_localization_free(self_localization *sl) {
  free(sl);
}

void self_localization_update(self_localization *sl){
  //rotation angle of right wheel
  sl->old_x = sl->current_x;
  sl->old_y = sl->current_y;
  sl->old_angle = sl->current_angle;

  sl->right_motor_old_angle = sl->right_motor_current_angle;
  sl->right_motor_current_angle = ev3_motor_get_counts(right_motor);
  sl->right_motor_rotation_angle =
    sl->right_motor_current_angle - sl->right_motor_old_angle;
  sl->right_wheel_moving_distance =
    sl->wheel_across * M_PI * (sl->right_motor_rotation_angle / 360.0);

  //rotation angle of left wheel
  sl->left_motor_old_angle = sl->left_motor_current_angle;
  sl->left_motor_current_angle = ev3_motor_get_counts(left_motor);
  sl->left_motor_rotation_angle =
    sl->left_motor_current_angle - sl->left_motor_old_angle;
  sl->left_wheel_moving_distance =
    sl->wheel_across * M_PI * (sl->left_motor_rotation_angle / 360.0);

  //moving distance and turning angle
  sl->moving_distance =
    (sl->right_wheel_moving_distance + sl->left_wheel_moving_distance) / 2;
  sl->turning_angle = (sl->right_wheel_moving_distance - sl->left_wheel_moving_distance)
    / sl->between_wheels;

  //updating of coordinates
  sl->current_x = sl->old_x + (sl->moving_distance * cos(sl->old_angle + (sl->turning_angle/2)));
  sl->current_y = sl->old_y + (sl->moving_distance * sin(sl->old_angle + (sl->turning_angle/2)));
  sl->current_angle = sl->old_angle + sl->turning_angle;
}

int self_localization_near_target_coordinates(float target_x, float target_y, float target_radius,
					 float ev3_radius, self_localization* sl){
  float distance_between_two_points =
    sqrt( pow((target_x - sl->current_x), 2) + pow((target_y - sl->current_y), 2));
  float total_of_two_radius = target_radius + ev3_radius;

  char s[50];
  //sprintf(s, "dbtp:%f, totr:%f", distance_between_two_points, total_of_two_radius);
  //ev3_lcd_draw_string(s, 0, 60);

  if(distance_between_two_points > total_of_two_radius)
    return 0;
  else
    return 1;
}

void self_localization_display_coordinates(self_localization* sl){
  char str[40];
  sprintf(str, "X:%f Y:%f", sl->current_x, sl->current_y);
  ev3_lcd_draw_string(str, 0, 50);
}


/*
  void get_black(void) {
  int light_u = ev3_color_sensor_get_reflect(color_sensor);
  int light = (int) light_u;
  char str[10];
  sprintf(str, "get black:%d", light);
  ev3_lcd_draw_string(str, 0, 20);
  }
*/

void self_localization_writing_current_coordinates(FILE* fp, self_localization* sl) {

  fprintf(fp, "%f %f\n", sl->current_x, sl->current_y);

  return;
}




float self_localization_navi(int px, int py){
  float next_x,next_y;
  int next_direction;
  float dis_p = 0;
  get_new_place_information(&next_x,&next_y,&next_direction); //¡‚¢‚éêŠ

  if(px - next_x != 0 || py - next_y != 0)
    dis_p = atan2(py - next_y ,px - next_x);

  float arg = wheel_angle_of_rotation_to_direction(next_direction);
  int distance = sqrt((px - next_x) * (px - next_x) + (py - next_y) * (py - next_y ));
  float arg2 = arg/180 * M_PI - (dis_p - M_PI/2);

  return navi_pid(distance * sin(arg2));
}

float navi_pid(float distance){
  float p,i,d;
  diff[0] = diff[1];
  diff[1] = distance;//•Î·‚ğæ“¾
  integral += (diff[1] + diff[0]) / 2.0 * DEL;//•Î·‚Ì—İÏ

  p = KP * diff[1];//•Î·*”ä—áƒQƒCƒ“
  i = KI * integral;//•Î·‚Ì—İÏ*Ï•ªƒQƒCƒ“
  d = KD * (diff[1] - diff[0]) / DEL;//¡‰ñ‚Ì•Î·-‘O‰ñ‚Ì•Î·/ˆ—üŠú*Ï•ªƒQƒCƒ“
  float answer = p + i + d;
  return answer;
}

void get_new_place_information(float *next_x,float *next_y,int *next_direction){
  int port_b = ev3_motor_get_counts(right_motor);
  int port_c = ev3_motor_get_counts(left_motor);

  int distance = ((port_b - last_angle[0]) + (port_c - last_angle[1]))/2;
  *next_direction = direction + (port_b - last_angle[0]) - (port_c - last_angle[1]);
  float arg = wheel_angle_of_rotation_to_direction((*next_direction + direction)/2);
  *next_x = x + distance * sin(-arg/180 * M_PI);
  *next_y = y + distance * cos(arg/180 * M_PI);
  return;
}

int wheel_angle_of_rotation_to_direction(int right){
  int answer = RADIUS * right / VEHICLE_WIDTH;
  return answer;
}
int direction_to_wheel_angle_of_rotation(int angle){
  return VEHICLE_WIDTH * angle / RADIUS;
}
