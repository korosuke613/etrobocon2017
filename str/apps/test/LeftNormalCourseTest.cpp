/**
 * LeftNormalCourseTest.cpp
 */

/* 
g++-7 -w ../src/Distance.cpp ../src/Pid.cpp ../src/TurnControl.cpp ../src/SpeedControl.cpp ../src/LineTracer.cpp ../src/NormalCourse.cpp ../src/LeftNormalCourse.cpp LeftNormalCourseTest.cpp gtest_main.o gtest-all.o -I../include -I../../googletest/googletest/include
*/

#include <gtest/gtest.h>
#include "LeftNormalCourse.h" // このヘッダファイルのcppファイルをテスト

// 移動距離0の時に直進モード
TEST( LeftNormalCourseTest, statusCheckTest1 )
{
    LeftNormalCourse lnc;
    int value;

    lnc.statusCheck(0, 0);
    value = lnc.getStatus();

    ASSERT_EQ(value, (int)LeftStatus::STRAIGHT);
}

// ステータスが変わらなかったらstatusCheckがfalseを返す。
TEST( LeftNormalCourseTest, statusCheckTest2 )
{
    LeftNormalCourse lnc;
    bool value;

    value = lnc.statusCheck(0, 0);

    ASSERT_EQ(value, false);
}

// ステータスが変わらなかったらstatusCheckがfalseを返す。
TEST( LeftNormalCourseTest, statusCheckTest3 )
{
    LeftNormalCourse lnc;
    bool value;

    lnc.statusCheck(0, 0);
    value = lnc.statusCheck(100, 100);

    ASSERT_EQ(value, false);
}

// ステータスが変わったらstatusCheckがtrueを返す。
TEST( LeftNormalCourseTest, statusCheckTest4 )
{
    LeftNormalCourse lnc;
    bool value;

    lnc.statusCheck(0, 0);
    lnc.statusCheck(100, 100);
    value = lnc.statusCheck(3300, 3300);

    ASSERT_EQ(value, true);
}

// 20000以上走るとSTOPモードになる。
TEST( LeftNormalCourseTest, runNormalCourseTest1 )
{
    LeftNormalCourse lnc;
    int value;

    lnc.statusCheck(0, 0);
    lnc.statusCheck(20000, 20000);

    lnc.runNormalCourse();

    value = lnc.getStatus();

    ASSERT_EQ(value, (int)LeftStatus::STOP);
}

// STOPモードになるまではtrueを返す。
TEST( LeftNormalCourseTest, runNormalCourseTest2 )
{
    LeftNormalCourse lnc;
    bool value;

    lnc.statusCheck(0, 0);
    lnc.statusCheck(10000, 10000);

    value = lnc.runNormalCourse();

    ASSERT_EQ(value, true);
}

// STOPモードになるまではtrueを返す。
TEST( LeftNormalCourseTest, runNormalCourseTest3 )
{
    LeftNormalCourse lnc;
    bool value;

    lnc.statusCheck(0, 0);
    lnc.statusCheck(10000, 10000);
    lnc.statusCheck(20000, 20000);

    value = lnc.runNormalCourse();

    ASSERT_EQ(value, false);
}

// 3240以上走るとSTRAIGHT_SLOWモードになる。
TEST( LeftNormalCourseTest, runNormalCourseTest4 )
{
    LeftNormalCourse lnc;
    int value;

    lnc.statusCheck(0, 0);
    lnc.statusCheck(3100, 3100);

    lnc.runNormalCourse();

    value = lnc.getStatus();

    ASSERT_EQ(value, (int)LeftStatus::STRAIGHT_SLOW);
}


// 5200まではCURVE_RIGHTモードになる。
TEST( LeftNormalCourseTest, runNormalCourseTest6 )
{
    LeftNormalCourse lnc;
    int value;

    lnc.statusCheck(0, 0);
    lnc.statusCheck(5000, 5000);

    lnc.runNormalCourse();

    value = lnc.getStatus();

    ASSERT_EQ(value, (int)LeftStatus::CURVE_RIGHT);
}

// 7500まではCURVE_RIGHTモードになる。
TEST( LeftNormalCourseTest, runNormalCourseTest7 )
{
    LeftNormalCourse lnc;
    int value;

    lnc.statusCheck(0, 0);
    lnc.statusCheck(7400, 7400);

    lnc.runNormalCourse();

    value = lnc.getStatus();

    ASSERT_EQ(value, (int)LeftStatus::CURVE_LEFT_SHORT);
}


// 11000まではCURVE_LEFTモードになる。
TEST( LeftNormalCourseTest, runNormalCourseTest8 )
{
    LeftNormalCourse lnc;
    int value;

    lnc.statusCheck(0, 0);
    lnc.statusCheck(10000, 10000);

    lnc.runNormalCourse();

    value = lnc.getStatus();

    ASSERT_EQ(value, (int)LeftStatus::CURVE_LEFT);
}

// 12200まではCURVE_RIGHTモードになる。
TEST( LeftNormalCourseTest, runNormalCourseTest9 )
{
    LeftNormalCourse lnc;
    int value;

    lnc.statusCheck(0, 0);
    lnc.statusCheck(12000, 12000);

    lnc.runNormalCourse();

    value = lnc.getStatus();

    ASSERT_EQ(value, (int)LeftStatus::CURVE_RIGHT);
}

// 15500まではSTRAIGHTモードになる。
TEST( LeftNormalCourseTest, runNormalCourseTest10 )
{
    LeftNormalCourse lnc;
    int value;

    lnc.statusCheck(0, 0);
    lnc.statusCheck(15000, 15000);

    lnc.runNormalCourse();

    value = lnc.getStatus();

    ASSERT_EQ(value, (int)LeftStatus::STRAIGHT);
}

// 右にそれたらturnが負の値になる
TEST( LeftNormalCourseTest, edgeChangeTest1 )
{
    LeftNormalCourse lnc;
    int value;

    lnc.statusCheck(0, 0);

    lnc.runNormalCourse();
    lnc.lineTracer.runLine(0, 0, 100);
    value = lnc.lineTracer.getTurn();

    ASSERT_LT(value, 0);
}

// 左にそれたらturnが正の値になる
TEST( LeftNormalCourseTest, edgeChangeTest2 )
{
    LeftNormalCourse lnc;
    int value;

    lnc.statusCheck(0, 0);

    lnc.runNormalCourse();
    lnc.lineTracer.runLine(0, 0, 0);
    value = lnc.lineTracer.getTurn();

    ASSERT_GT(value, 0);
}