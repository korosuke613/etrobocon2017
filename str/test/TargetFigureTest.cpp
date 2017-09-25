#include <gtest/gtest.h>
#include <TargetFigure.h>

//ブロックの初期位置から目標とする図形を決定する

TEST(TargetFigureTest, returnBlack0Red1Yellow5Blue2Green10SetBlack8Red13Yellow9Blue6Green14)
{
	TargetFigure targetFigure;
	
	// 各ブロックの初期位置を入力
	int initPositions[5] = {8,13,9,6,14};// 黒 赤 黄 青 緑
	targetFigure.set(initPositions); 
	// 初期位置を評価し、目標図形を決定する
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 0);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 1);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 5);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 2);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 10);
	
}