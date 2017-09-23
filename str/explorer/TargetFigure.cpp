#include "TargetFigure.h"


TargetFigure::TargetFigure()
{
	
}

TargetFigure::~TargetFigure()
{
	
}

// ブロックの初期位置設定
void TargetFigure::set(array<int, 5> positions)
{
	initPositions = positions;
}

// 初期位置を評価し、目標とする図形を決定する
void TargetFigure::evaluate();
{
	targets = leftSquare;
}

int getTargetNum(BlockColor color)
{
	int targetNum = 0;
	
	switch(color)
	{
	case BlockColor::Black:
		targetNum = targets(0);
		break;
		
	case BlockColor::Red:
		targetNum = targets(1);
		break;
		
	case BlockColor::Yellow:
		targetNum = targets(2);
		break;
		
	case BlockColor::Blue:
		targetNum = targets(3);
		break;
		
	case BlockColor::Green:
		targetNum = targets(4);
		break;
	}
	
	return targetNum;
}

