
#include"Block.h"
#include<string.h>

//�R���X�g���N�^
Block::Block(int nodeNum){
	position = nodeNum;
}

//�f�X�g���N�^
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
