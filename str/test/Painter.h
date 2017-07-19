#ifndef _PAINTER_H
#define _PAINTER_H
#include "Turtle.h"

class Painter {
 public:
  Painter(Turtle* turtle)
    : turtle_(turtle){}
  ~Painter(){}

  bool DrawCircle(int x, int y, int r);
 private:
  Turtle* turtle_;
};
#endif // _PAINTER_H
