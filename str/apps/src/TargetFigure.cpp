#include "TargetFigure.h"


TargetFigure::TargetFigure()
{
	
}

TargetFigure::~TargetFigure()
{
	
}

// ブロックの初期位置設定
void TargetFigure::set(int8_t *positions)
{
	initPositions = positions;
	analyzer.set(initPositions);
	
}

// 初期位置を評価し、目標とする図形を決定する
void TargetFigure::evaluate()
{
	// 左凹四角形にあるブロックの個数が3個以上である かつ 五角形にあるブロックが交換パターンである場合 または 左凹四角形にあるブロックの個数が2個以下である かつ 左凹四角形にあるブロックが交換パターンである かつ 五角形にあるブロックが交換パターンである場合
	if((analyzer.getInLeftSquareCount() >= 3 && analyzer.hasExchangePatternOnPentagon() == true) || (analyzer.getInLeftSquareCount() <= 2 && analyzer.hasExchangePatternOnLeftSquare() == true && analyzer.hasExchangePatternOnPentagon() == true))
	{
		// 目標図形を右凹四角形とする
		for(int i=0; i<5; i++)
		{
			targets[i] = rightSquare[i];
		}
	}else 
	// 左凹四角形にあるブロックの個数が2個以下である かつ 左凹四角形にあるブロックが交換パターンでない かつ 半分より右側にあるブロックが2個以下である場合
	if(analyzer.getInLeftSquareCount() <= 2 && analyzer.hasExchangePatternOnLeftSquare() == false && analyzer.getInRightSideCount() <= 2)
	{
		// 目標図形を左四角形とする
		for(int i=0; i<5; i++)
		{
			targets[i] = leftSquare[i];
		}
	}else
	{
		// 目標図形を五角形とする
		for(int i=0; i<5; i++)
		{
			targets[i] = pentagon[i];
		}
	}
	
}

// 各色の目標とする位置番号を取得する
int8_t TargetFigure::getTargetNum(BlockColor color)
{
	int8_t targetNum = 0;
	
	switch(color)
	{
	case BlockColor::Black:
		targetNum = targets[0];
		break;
		
	case BlockColor::Red:
		targetNum = targets[1];
		break;
		
	case BlockColor::Yellow:
		targetNum = targets[2];
		break;
		
	case BlockColor::Blue:
		targetNum = targets[3];
		break;
		
	case BlockColor::Green:
		targetNum = targets[4];
		break;
	}
	
	return targetNum;
}

