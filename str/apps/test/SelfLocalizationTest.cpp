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

// Pidのtarget以下の数字を入力すると負の数を出力する
TEST( SelfLocalizationTest, CalculateTest2 )
{
    SelfLocalization sl(0,0);

    int l, r;
    l = r = 0;
    for(int i = 0; i < 40; i++){
        l = r += 3;
        sl.update(l, r);
        sl.writing_current_coordinates();
    }
    for(int i = 0; i < 20; i++){
        l += 3;
        r += 1;
        sl.update(l, r);
    }
    for(int i = 0; i < 40; i++){
        l = r += 3;
        sl.update(l, r);
        sl.writing_current_coordinates();
    }
    std::cout << sl.getPointY() << std::endl;
}