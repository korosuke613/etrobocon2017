#ifndef __WALKER__
#define __WALKER__

#include "Motor.h"
#include "Clock.h"
#include "util.h"

using namespace ev3api;

class Walker {
public:
  Walker();
  void stop();
  void run(int8_t pwm, int8_t turn);
  int edgeChange();
  void moveAngle(int8_t pwm, int angle);
  void angleChange(int angle, int rotation);
  int32_t get_count_L();
  int32_t get_count_R();
  void init();
  void terminate();
  void reset();

private:
  Motor leftWheel;
  Motor rightWheel;
  Clock clock;
  int8_t leftRight = 1; // 1 -> 右, -1 -> 左
};


#endif
