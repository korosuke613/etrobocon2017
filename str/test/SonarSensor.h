#ifndef __SONAR_SENSOR__
#define __SONAR_SENSOR__

/**
 * このヘッダファイルはテスト用です
 */

class SonarSensor {
public:
    SonarSensor() {}

    virtual int getDistance() = 0;
};

#endif
