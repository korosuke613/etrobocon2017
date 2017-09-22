
#include"Node.h"


//コンストラクタ
Node::Node()
{
	nodeNum = 0;
	hasBlock = false;
	positionX=0;
	positionY=0;
	
	

}

//デストラクタ
Node::~Node(){}

void Node::setNum(int num)
{
	nodeNum = num;
}

void Node::setColor()
{
	// ノードの色設定
	if(nodeNum == 1 || nodeNum == 7 || nodeNum == 8 || nodeNum == 14)
	{
		color = BlockColor::Red;
	}else if(nodeNum == 3 || nodeNum == 5 || nodeNum == 13 || nodeNum == 15)
	{
		color = BlockColor::Yellow;
	}else if(nodeNum == 2 || nodeNum == 4 || nodeNum == 9 || nodeNum == 12)
	{
		color = BlockColor::Blue;
	}else if(nodeNum == 6 || nodeNum == 10 || nodeNum == 11)
	{
		color = BlockColor::Green;
	}else if(nodeNum == 0)
	{
		color = BlockColor::Black;
	}
	
}
//周囲のノードの設定
void Node::setNeighbor(vector<Node*> nodes)
{
	neighbor = nodes;
	return;
}

// 隣接ノード取得
vector<Node*> Node::getNeighbor()
{
	return neighbor;
}

// ノードの位置番号取得
int Node::getNum()
{
	return nodeNum;
}

// ノードの色取得
BlockColor Node::getColor()
{
	return color; 
}

// ノードがブロックを持っているかの判定の変化
void Node::setHasBlock(bool exists)
{
	hasBlock = exists;
}

bool Node::getHasBlock()
{
	return hasBlock;
}

void Node::setPosition(int x, int y)
{
	positionX = x;
	positionY = y;
}

int Node::getPositionX()
{
	return positionX;
}

int Node::getPositionY()
{
	return positionY;
}

