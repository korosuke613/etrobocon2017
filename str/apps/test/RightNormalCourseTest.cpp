/**
 * RightNormalCourseTest.cpp
 */

/*
g++-7 -w ../src/Distance.cpp ../src/Pid.cpp ../src/TurnControl.cpp ../src/SpeedControl.cpp ../src/LineTracer.cpp ../src/NormalCourse.cpp ../src/RightNormalCourse.cpp RightNormalCourseTest.cpp gtest_main.o gtest-all.o -I../include -I../../googletest/googletest/include
*/

#include <gtest/gtest.h>
#include "RightNormalCourse.h" // このヘッダファイルのcppファイルをテスト

// 移動距離0の時に直進モード
TEST( RightNormalCourseTest, statusCheckTest1 )
{
    RightNormalCourse rnc;
    int value;

    rnc.statusCheck(0, 0);
    value = rnc.getStatus();

    ASSERT_EQ(value, (int)RightStatus::STRAIGHT);
}

// ステータスが変わらなかったらstatusCheckがfalseを返す。
TEST( RightNormalCourseTest, statusCheckTest2 )
{
    RightNormalCourse rnc;
    bool value;

    value = rnc.statusCheck(0, 0);

    ASSERT_EQ(value, false);
}

// ステータスが変わらなかったらstatusCheckがfalseを返す。
TEST( RightNormalCourseTest, statusCheckTest3 )
{
    RightNormalCourse rnc;
    bool value;

    rnc.statusCheck(0, 0);
    value = rnc.statusCheck(100, 100);

    ASSERT_EQ(value, false);
}

// ステータスが変わったらstatusCheckがtrueを返す。
TEST( RightNormalCourseTest, statusCheckTest4 )
{
    RightNormalCourse rnc;
    bool value;

    rnc.statusCheck(0, 0);
    rnc.statusCheck(100, 100);
    value = rnc.statusCheck(3300, 3300);

    ASSERT_EQ(value, true);
}

// 20000以上走るとSTOPモードになる。
TEST( RightNormalCourseTest, runNormalCourseTest1 )
{
    RightNormalCourse rnc;
    int value;

    rnc.statusCheck(0, 0);
    rnc.statusCheck(20000, 20000);

    rnc.runNormalCourse();

    value = rnc.getStatus();

    ASSERT_EQ(value, (int)RightStatus::STOP);
}

// STOPモードになるまではtrueを返す。
TEST( RightNormalCourseTest, runNormalCourseTest2 )
{
    RightNormalCourse rnc;
    bool value;

    rnc.statusCheck(0, 0);
    rnc.statusCheck(10000, 10000);

    value = rnc.runNormalCourse();

    ASSERT_EQ(value, true);
}

// STOPモードになるまではtrueを返す。
TEST( RightNormalCourseTest, runNormalCourseTest3 )
{
    RightNormalCourse rnc;
    bool value;

    rnc.statusCheck(0, 0);
    rnc.statusCheck(10000, 10000);
    rnc.statusCheck(20000, 20000);

    value = rnc.runNormalCourse();

    ASSERT_EQ(value, false);
}

// 5200まではCURVE_RIGHTモードになる。
TEST( RightNormalCourseTest, runNormalCourseTest6 )
{
    RightNormalCourse nc;
    int value;

    nc.statusCheck(0, 0);
    nc.statusCheck(5000, 5000);

    nc.runNormalCourse();

    value = nc.getStatus();

    ASSERT_EQ(value, (int)RightStatus::CURVE_RIGHT);
}

// 7500まではCURVE_RIGHTモードになる。
TEST( RightNormalCourseTest, runNormalCourseTest7 )
{
    RightNormalCourse nc;
    int value;

    nc.statusCheck(0, 0);
    nc.statusCheck(8000, 8000);

    nc.runNormalCourse();

    value = nc.getStatus();

    ASSERT_EQ(value, (int)RightStatus::CURVE_LEFT_SHORT);
}


// 11000まではCURVE_LEFTモードになる。
TEST( RightNormalCourseTest, runNormalCourseTest8 )
{
    RightNormalCourse nc;
    int value;

    nc.statusCheck(0, 0);
    nc.statusCheck(10000, 10000);

    nc.runNormalCourse();

    value = nc.getStatus();

    ASSERT_EQ(value, (int)RightStatus::CURVE_LEFT);
}

// 12200まではCURVE_RIGHTモードになる。
TEST( RightNormalCourseTest, runNormalCourseTest9 )
{
    RightNormalCourse nc;
    int value;

    nc.statusCheck(0, 0);
    nc.statusCheck(12000, 12000);

    nc.runNormalCourse();

    value = nc.getStatus();

    ASSERT_EQ(value, (int)RightStatus::CURVE_RIGHT);
}

// 15500まではSTRAIGHTモードになる。
TEST( RightNormalCourseTest, runNormalCourseTest10 )
{
    RightNormalCourse nc;
    int value;

    nc.statusCheck(0, 0);
    nc.statusCheck(15000, 15000);

    nc.runNormalCourse();

    value = nc.getStatus();

    ASSERT_EQ(value, (int)RightStatus::STRAIGHT);
}


// 左にそれたらturnが正の値になる
TEST( RightNormalCourseTest, edgeChangeTest1 )
{
    RightNormalCourse rnc;
    int value;

    rnc.statusCheck(0, 0);

    rnc.runNormalCourse();
    rnc.lineTracer.runLine(0, 0, 100);
    value = rnc.lineTracer.getTurn();

    ASSERT_GT(value, 0);
}

// 右にそれたらturnが負の値になる
TEST( RightNormalCourseTest, edgeChangeTest2 )
{
    RightNormalCourse rnc;
    int value;

    rnc.statusCheck(0, 0);

    rnc.runNormalCourse();
    rnc.lineTracer.runLine(0, 0, 0);
    value = rnc.lineTracer.getTurn();

    ASSERT_LT(value, 0);
}