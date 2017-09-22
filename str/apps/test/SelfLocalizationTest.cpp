/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場) 
$ g++-7 SelfLocalizationTest.cpp ../src/SelfLocalization.cpp gtest_main.o gtest-all.o -I../include -I../../googletest/googletest/include
*/

#include <gtest/gtest.h>
#include "SelfLocalization.h" // このヘッダファイルのcppファイルをテスト

void straight(SelfLocalization &sl, int kyori, int &l, int &r){
    for(int i = 0; i < kyori; i++){
        l += 10; 
        r += 10;
        sl.update(l, r);
    }
}

void curve(SelfLocalization &sl, float sub_degree, int &l, int &r){
    sub_degree = sub_degree / 90;
    for(int i = 0; i < 120 * sub_degree; i++){
        l += 3; 
        sl.update(l, r);
    }
}

TEST( SelfLocalizationTest, CalculateTest1 )
{
    SelfLocalization sl(0,0, false);

    sl.update(100, 200);

    ASSERT_GE(sl.getPointX(), 10.0);
    ASSERT_GE(sl.getPointY(), 2.0);  
}

TEST( SelfLocalizationTest, CalculateTest2 )
{
    SelfLocalization sl(0, 0, true);
    int l, r;
    l = r = 0;

    for(int i=0; i < 10; i++){
        straight(sl, 20, l, r);
        curve(sl, 180, l, r);
        straight(sl, 20, l, r);
        curve(sl, 180, l, r);
    }
    ASSERT_LE(sl.getPointX(), 1.0);
    ASSERT_LE(sl.getPointY(), 1.0); 
}

TEST( SelfLocalizationTest, calculateBetweenEv3AndBorder1)
{
    SelfLocalization sl(0, 0, true);
    float distance = sl.calculate_between_ev3_and_border(0.0, 0.0, 10.0, 10.0, 0.0, 0.0);
    ASSERT_FLOAT_EQ(distance, 0.0);

}

TEST( SelfLocalizationTest, calculateBetweenEv3AndBorder2)
{
    SelfLocalization sl(0, 0, true);
    float distance = sl.calculate_between_ev3_and_border(-50.0, 80.0, 127.0, 91.0, -85.0, 70.0);
    ASSERT_NEAR(distance, 7.809, 0.001);

}

TEST( SelfLocalizationTest, calculateBetweenEv3AndBorder3)
{
    SelfLocalization sl(0, 0, true);
    float distance = sl.calculate_between_ev3_and_border(2.0, 1.0, 6.0, 7.0, 3.0, 4.0);
    ASSERT_NEAR(distance, -0.83205, 0.001);

}

TEST( SelfLocalizationTest, calculateBetweenEv3AndBorder4)
{
    SelfLocalization sl(0, 0, true);
    float distance = sl.calculate_between_ev3_and_border( 0.0, 0.0, 10.0, 0.0, 3.0, 0.0);
    ASSERT_NEAR(distance, 0.0, 0.001);

}

TEST( SelfLocalizationTest, calculateBetweenEv3AndBorder5)
{
    SelfLocalization sl(0, 0, true);
    float distance = sl.calculate_between_ev3_and_border( 0.0, 0.0, 0.0, 10.0, 0.0, 3.0);
    ASSERT_NEAR(distance, 0.0, 0.001);

}