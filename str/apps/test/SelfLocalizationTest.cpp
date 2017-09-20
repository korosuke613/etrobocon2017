/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場) 
$ g++-7 SelfLocalizationTest.cpp ../src/SelfLocalization.cpp gtest_main.o gtest-all.o -I../include -I../../googletest/googletest/include
*/

#include <gtest/gtest.h>
#include "SelfLocalization.h" // このヘッダファイルのcppファイルをテスト

// Pidのtarget以下の数字を入力すると負の数を出力する
TEST( SelfLocalizationTest, CalculateTest1 )
{
    SelfLocalization sl(0,0);

    sl.update(100, 200);

    ASSERT_GE(sl.getPointX(), 10.0);
    ASSERT_GE(sl.getPointY(), 2.0);  
}