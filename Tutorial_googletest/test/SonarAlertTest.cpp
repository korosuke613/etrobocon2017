#include <gtest/gtest.h>
#include <app/SonarAlert.h>


// $B%"%i!<%H$9$k5wN%$r%3%s%9%H%i%/%?$G(B30$B$K%;%C%H$9$k$H(B30$B$rJV$9(B
TEST( detectBarrierTest, return30WhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );
    ASSERT_EQ( sonarAlert.getDistanceBorder(), 30 );
}

// $B%"%i!<%H5wN%(B30$B0JFb!J(B20$B!K$KF~$C$F$$$F$b(B1$B2sL\$N4QB,$G$O>c32J*$rFCDj$7$J$$(B
TEST( detectBarrierTest, notDetectBarrierCheckOneTimeOnlyWhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );
    ASSERT_EQ( sonarAlert.detectBarrier( 20 ), 0 );
}

// $B%"%i!<%H5wN%(B30$B0JFb!J(B20$B!K$KF~$C$F$$$F(B10$B2sL\$N4QB,$G$O>c32J*$rFCDj$9$k(B
TEST( detectBarrierTest, detectBarrierCheckTenTimeOnlyWhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );

    for( int i = 0; i < 9; i++ )
        sonarAlert.detectBarrier( 20 );

    ASSERT_EQ( sonarAlert.detectBarrier( 20 ), 1 );
}

// $B%"%i!<%H5wN%(B30$B0JFb!J(B20$B!K$KF~$C$F$$$F$b(B11$B2sL\$N4QB,$G$O>c32J*$rFCDj$7$J$$(B
TEST( detectBarrierTest, detectBarrierCheckElevenTimeOnlyWhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );

    for( int i = 0; i < 10; i++ )
        sonarAlert.detectBarrier( 20 );

    ASSERT_EQ( sonarAlert.detectBarrier( 20 ), 0 );
}

// $B%"%i!<%H5wN%(B30$B0JFb!J(B20$B!K$KF~$C$F$$$F(B20$B2sL\$N4QB,$G$O>c32J*$rFCDj$9$k(B
TEST( detectBarrierTest, detectBarrierCheckTwentyTimeOnlyWhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );

    for( int i = 0; i < 19; i++ )
        sonarAlert.detectBarrier( 20 );

    ASSERT_EQ( sonarAlert.detectBarrier( 20 ), 1 );
}

