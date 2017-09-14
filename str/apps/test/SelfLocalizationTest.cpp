/**
 * SelfLocalizationTest.cpp
 */

/* コンパイル(平木場) 
$ g++-7 -w ../apps/commons/Pid.cpp PidTest.cpp gtest_main.o gtest-all.o -I. -I.. -I../googletest/googletest/include
$ ./a.out
*/

#include <gtest/gtest.h>
#include "SelfLocalization.h" // このヘッダファイルのcppファイルをテスト

// Pidのtarget以下の数字を入力すると負の数を出力する
TEST( SelfLocalizationTest, CalculateTest1 )
{
    SelfLocalization sl;

    sl(0, 0);
    sl.update(100, 200);

    std::cout << sl.getPointX() << std::endl;
    std::cout << sl.getPointY() << std::endl;    
}