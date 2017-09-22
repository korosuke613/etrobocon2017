/**
 * AddTest.cpp
 * ヘッダファイルは書かなくてもいいらしい
 */

// googletest/googletest/include内のディレクトリおよびファイルをインクルードする。
#include <gtest/gtest.h>

// なんかのテストコード
int add( int x, int y )
{
    return x + y;
}

// テストケース名とテスト内容を記述する。
// テストケース名はこのテストクラス名、テスト内容は具体的なテストメソッド名を入れるといいかも。
TEST( AddTest, get3add1and2 )
{
    // みんな大好きassertEqual文
    // assertThat文に相当するものはないっぽいけど、ASSERT_EQ文でエラーが発生した時には、引数をコンソール上に表示してくれる完全上位互換
    ASSERT_EQ( add( 1, 2 ), 3 );
}