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
    int angle_one = -3;
    if(sub_degree < 0)angle_one = 3;
    sub_degree = sub_degree / 90;
    for(int i = 0; i < 120 * std::abs(sub_degree); i++){
        l += angle_one; 
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
    ASSERT_LE(sl.getPointX(), 7.0);
    ASSERT_LE(sl.getPointY(), 3.0); 
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

TEST( SelfLocalizationTest, calculateCurrentAngleTest1)
{
    SelfLocalization sl(0, 0, false);
    int l, r;
    l = r = 0;

    straight(sl, 20, l, r);
    curve(sl, 45, l, r);

    sl.calculate_current_angle();

    ASSERT_EQ(sl.current_angle_degree, 58);
}

TEST( SelfLocalizationTest, calculateCurrentAngleTest2)
{
    SelfLocalization sl(0, 0, false);
    int l, r;
    l = r = 0;

    straight(sl, 20, l, r);
    curve(sl, -45, l, r);

    sl.calculate_current_angle();

    ASSERT_EQ(sl.current_angle_degree, -58);
}

TEST( SelfLocalizationTest, calculateCurrentAngleTest3)
{
    SelfLocalization sl(0, 0, false);
    int l, r;
    l = r = 0;

    straight(sl, 20, l, r);
    curve(sl, 90, l, r);
    straight(sl, 20, l, r);
    curve(sl, -90, l, r);

    sl.calculate_current_angle();

    ASSERT_EQ(sl.current_angle_degree, 0);
}

TEST( SelfLocalizationTest, isOverNormalVectorTest1){
    SelfLocalization sl(0, 0, false);
    sl.init_normal_vector(0.0, 0.0, 100.0, 100.0, 0.0, 0.0);
    ASSERT_EQ(sl.is_over_normal_vector(10.0, 10.0), false);
}

TEST( SelfLocalizationTest, isOverNormalVectorTest2){
    SelfLocalization sl(0, 0, false);
    sl.init_normal_vector(0.0, 0.0, 100.0, 100.0, 0.0, 0.0);
    ASSERT_EQ(sl.is_over_normal_vector(101.0, 101.0), true);
}

TEST( SelfLocalizationTest, isOverNormalVectorTest3){
    SelfLocalization sl(0, 0, false);
    sl.init_normal_vector(0.0, 0.0, 100.0, 100.0, 0.0, 0.0);
    ASSERT_EQ(sl.is_over_normal_vector(99.0, 101.0), true);
}

TEST( SelfLocalizationTest, isOverNormalVectorTest4){
    SelfLocalization sl(0, 0, false);
    sl.init_normal_vector(0.0, 0.0, 100.0, 100.0, 0.0, 0.0);
    ASSERT_EQ(sl.is_over_normal_vector(101.0, 99.0), true);
}