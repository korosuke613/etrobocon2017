#include <gtest/gtest.h>
#include "BoardAnalyzer.h"


//ブロックの初期配置の盤面の分析を行うテスト(評価に用いる属性の分析)
TEST(LeftSquareCountTest, return0SetBlack8Red13Yellow9Blue6Green14)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {8,13,9,6,14};// 黒 赤 黄 青 緑
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 左凹四角形上のブロックの数のテスト
	ASSERT_EQ( analyzer.getInLeftSquareCount(), 0);
	
}

TEST(LeftSquareCountTest, return3SetBlack1Red2Yellow3Blue4Green5)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {1,2,3,4,5};// 黒 赤 黄 青 緑
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 左凹四角形上のブロックの数のテスト
	ASSERT_EQ( analyzer.getInLeftSquareCount(), 3);
	
}

TEST(LeftSquareCountTest, return2SetBlack5Red8Yellow10Blue12Green6)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {5,8,10,12,6};// 黒 赤 黄 青 緑
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 左凹四角形上のブロックの数のテスト
	ASSERT_EQ( analyzer.getInLeftSquareCount(), 2);
	
}


// 左凹四角形上の交換パターンの検出テスト
TEST(LeftSquareExchangePatternTest, returnTrueSetBlack10Red2Yellow8Blue1Green5)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {10,2,8,1,5};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnLeftSquare(), true);
}

TEST(LeftSquareExchangePatternTest, returnFalseSetBlack1Red2Yellow3Blue4Green5)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {1,2,3,4,5};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnLeftSquare(), false);
}

TEST(LeftSquareExchangePatternTest, returnTrueSetBlack9Red4Yellow10Blue41Green5)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {9,4,10,14,5};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnLeftSquare(), true);
}

TEST(LeftSquareExchangePatternTest, returnTrueSetBlack13Red5Yellow1Blue6Green4)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {13,5,1,6,4};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnLeftSquare(), true);
}

TEST(LeftSquareExchangePatternTest, returnTrueSetBlack1Red12Yellow6Blue10Green2)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {1,12,6,10,2};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnLeftSquare(), true);
}

TEST(LeftSquareExchangePatternTest, returnFalseSetBlack8Red2Yellow1Blue5Green3)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {8,2,1,5,3};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnLeftSquare(), false);
}


// 五角形上の交換パターンの検出テスト
TEST(PentagonExchangePatternTest, returnTrueSetBlack10Red2Yellow8Blue1Green5)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {6,2,4,3,8};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnPentagon(), true);
}

TEST(PentagonExchangePatternTest, returnTrueSetBlack1Red9Yellow4Blue14Green13)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {1,9,4,14,13};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnPentagon(), true);
}

TEST(PentagonExchangePatternTest, returnTrueSetBlack12Red15Yellow6Blue11Green13)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {12,15,6,11,13};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnPentagon(), true);
}

TEST(PentagonExchangePatternTest, returnTrueSetBlack9Red6Yellow2Blue5Green14)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {9,6,2,5,14};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnPentagon(), true);
}

TEST(PentagonExchangePatternTest, returnFalseSetBlack1Red2Yellow3Blue4Green5)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {1,2,3,4,5};
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 交換パターンの検出
	ASSERT_EQ( analyzer.hasExchangePatternOnPentagon(), false);
}


//ブロックの初期配置の盤面の分析を行うテスト(評価に用いる属性の分析)
TEST(RightSideCountTest, return2SetBlack8Red13Yellow9Blue6Green14)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {8,13,9,6,14};// 黒 赤 黄 青 緑
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 左凹四角形上のブロックの数のテスト
	ASSERT_EQ( analyzer.getInRightSideCount(), 1);
	
}

TEST(RightSideCountTest, return2SetBlack1Red2Yellow3Blue4Green5)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {1,2,3,4,5};// 黒 赤 黄 青 緑
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 左凹四角形上のブロックの数のテスト
	ASSERT_EQ( analyzer.getInRightSideCount(), 2);
	
}

TEST(RightSideCountTest, return0SetBlack5Red8Yellow10Blue12Green6)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {5,8,10,12,6};// 黒 赤 黄 青 緑
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 左凹四角形上のブロックの数のテスト
	ASSERT_EQ( analyzer.getInRightSideCount(), 0);
	
}

TEST(RightSideCountTest, return5SetBlack3Red4Yellow7Blue11Green9)
{
	BoardAnalyzer analyzer;
	int8_t initPositions[5] = {3,4,7,11,9};// 黒 赤 黄 青 緑
	
	// 初期位置の入力
	analyzer.set(initPositions);
	
	// 左凹四角形上のブロックの数のテスト
	ASSERT_EQ( analyzer.getInRightSideCount(), 5);
	
}

