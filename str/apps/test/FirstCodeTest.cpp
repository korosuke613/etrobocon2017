/**
 * FirstCodeTest.cpp
 */

 /* コンパイル(森) 
  * $ g++ -w ../src/FirstCode.cpp FirstCodeTest.cpp gtest_main.o gtest-all.o -I../include -I../../googletest/googletest/include
  * $ ./a.out
  */

#include <gtest/gtest.h>
#include "FirstCode.h" // このヘッダファイルのcppファイルをテスト

// 何もしない場合は0を返す
TEST( FirstCodeTest, get0WhenNoneUpAndDownAnyDigit )
{
    FirstCode obj;

    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 0 );
}

// 最初に5桁目を上げた場合は10000を返す
TEST( FirstCodeTest, get10000WhenOnceUp5thDigit )
{
    FirstCode obj;

    obj.upDigit( 5 );
    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 10000 );
}

// 最初に4桁目を上げた場合は1000を返す
TEST( FirstCodeTest, get1000WhenOnceUp4thDigit )
{
    FirstCode obj;

    obj.upDigit( 4 );
    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 1000 );
}

// 最初に3桁目を上げた場合は100を返す
TEST( FirstCodeTest, get100WhenOnceUp3rdDigit )
{
    FirstCode obj;

    obj.upDigit( 3 );
    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 100 );
}

// 最初に2桁目を上げた場合は10を返す
TEST( FirstCodeTest, get10WhenOnceUp2ndDigit )
{
    FirstCode obj;

    obj.upDigit( 2 );
    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 10 );
}

// 最初に1桁目を上げた場合は1を返す
TEST( FirstCodeTest, get1WhenOnceUp1stDigit )
{
    FirstCode obj;

    obj.upDigit( 1 );
    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 1 );
}

// 5桁目を10回上げた場合は0を返す
TEST( FirstCodeTest, get0When10thUp5thDigit )
{
    FirstCode obj;

    for( int i = 0; i < 10; i++ ) {
        obj.upDigit( 5 );
    }
    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 0 );
}

// 最初に1桁目を上げて下げた場合は0を返す
TEST( FirstCodeTest, get0WhenOnceUpAndDown1stDigita )
{
    FirstCode obj;

    obj.upDigit( 1 );
    obj.downDigit( 1 );
    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 0 );
}

// 5桁目を1回下げた場合は90000を返す
TEST( FirstCodeTest, get90000WhenOnceDown5thDigit )
{
    FirstCode obj;

    obj.downDigit( 5 );
    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 90000 );
}

// 5桁目を10回下げた場合は0を返す
TEST( FirstCodeTest, get0When10thDown5thDigit )
{
    FirstCode obj;

    for( int i = 0; i < 10; i++ ) {
        obj.downDigit( 5 );
    }
    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 0 );
}

// 1桁目を5回、2桁目を4回、3桁目を3回、4桁目を2回、5桁目を1回上げると12345を返す
TEST( FirstCodeTest, get12345WhenOnceDown5thDigit )
{
    FirstCode obj;
    int set[ 5 ];
    set[ 0 ] = 5;
    set[ 1 ] = 4;
    set[ 2 ] = 3;
    set[ 3 ] = 2;
    set[ 4 ] = 1;

    for( int i = 0; i < 5; i++ ) {
        for( int j = 0; j < set[ i ]; j++ ) {
            obj.upDigit( i + 1 );
        }
    }
    int expected = obj.getFirstCode();

    ASSERT_EQ( expected, 12345 );
}

// 桁数を何もいじらない場合は5を返す
TEST( FirstCodeTest, get5WhenDoNotChangeLeftAndRightAnyDigitNumber )
{
    FirstCode obj;

    int expected = obj.getDigit();

    ASSERT_EQ( expected, 5 );
}

// 桁数を右に1回ずれた場合は4を返す
TEST( FirstCodeTest, get4WhenOnceChangeRightDigitNumber )
{
    FirstCode obj;

    obj.changeRightDigit();
    int expected = obj.getDigit();

    ASSERT_EQ( expected, 4 );
}

// 桁数を右に5回ずれた場合は5を返す
TEST( FirstCodeTest, get5When5thChangeRightDigitNumber )
{
    FirstCode obj;

    for( int i = 0; i < 5; i++ ) {
        obj.changeRightDigit();
    }
    int expected = obj.getDigit();

    ASSERT_EQ( expected, 5 );
}

// 桁数を右に2回ずれてから左に1回ずれた場合は4を返す
TEST( FirstCodeTest, get5WhenOnceChangeLeftDigitNumberAfterTwiceChangeRightDigitNumber )
{
    FirstCode obj;

    obj.changeRightDigit();
    obj.changeRightDigit();
    obj.changeLeftDigit();
    int expected = obj.getDigit();

    ASSERT_EQ( expected, 4 );
}

// 桁数を左に1回ずれた場合は1を返す
TEST( FirstCodeTest, get1WhenOnceChangeLeftDigitNumber )
{
    FirstCode obj;

    obj.changeLeftDigit();
    int expected = obj.getDigit();

    ASSERT_EQ( expected, 1 );
}

