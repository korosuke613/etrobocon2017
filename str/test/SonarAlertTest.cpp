#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <app/SonarAlert.h>
#include "MockSonarSensor.h"
using ::testing::AtLeast;
using ::testing::Return;

// アラートする距離をコンストラクタで30にセットすると30を返す
TEST( detectBarrierTest, return30WhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );
    ASSERT_EQ( sonarAlert.getDistanceBorder(), 30 );
}

// アラート距離30以内（20）に入っていても1回目の観測では障害物を特定しない
TEST( detectBarrierTest, notDetectBarrierCheckOneTimeOnlyWhenSetAlertDistance30 )
{
    MockSonarSensor sonarSensor;
    EXPECT_CALL( sonarSensor, getDistance() )
        .Times(0);

    SonarAlert sonarAlert( 30, 4, sonarSensor );

    ASSERT_EQ( sonarAlert.detectBarrier(), 0 );
}

// アラート距離30以内（20）に入っていて10回目の観測では障害物を特定する
TEST( detectBarrierTest, detectBarrierCheckTenTimesOnlyWhenSetAlertDistance30 )
{
    MockSonarSensor sonarSensor;
    EXPECT_CALL( sonarSensor, getDistance() )
        .Times(2) // if文内で2回呼ばれている
        .WillRepeatedly( Return(20) );

    SonarAlert sonarAlert( 30, 4, sonarSensor );

    for( int i = 0; i < 9; i++ )
        sonarAlert.detectBarrier();

    ASSERT_EQ( sonarAlert.detectBarrier(), 1 );
}

// アラート距離30以内（20）に入っていても11回目の観測では障害物を特定しない
TEST( detectBarrierTest, detectBarrierCheckElevenTimesOnlyWhenSetAlertDistance30 )
{

    MockSonarSensor sonarSensor;
    EXPECT_CALL( sonarSensor, getDistance() )
        .Times(2) // if文内で2回呼ばれている
        .WillRepeatedly( Return(20) );

    SonarAlert sonarAlert( 30, 4, sonarSensor );

    for( int i = 0; i < 10; i++ )
        sonarAlert.detectBarrier();

    ASSERT_EQ( sonarAlert.detectBarrier(), 0 );
}

// アラート距離30以内（20）に入っていて20回目の観測では障害物を特定する
TEST( detectBarrierTest, detectBarrierCheckTwentyTimesOnlyWhenSetAlertDistance30 )
{
    MockSonarSensor sonarSensor;
    EXPECT_CALL( sonarSensor, getDistance() )
        .Times(4) // if文内で2回呼ばれている
        .WillRepeatedly( Return(20) );

    SonarAlert sonarAlert( 30, 4, sonarSensor );

    for( int i = 0; i < 19; i++ )
        sonarAlert.detectBarrier();

    ASSERT_EQ( sonarAlert.detectBarrier(), 1 );
}

