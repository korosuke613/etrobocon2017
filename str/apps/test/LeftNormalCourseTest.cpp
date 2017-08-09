/**
 * LeftNormalCourseTest.cpp
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
