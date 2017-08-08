
#include"Block.h"
#include<string.h>

//コンストラクタ
Block::Block(int nodeNum){
	position = nodeNum;
}

//デストラクタ
Block::~Block(){}

void Block::setPosition(int nodeNum){
	position = nodeNum;
}

void Block::setColor(char color[8]){
	strcpy(blockColor, color);
}

int Block::getPosition(){
	return position;
}

char* Block::getBlockColor(){
	return blockColor;
}
