#include "BoardAnalyzer.h"

BoardAnalyzer::BoardAnalyzer()
{
	
}

BoardAnalyzer::~BoardAnalyzer()
{
	
}

// ブロックの配置の入力
void BoardAnalyzer::set(int *initPositions)
{
	positions = initPositions;
}

// 左凹四角形中のブロックの個数
int BoardAnalyzer::getInLeftSquareCount()
{
	int leftSquareCount = 0;
	
	// ブロックの初期位置で左凹四角形上にあるものをカウント
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			if(positions[i] == leftSquare[j])
			{
				leftSquareCount++;
			}
		}
	}
	
	return leftSquareCount;
}

// 左凹四角形上の交換パターンを検出
bool BoardAnalyzer::hasExchangePatternOnLeftSquare()
{
	bool isExchangePattern = false;
	
	// 初期位置の中で、左凹四角形上にあるものを取得
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			if(positions[i] == leftSquare[j] && positions[j] == leftSquare[i])
			{
				isExchangePattern = true;
			}
		}
	}
	
	return isExchangePattern;
}

// 五角形上の交換パターンを検出
bool BoardAnalyzer::hasExchangePatternOnPentagon()
{
	bool isExchangePattern = false;
	
	// 初期位置の中で、左凹四角形上にあるものを取得
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			if(positions[i] == pentagon[j] && positions[j] == pentagon[i])
			{
				isExchangePattern = true;
			}
		}
	}
	
	return isExchangePattern;
}

// 左凹四角形中のブロックの個数
int BoardAnalyzer::getInRightSideCount()
{
	int rightSideCount = 0;
	
	// ブロックの初期位置で左凹四角形上にあるものをカウント
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<6; j++)
		{
			if(positions[i] == rightSide[j])
			{
				rightSideCount++;
			}
		}
	}
	
	return rightSideCount;
}
