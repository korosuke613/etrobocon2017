
#include "PuzzleExplorer.h"

// コンストラクタ
PuzzleExplorer::PuzzleExplorer()
{
	myPosition = 0;
}

// デストラクタ
PuzzleExplorer::~PuzzleExplorer(){}

// ブロック並べエリアのマップ、ブロックの初期配置などの初期設定
void PuzzleExplorer::init(array<int, 5> blockPositions)
{
	//機体初期位置10
	setMyPosition(10);
	
	// ノードの設定
	setNodes();
	
	//ブロックの位置設定
	setBlocks(blockPositions);
	
	// 隣接ノード設定
	setNeighborNode();
	
}

// 現在地の変更
void PuzzleExplorer::setMyPosition(int num)
{
	myPosition = num;
	return;
}

// ノードの設定(位置番号、色)
void PuzzleExplorer::setNodes()
{
	for(int i=0; i<16; i++)
	{
		Node node(i);
		nodeList[i] = node;
	}
}

// 隣接ノードの設定
void PuzzleExplorer::setNeighborNode()
{
	//nodeListから隣接ノードを取得
	for(int i=0; i<16;i++)
	{
		vector<Node> neighbor;
		
		for(int j=0; j<5; j++)
		{
			// 配列の数をそろえるために入れた-1を取り除く
			if(neighborList[i][j] == -1)
			{
				continue;
			}
			neighbor.push_back(nodeList[neighborList[i][j]]);
		}
		
		nodeList[i].setNeighbor(neighbor);
		neighbor.clear();
	}
	return;
}

// ブロック設定
void PuzzleExplorer::setBlocks(array<int, 5> blockPositions)
{
	for(int i=0; i<5; i++)
	{
		Block block(blockPositions[i]);
		blockList[i] = block;
		
		// ブロックを持つノード設定
		nodeList[blockPositions[i]].setHasBlock(true);
	}
	
	blockList[0].setColor(BlockColor::Black);
	blockList[1].setColor(BlockColor::Red);
	blockList[2].setColor(BlockColor::Yellow);
	blockList[3].setColor(BlockColor::Blue);
	blockList[4].setColor(BlockColor::Green);
	
	return;
}

// 位置番号からノードの色を返す
BlockColor PuzzleExplorer::getNodeColor(int num)
{
	return nodeList[num].getColor();
}

// 現在地の隣接ノード取得
vector<Node> PuzzleExplorer::getMyNeighbor()
{
	return nodeList[myPosition].getNeighbor();
}

// 現地点から最寄りのブロックの位置を返す
int PuzzleExplorer::getNearestBlockPosition()
{	
	Node node = nodeList[myPosition];
	queue<Node> que;
	
	// ブロックを持つノードが見つかるまで幅優先探索
	while(!node.getHasBlock())
	{
		vector<Node> nodes = node.getNeighbor();
		
		// 隣接ノードをキューに格納 
		for(int i=0; i<nodes.size(); i++){
			que.push(nodes[i]);
		}
		
		node = que.front();
		
		// キューの先頭がブロックを持っていたら終了
		if(que.front().getHasBlock())
		{
			break;
		}
		
		// 先頭要素の削除
		que.pop();
	}
	
	return node.getNum();
}
