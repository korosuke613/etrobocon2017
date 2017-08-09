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