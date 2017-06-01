#include <gtest/gtest.h>
#include <app/SonarAlert.h>


// アラートする距離をコンストラクタで30にセットすると30を返す
TEST( detectBarrierTest, return30WhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );
    ASSERT_EQ( sonarAlert.getDistanceBorder(), 30 );
}

// アラート距離30以内（20）に入っていても1回目の観測では障害物を特定しない
TEST( detectBarrierTest, notDetectBarrierCheckOneTimeOnlyWhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );
    ASSERT_EQ( sonarAlert.detectBarrier( 20 ), 0 );
}

// アラート距離30以内（20）に入っていて10回目の観測では障害物を特定する
TEST( detectBarrierTest, detectBarrierCheckTenTimeOnlyWhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );

    for( int i = 0; i < 9; i++ )
        sonarAlert.detectBarrier( 20 );

    ASSERT_EQ( sonarAlert.detectBarrier( 20 ), 1 );
}

// アラート距離30以内（20）に入っていても11回目の観測では障害物を特定しない
TEST( detectBarrierTest, detectBarrierCheckElevenTimeOnlyWhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );

    for( int i = 0; i < 10; i++ )
        sonarAlert.detectBarrier( 20 );

    ASSERT_EQ( sonarAlert.detectBarrier( 20 ), 0 );
}

// アラート距離30以内（20）に入っていて20回目の観測では障害物を特定する
TEST( detectBarrierTest, detectBarrierCheckTwentyTimeOnlyWhenSetAlertDistance30 )
{
    SonarAlert sonarAlert( 30, 4 );

    for( int i = 0; i < 19; i++ )
        sonarAlert.detectBarrier( 20 );

    ASSERT_EQ( sonarAlert.detectBarrier( 20 ), 1 );
}

