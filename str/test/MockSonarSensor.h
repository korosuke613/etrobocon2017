#ifndef __MOCK_SONAR_SENSOR__
#define __MOCK_SONAR_SENSOR__
#include "gmock/gmock.h"
#include "SonarSensor.h"

class MockSonarSensor : public SonarSensor {
public:
    MOCK_METHOD0(getDistance, int());
};
#endif
