/**
 * SpeedControlTest.cpp
 */

 /* コンパイル(平木場) 
$ g++-7 -w ../src/Pid.cpp ../src/SpeedControl.cpp SpeedControlTest.cpp gtest_main.o gtest-all.o -I../include -I../../googletest/googletest/include
$ ./a.out
*/

#include <gtest/gtest.h>
#include "SpeedControl.h" // このヘッダファイルのcppファイルをテスト

// SpeedControl.calculateSpeedForPid()で100を超えない
TEST( SpeedControlTest, calculateSpeedForPidTest1 )
{
    SpeedControl sp;
    int value;

    sp.setPid ( 2.0, 4.8, 0.024, 150.0 );
    value = sp.calculateSpeedForPid(0,0);

    ASSERT_LE(value, 100);
}

// SpeedControl.calculateSpeedForPid()で-100より下回らない
TEST( SpeedControlTest, calculateSpeedForPidTest2 )
{
    SpeedControl sp;
    int value, r, l;
    r = l = 0;
    sp.setPid ( 2.0, 4.8, 0.024, 150.0 );
    for(int i=0; i<25; i++){
        if(i==24){
            r = l += 10000;
        }
        value = sp.calculateSpeedForPid(r,l);
        l = r += i * 10;
    }

    ASSERT_GE(value, -100);
}

class test_SpeedControl: public SpeedControl{
public:
    test_SpeedControl():
        SpeedControl(){
    }
    int calcDistance4ms(int curAngleL, int curAngleR){
        return SpeedControl::calcDistance4ms(curAngleL, curAngleR);
    }
};

// SpeedControl.calcDistance4msで4msで360度進んだとき、
// 円周分進んだことになる。
TEST( SpeedControlTest, calcDistance4msTest1 )
{
    test_SpeedControl sp;
    int value, l;
    float circle;

    l = 0;
    circle = 2 * 3.14 * 81;
    value = sp.calcDistance4ms(0, 0);
    value += sp.calcDistance4ms(90, 90);
    value += sp.calcDistance4ms(180, 180);
    value += sp.calcDistance4ms(270, 270);
    value += sp.calcDistance4ms(360, 360);

    ASSERT_EQ(value, (int)circle);
}