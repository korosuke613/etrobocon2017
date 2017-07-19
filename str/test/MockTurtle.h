#ifndef _MOCK_TURTLE_H
#define _MOCK_TURTLE_H
#include "gmock/gmock.h"
#include "Turtle.h"

class MockTurtle : public Turtle {
 public:
  MOCK_METHOD0(PenUp, void());  
  MOCK_METHOD0(PenDown, void());
};
#endif // _MOCK_TURTLE_H
