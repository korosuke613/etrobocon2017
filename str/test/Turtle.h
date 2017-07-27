#ifndef _TURTLE_H
#define _TURTLE_H

class Turtle {
 public:
  Turtle(){}
  virtual ~Turtle() {}

  virtual void PenUp() = 0;
  virtual void PenDown() = 0;
};
#endif // _TURTLE_H
