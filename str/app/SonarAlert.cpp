#include "SonarAlert.h"

SonarAlert::SonarAlert( int distanceBorder, int secPerCycle ):
    SONAR_ALERT_DISTANCE( distanceBorder )
{
    timeCounter = 0;
    // sonarSensor = new SonarSensor( PORT_3 );
    this->secPerCycle = secPerCycle;
}

// Testコード用
SonarAlert::SonarAlert( int distanceBorder, int secPerCycle, SonarSensor& sensor):
    SONAR_ALERT_DISTANCE( distanceBorder )
{
    timeCounter = 0;
    sonarSensor = &sensor;
    this->secPerCycle = secPerCycle;
}

SonarAlert::~SonarAlert()
{
    // delete sonarSensor;
}

/**
 * 目の前に障害物が存在するか検知する。
 * @pre
 * @return 0 : 障害物なし
 *         1 : 障害物あり
 */
int SonarAlert::detectBarrier()
{
    timeCounter++;
    int alert = 0;

    if( timeCounter == 40/secPerCycle )
    {
        if( sonarSensor->getDistance() <= SONAR_ALERT_DISTANCE
                && 0 <= sonarSensor->getDistance() )
        {
            alert = 1;
        }
        else
        {
            alert = 0;
        }
        timeCounter = 0;
    }

    return alert;
}

int SonarAlert::getDistanceBorder()
{
    return SONAR_ALERT_DISTANCE;
}
