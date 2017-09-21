/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場) 
$ g++-7 DistanceTest.cpp ../src/Distance.cpp gtest_main.o gtest-all.o -I../include -I../../googletest/googletest/include
*/

#include <gtest/gtest.h>
#include "Distance.h" // このヘッダファイルのcppファイルをテスト

TEST( DistanceTest, getDistanceTotalTest1 )
{
    Distance ds;
    int l, r;
    
    l = 10;
    r = 20;

    ASSERT_EQ(ds.getDistanceTotal(l, r), (l + r)/2);
}

TEST( DistanceTest, getDistanceCurrentTest1 )
{
    Distance ds;
    int l, r, step_l, step_r;
    
    l = 10;
    r = 20;
    ds.getDistanceTotal(l, r);
    ds.resetDistance(l, r);
    step_l = 20;
    step_r = 10;

    ASSERT_EQ(
        ds.getDistanceCurrent(l + step_l, r + step_r), 
        (step_l + step_r)/2
    );
}

TEST( DistanceTest, getDistanceCurrentTest2 )
{
    Distance ds;
    int l, r, step_l, step_r;
    
    l = 100;
    r = 200;
    ds.getDistanceTotal(l, r);
    ds.resetDistance(l, r);
    step_l = 20;
    step_r = 10;

    ASSERT_EQ(
        ds.getDistanceTotal(l, r), 
        (l + r)/2
    );
}