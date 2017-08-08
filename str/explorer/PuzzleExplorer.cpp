
#include "PuzzleExplorer.h"

//コンストラクタ
PuzzleExplorer::PuzzleExplorer(array<int, 5> blockPositions)
{
	this->blockPositions = blockPositions;
	//初期位置を10とする
	this->myPosition = 10;
}

//デストラクタ
PuzzleExplorer::~PuzzleExplorer(){}


int PuzzleExplorer::getNearestBlockPosition()
{
	Block* block = new Block(8);
	
	return block->getPosition();
}
