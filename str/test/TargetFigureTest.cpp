#include <gtest/gtest.h>
#include <TargetFigure.h>

//ブロックの初期位置から目標とする図形を決定する

TEST(TargetFigureTest, returnBlack0Red1Yellow5Blue2Green10SetBlack1Red2Yellow9Blue6Green14)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int8_t initPositions[5] = {1,2,9,6,14};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 0);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 1);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 5);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 2);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 10);
	
}

TEST(TargetFigureTest, returnBlack0Red1Yellow5Blue2Green10SetBlack6Red12Yellow9Blue13Green15)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int8_t initPositions[5] = {6,12,9,13,15};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 0);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 1);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 5);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 2);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 10);
	
}

TEST(TargetFigureTest, returnBlack0Red1Yellow5Blue2Green10SetBlack3Red11Yellow6Blue8Green12)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int8_t initPositions[5] = {3,11,6,8,12};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 0);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 1);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 5);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 2);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 10);
	
}

TEST(TargetFigureTest, returnBlack0Red1Yellow5Blue2Green10SetBlack5Red2Yellow6Blue8Green12)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int8_t initPositions[5] = {5,2,6,8,12};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 0);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 1);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 5);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 2);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 10);
	
}

TEST(TargetFigureTest, returnBlack0Red1Yellow5Blue2Green10SetBlack6Red13Yellow4Blue11Green1)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int8_t initPositions[5] = {6,13,4,11,1};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 0);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 1);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 5);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 2);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 10);
	
}

TEST(TargetFigureTest, returnBlack0Red7Yellow3Blue4Green11SetBlack1Red2Yellow5Blue9Green6)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int8_t initPositions[5] = {1,2,5,9,6};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 0);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 7);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 3);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 4);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 11);
	
}

TEST(TargetFigureTest, returnBlack0Red7Yellow3Blue4Green11SetBlack4Red13Yellow14Blue10Green2)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int8_t initPositions[5] = {4,13,14,10,2};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 0);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 7);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 3);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 4);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 11);
	
}

TEST(TargetFigureTest, returnBlack8Red14Yellow13Blue9Green6SetBlack1Red2Yellow4Blue3Green7)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int8_t initPositions[5] = {1,2,4,3,7};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 8);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 14);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 13);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 9);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 6);
	
}

TEST(TargetFigureTest, returnBlack8Red14Yellow13Blue9Green6SetBlack1Red2Yellow8Blue5Green12)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int8_t initPositions[5] = {1,2,8,5,12};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 8);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 14);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 13);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 9);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 6);
	
}

TEST(TargetFigureTest, returnBlack8Red14Yellow13Blue9Green6SetBlack1Red3Yellow4Blue11Green14)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int8_t initPositions[5] = {1,3,4,11,14};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 8);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 14);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 13);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 9);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 6);
	
}
