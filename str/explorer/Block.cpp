
#include"Block.h"
#include<string.h>

//�R���X�g���N�^
Block::Block(int num)
{
	position = num;
}

//�f�X�g���N�^
Block::~Block(){}

void Block::setPosition(int nodeNum)
{
	position = nodeNum;
}

void Block::setColor(BlockColor blockColor)
{
	color = blockColor;
}

int Block::getPosition()
{
	return position;
}

BlockColor Block::getBlockColor()
{
	return color;
}
