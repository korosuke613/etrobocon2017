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