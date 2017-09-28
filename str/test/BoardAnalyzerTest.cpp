#include <gtest/gtest.h>
#include "BoardAnalyzer.h"


//ブロックの初期配置の盤面の分析を行うテスト(評価に用いる属性の分析)
TEST(Test, return0SetBlack9Red13Yellow9Blue6Green14)
{
	BoardAnalyzer analyzer;
	int initPositions[5] = {8,13,9,6,14};// 黒 赤 黄 青 緑
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 左凹四角形上のブロックの数のテスト
	ASSERT_EQ( 	analyzer.getInLeftSquareCount(), 0);
	
}

TEST(Test, return3SetBlack1Red2Yellow3Blue4Green5)
{
	BoardAnalyzer analyzer;
	int initPositions[5] = {1,2,3,4,5};// 黒 赤 黄 青 緑
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 左凹四角形上のブロックの数のテスト
	ASSERT_EQ( 	analyzer.getInLeftSquareCount(), 3);
	
}

TEST(Test, return2SetBlack5Red8Yellow10Blue12Green6)
{
	BoardAnalyzer analyzer;
	int initPositions[5] = {5,8,10,12,6};// 黒 赤 黄 青 緑
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 左凹四角形上のブロックの数のテスト
	ASSERT_EQ( 	analyzer.getInLeftSquareCount(), 2);
	
}