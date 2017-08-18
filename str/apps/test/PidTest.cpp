/**
 * PidTest.cpp
 */

/* コンパイル(平木場) 
$ g++-7 -w ../apps/commons/Pid.cpp PidTest.cpp gtest_main.o gtest-all.o -I. -I.. -I../googletest/googletest/include
$ ./a.out
*/

#include <gtest/gtest.h>
#include "Pid.h" // このヘッダファイルのcppファイルをテスト

class TEST_CLASS : public Pid {
public:
    TEST_CLASS():
        Pid(0.5, 0.5, 0.5, 30.0){
    }
    double limitOutput(double pid_value) {
        return Pid::limitOutput(pid_value);
    }
};

// Pidのtarget以下の数字を入力すると負の数を出力する
TEST( PidTest, CalculateTest1 )
{
    TEST_CLASS pid;
 
    // コンストラクタの引数targetに30を入れる
    pid.setPid(0.5, 0.5, 0.5, 30.0);
    // calculateにtarget以下の値を入力する
    pid.calculate(20.0);
    // アウトプットは負の数になる
    ASSERT_LT( pid.get_output(), 0.0 );
}

// Pidのtarget以上の数字を入力すると正の数を出力する
TEST( detectBarrierTest, CalculateTest2 )
{
    TEST_CLASS pid;

    // コンストラクタの引数targetに30を入れる
    pid.setPid(0.5, 0.5, 0.5, 30.0);
    // calculateにtarget以下の値を入力する
    pid.calculate(50.0);
    // アウトプットは正の数になる
    ASSERT_GT( pid.get_output(), 0.0 );
}

// Pidの出力が100を超えると100になる
TEST( PidTest, limitOutputTest1 )
{
    TEST_CLASS pid;

    // コンストラクタの引数targetに30を入れる
    pid.setPid(0.5, 0.5, 0.5, 30.0);
    // calculateにtarget以上の値を入力する
    pid.calculate(300.0);
    // アウトプットは100.0になる
    double output = pid.limitOutput(pid.get_output());
    ASSERT_GE( output, 100.0 );
}

// Pidの出力が-100を超えると-100になる
TEST( PidTest, limitOutputTest2 )
{
    TEST_CLASS pid;

    // コンストラクタの引数targetに300を入れる
    pid.setPid(0.5, 0.5, 0.5, 300.0);
    // calculateにtarget以下の値を入力する
    pid.calculate(30.0);
    // アウトプットは-100.0になる
    double output = pid.limitOutput(pid.get_output());
    ASSERT_GE( output, -100.0 );
}

// Pidの出力が100~-100の範囲だとそのまま
TEST( PidTest, limitOutputTest3 )
{
    TEST_CLASS pid;

    // コンストラクタの引数targetに30を入れる
    pid.setPid(0.5, 0.5, 0.5, 30.0);
    // calculateにtarget以下の値を入力する
    pid.calculate(30.0);
    // アウトプットは0になる
    double output = pid.limitOutput(pid.get_output());
    ASSERT_DOUBLE_EQ( output, 0.0 );
}