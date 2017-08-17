
#include"Node.h"


//コンストラクタ
Node::Node(int num)
{
	nodeNum = num;
	hasBlock = false;
	
	// ノードの色設定
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

//デストラクタ
Node::~Node(){}


//周囲のノードの設定
void Node::setNeighbor(vector<Node> nodes)
{
	neighbor = nodes;
	return;
}

// 隣接ノード取得
vector<Node> Node::getNeighbor()
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

