#ifndef __EMOTER__
#define __EMOTER__

#include "Motor.h"
#include "Clock.h"

#include "util.h"

using namespace ev3api;

class Emoter {
public:
  Emoter();
  void turn(int8_t pwm);
  void wipe(int8_t pwm, int maxChange, int angle);
  void changeDefault(int angle);
  void defaultSet(int angle);
  void init();
  void terminate();
  void reset();

private:
  Motor tailHand;
  Clock clock;
};

#endif
