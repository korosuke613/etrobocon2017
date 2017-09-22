#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <app/SonarAlert.h>
#include "MockSonarSensor.h"
using ::testing::AtLeast;
using ::testing::Return;

// $B%"%i!<%H$9$k5wN%$r%3%s%9%H%i%/%?$G(B30$B$K%;%C%H$9$k$H(B30$B$rJV$9(B
TEST( detectBarrierTest, return30WhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );
    ASSERT_EQ( sonarAlert.getDistanceBorder(), 30 );
}

// $B%"%i!<%H5wN%(B30$B0JFb!J(B20$B!K$KF~$C$F$$$F$b(B1$B2sL\$N4QB,$G$O>c32J*$rFCDj$7$J$$(B
TEST( detectBarrierTest, notDetectBarrierCheckOneTimeOnlyWhenSetAlertDistance30 )
{
    MockSonarSensor sonarSensor;
    EXPECT_CALL( sonarSensor, getDistance() )
        .Times(0);

    SonarAlert sonarAlert( 30, 4, sonarSensor );

    ASSERT_EQ( sonarAlert.detectBarrier(), 0 );
}

// $B%"%i!<%H5wN%(B30$B0JFb!J(B20$B!K$KF~$C$F$$$F(B10$B2sL\$N4QB,$G$O>c32J*$rFCDj$9$k(B
TEST( detectBarrierTest, detectBarrierCheckTenTimesOnlyWhenSetAlertDistance30 )
{
    MockSonarSensor sonarSensor;
    EXPECT_CALL( sonarSensor, getDistance() )
        .Times(2) // if$BJ8Fb$G(B2$B2s8F$P$l$F$$$k(B
        .WillRepeatedly( Return(20) );

    SonarAlert sonarAlert( 30, 4, sonarSensor );

    for( int i = 0; i < 9; i++ )
        sonarAlert.detectBarrier();

    ASSERT_EQ( sonarAlert.detectBarrier(), 1 );
}

// $B%"%i!<%H5wN%(B30$B0JFb!J(B20$B!K$KF~$C$F$$$F$b(B11$B2sL\$N4QB,$G$O>c32J*$rFCDj$7$J$$(B
TEST( detectBarrierTest, detectBarrierCheckElevenTimesOnlyWhenSetAlertDistance30 )
{

    MockSonarSensor sonarSensor;
    EXPECT_CALL( sonarSensor, getDistance() )
        .Times(2) // if$BJ8Fb$G(B2$B2s8F$P$l$F$$$k(B
        .WillRepeatedly( Return(20) );

    SonarAlert sonarAlert( 30, 4, sonarSensor );

    for( int i = 0; i < 10; i++ )
        sonarAlert.detectBarrier();

    ASSERT_EQ( sonarAlert.detectBarrier(), 0 );
}

// $B%"%i!<%H5wN%(B30$B0JFb!J(B20$B!K$KF~$C$F$$$F(B20$B2sL\$N4QB,$G$O>c32J*$rFCDj$9$k(B
TEST( detectBarrierTest, detectBarrierCheckTwentyTimesOnlyWhenSetAlertDistance30 )
{
    MockSonarSensor sonarSensor;
    EXPECT_CALL( sonarSensor, getDistance() )
        .Times(4) // if$BJ8Fb$G(B2$B2s8F$P$l$F$$$k(B
        .WillRepeatedly( Return(20) );

    SonarAlert sonarAlert( 30, 4, sonarSensor );

    for( int i = 0; i < 19; i++ )
        sonarAlert.detectBarrier();

    ASSERT_EQ( sonarAlert.detectBarrier(), 1 );
}

