#include "BoardAnalyzer.h"

BoardAnalyzer::BoardAnalyzer()
{
	
}

BoardAnalyzer::~BoardAnalyzer()
{
	
}

// ブロックの配置の入力
void BoardAnalyzer::set(int* initPositions)
{
	positions = initPositions;
}

// 左凹四角形中のブロックの個数
int BoardAnalyzer::getInLeftSquareCount()
{
	int leftSquareCount = 0;
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

