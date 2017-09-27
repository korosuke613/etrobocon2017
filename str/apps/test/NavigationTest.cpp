/**
 * NavigationTest.cpp
 */

/* コンパイル(平木場) 
g++-7 NavigationTest.cpp ../src/SelfLocalization.cpp ../src/Pid.cpp ../src/TurnControl.cpp ../src/SpeedControl.cpp ../src/LineTracerWalker.cpp ../src/Navigation.cpp gtest_main.o gtest-all.o -I../include -I../../googletest/googletest/include
*/

#include <gtest/gtest.h>
#include "Navigation.h" // このヘッダファイルのcppファイルをテスト

TEST( NavigationTest, setLineTest1 )
{
    Navigation navi(0, 0, false);

    navi.setLine(0.0, 10.0, 100.0, 200.0);
    ASSERT_EQ(navi.start_x, 0.0);
    ASSERT_EQ(navi.start_y, 10.0);
    ASSERT_EQ(navi.goal_x, 100.0);
    ASSERT_EQ(navi.goal_y, 200.0);    
}

TEST( NavigationTest, getDiffLineTest1 )
{
    Navigation navi(0, 0, false);

    navi.setLine(0.0, 0.0, 100.0, 100.0);
    ASSERT_LT(navi.getDiffLine(10.0, 11.0), 0.0);
}

TEST( NavigationTest, getDiffLineTest2 )
{
    Navigation navi(0, 0, false);

    navi.setLine(0.0, 0.0, 100.0, 100.0);
    ASSERT_GT(navi.getDiffLine(10.0, 9.0), 0.0);
}

TEST( NavigationTest, getDiffLineTest3 )
{
    Navigation navi(0, 0, false);

    navi.setLine(0.0, 0.0, 0.0, 100.0);
    ASSERT_EQ(navi.getDiffLine(10.0, 20.0), 10.0);
}

TEST( NavigationTest, getDiffLineTest4 )
{
    Navigation navi(0, 0, false);

    navi.setLine(0.0, 0.0, 0.0, 100.0);
    ASSERT_EQ(navi.getDiffLine(-10.0, 20.0), -10.0);
}

TEST( NavigationTest, calculateValueTest1 )
{
    Navigation navi(0, 0, false);

    navi.setLine(0.0, 0.0, 0.0, 100.0);
    ASSERT_EQ(navi.calculateValue(10, 10, false), true);
}

TEST( NavigationTest, checkEndOfLineTest2 )
{
    Navigation navi(0, 0, false);

    navi.setLine(0.0, 0.0, 100.0, 0.0);
    bool end = navi.calculateValue(1500, 1500, false);
    ASSERT_EQ(end, false);
}

TEST( NavigationTest, calculateLineAngle1 )
{
    Navigation navi(0, 0, false);

    navi.setLine(0.0, 0.0, 100.0, 100.0);
    navi.getDiffLine(0.0, 0.0);
    navi.calculate_line_angle(false);
    ASSERT_EQ(navi.goal_angle, 45);
}


TEST( NavigationTest, calculateLineAngle2 )
{
    Navigation navi(0, 0, false);

    navi.setLine(0.0, 0.0, 100.0, 100.0);
    navi.getDiffLine(0.0, 0.0);
    navi.calculate_line_angle(true);
    ASSERT_EQ(navi.goal_angle, -135);
}

TEST( NavigationTest, calculateAngleTest1)
{
    bool isBack = false;
    Navigation navi(0, 0, false);
    
    navi.setLine(0.0, 0.0, 100.0, 100.0);
    navi.calculate_line_angle(isBack);
    bool end = navi.calculateAngle(100, 280, isBack);
    ASSERT_EQ(end, true);
}

TEST( NavigationTest, calculateAngleTest2)
{
    bool isBack = false;
    Navigation navi(0, 0, false);
    
    navi.setLine(0.0, 0.0, 100.0, 100.0);
    navi.calculate_line_angle(isBack);
    bool end = navi.calculateAngle(0, 100, isBack);
    ASSERT_EQ(end, false);
}


TEST( NavigationTest, calculateAngleTest3)
{
    bool isBack = true;
    Navigation navi(0, 0, false);
    
    navi.setLine(0.0, 0.0, 100.0, 100.0);
    navi.calculate_line_angle(isBack);
    bool end = navi.calculateAngle(0, -550, isBack);
    ASSERT_EQ(end, true);
}