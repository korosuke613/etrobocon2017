
#include"Node.h"


//�R���X�g���N�^
Node::Node(int num)
{
	nodeNum = num;
	hasBlock = false;
	
	// �m�[�h�̐F�ݒ�
	if(num == 1 || num == 7 || num == 8 || num == 14)
	{
		color = BlockColor::Red;
	}else if(num == 3 || num == 5 || num == 13 || num == 15)
	{
		color = BlockColor::Yellow;
	}else if(num == 2 || num == 4 || num == 9 || num == 12)
	{
		color = BlockColor::Blue;
	}else if(num == 6 || num == 10 || num == 11)
	{
		color = BlockColor::Green;
	}else if(num == 0)
	{
		color = BlockColor::Black;
	}

}

//�f�X�g���N�^
Node::~Node(){}


//���͂̃m�[�h�̐ݒ�
void Node::setNeighbor(vector<Node> nodes)
{
	neighbor = nodes;
	return;
}

// �אڃm�[�h�擾
vector<Node> Node::getNeighbor()
{
	return neighbor;
}

// �m�[�h�̈ʒu�ԍ��擾
int Node::getNum()
{
	return nodeNum;
}

// �m�[�h�̐F�擾
BlockColor Node::getColor()
{
	return color; 
}

// �m�[�h���u���b�N�������Ă��邩�̔���̕ω�
void Node::setHasBlock(bool exists)
{
	hasBlock = exists;
}

bool Node::getHasBlock()
{
	return hasBlock;
}

