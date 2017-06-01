#include "SonarAlert.h"

SonarAlert::SonarAlert( int distanceBorder, int secPerCycle ):
    SONAR_ALERT_DISTANCE( distanceBorder )
{
    timeCounter = 0;
    this->secPerCycle = secPerCycle;
}

/**
 * 目の前に障害物が存在するか検知する。
 * @pre
 * @return 0 : 障害物なし
 *         1 : 障害物あり
 */
int SonarAlert::detectBarrier( int sensorDistance )
{
    timeCounter++;
    int alert = 0;

    if( timeCounter == 40/secPerCycle )
    {
        if( sensorDistance <= SONAR_ALERT_DISTANCE && 0 <= sensorDistance)
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
