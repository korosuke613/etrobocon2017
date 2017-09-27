#include "TargetFigure.h"


TargetFigure::TargetFigure()
{
	
}

TargetFigure::~TargetFigure()
{
	
}

// ブロックの初期位置設定
void TargetFigure::set(int* positions)
{
	for(int i=0; i<5; i++){
		initPositions[i] = positions[i];
	}
}

// 初期位置を評価し、目標とする図形を決定する
void TargetFigure::evaluate()
{
	
	if(getNumberInLeftSquare(initPosition) )
	
	for(int i=0; i<5; i++){
		targets[i] = leftSquare[i];
	}
	
}

int TargetFigure::getNumberInLeftSquare()
{
	int num = 0;
	
	
	
	return 
}

int TargetFigure::getTargetNum(BlockColor color)
{
	int targetNum = 0;
	
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

