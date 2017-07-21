/**
 * PidTest.cpp
 */

/* コンパイル(平木場) 
$ g++ -w ../apps/commons/Pid.cpp PidTest.cpp gtest_main.o gtest-all.o -I. -I.. -I../googletest/googletest/include
$ ./a.out
*/

#include <gtest/gtest.h>
#include <apps/commons/Pid.h> // このヘッダファイルのcppファイルをテスト


// Pidのtarget以下の数字を入力すると負の数を出力する
TEST( detectBarrierTest, CalculateTest1 )
{
    // コンストラクタの引数targetに30を入れる
    Pid pid( 0.5, 0.5, 0.0, 30.0 );
    // calculateにtarget以下の値を入力する
    pid.calculate(20.0);
    // アウトプットは負の数になる
    ASSERT_LT( pid.get_output(), 0.0 );
}

// Pidのtarget以上の数字を入力すると正の数を出力する
TEST( detectBarrierTest, CalculateTest2 )
{
    // コンストラクタの引数targetに30を入れる
    Pid pid( 0.5, 0.5, 0.0, 30.0 );
    // calculateにtarget以下の値を入力する
    pid.calculate(50.0);
    // アウトプットは正の数になる
    ASSERT_GT( pid.get_output(), 0.0 );
}