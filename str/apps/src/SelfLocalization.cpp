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

FILE* SelfLocalization::fp;

SelfLocalization::SelfLocalization (std::int32_t left_motor_sl, std::int32_t right_motor_sl):
  left(left_motor_sl), right(right_motor_sl){
  //メンバ変数の初期化 基本的に0
  between_wheels = 16.0;
  moving_distance_mean = 0;
  turning_angle = 0;
  current_x = current_y = current_angle = 0;


  /* 地図を作らない時はFILE関連は消しとくこと！ ヘッダファイル含めて！*/
  fp = fopen("traveling_route.txt", "w");
}


void SelfLocalization::update (std::int32_t left_motor_sl, std::int32_t right_motor_sl) {

  //左車輪の回転角
  left.update(left_motor_sl);

  //右車輪の回転角
  right.update(right_motor_sl);  

  //移動距離と、車体の回転角
  moving_distance_mean = (right.moving_distance + left.moving_distance) / 2;
  turning_angle = (right.moving_distance - left.moving_distance) / between_wheels;

  //座標
  current_x += (moving_distance_mean * cos(current_angle + (turning_angle/2)));
  current_y += (moving_distance_mean * sin(current_angle + (turning_angle/2)));
  current_angle += turning_angle;

}

float SelfLocalization::getPointX(){
  return current_x;
}

float SelfLocalization::getPointY(){
  return current_y;
}

void SelfLocalization::writing_current_coordinates() {

  fprintf(fp, "%f %f\n", current_x, current_y);

  return;
}

bool SelfLocalization::approached_target_coordinates (float target_x, float target_y, float target_radius) {
  float distance = sqrt(
		      (target_x - current_x) * (target_x - current_x) +
		      (target_y - current_y) * (target_y - current_y)   );
  if(distance < target_radius)
    return true;
  return false;
}