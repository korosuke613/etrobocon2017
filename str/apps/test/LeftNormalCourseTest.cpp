/**
 * LeftNormalCourseTest.cpp
 */


#include <gtest/gtest.h>
#include "LeftNormalCourse.h" // このヘッダファイルのcppファイルをテスト

// 移動距離0の時に直進モード
TEST( LeftNormalCourseTest, statusCheckTest1 )
{
    LeftNormalCourse lnc;
    LeftStatus value;

    lnc.statusCheck(0, 0);
    value = lnc.getStatus()
    ASSERT_LE(value, LeftStatus::STRAIGHT);
}
