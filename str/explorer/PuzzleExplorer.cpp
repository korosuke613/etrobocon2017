
#include "PuzzleExplorer.h"

// コンストラクタ
PuzzleExplorer::PuzzleExplorer()
{
	myPosition = 0;
}

// デストラクタ
PuzzleExplorer::~PuzzleExplorer(){}

// ブロック並べエリアのマップ、ブロックの初期配置などの初期設定
void PuzzleExplorer::init(int *blockPositions)
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

// ノードの設定(位置番号、色、位置座標)
void PuzzleExplorer::setNodes()
{
	for(int i=0; i<16; i++)
	{
		Node node;
		node.setNum(i);
		node.setColor();
		node.setPosition(nodePositionList[i][0], nodePositionList[i][1]);
		nodeList[i] = node;
		
	}
}

// ブロック設定
void PuzzleExplorer::setBlocks(int *blockPositions)
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

// 隣接ノードの設定
void PuzzleExplorer::setNeighborNode()
{
	//nodeListから隣接ノードを取得
	for(int i=0; i<16;i++)
	{
		Node* neighbor[5] = {};
		
		for(int j=0; j<5; j++)
		{
			// 隣接ノード番号が-1の時(隣接ノードがないとき)nullポインタを入れる
			if(neighborList[i][j] == -1)
			{
				neighbor[j] = nullptr;
				continue;
			}
			Node* node = &nodeList[neighborList[i][j]];
			neighbor[j] = node;
		}
		
		nodeList[i].setNeighbor(neighbor);
		neighbor[5] = {};
	}
	return;
}

// 位置番号からノードの色を返す
BlockColor PuzzleExplorer::getNodeColor(int num)
{
	return nodeList[num].getColor();
}

// 現在地の隣接ノード取得
Node** PuzzleExplorer::getMyNeighbor()
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
		Node** nodes = node.getNeighbor();
		
		// 隣接ノードをキューに格納 
		for(int i=0; i<5; i++){
			
			// 隣接ノードがnullの時は飛ばす
			if(nodes[i] == nullptr)continue;
			
			que.push(*nodes[i]);
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

// 2つのノード間の経路探索
int* PuzzleExplorer::getRoot(int startNode, int goalNode)
{
	Node node = nodeList[startNode];
	Node goal = nodeList[goalNode];
	int i=0;
	
	// rootに経路を格納
	root[i] = node.getNum();
	i++;
	
	// ゴールノードに到着するまで探索
	while(node.getNum() != goal.getNum())
	{	
		int cost = 1000;
		Node** explorerNodes = node.getNeighbor();
		Node nextNode;
		
		// 隣接ノードからゴールまでのコストが低いノードを次の探索ノードに選択
		for(int j=0; j<5; j++)
		{
			//隣接ノードがnullの時飛ばす
			if(explorerNodes[j] == nullptr)continue;
			
			// ゴールノードまでの距離コストが小さければ更新
			int neighborCost = getCost(*explorerNodes[j], goal);
			if(cost > neighborCost)
				{
					cost = neighborCost;
					nextNode = *explorerNodes[j];
				}
		}
		
		root[i] = nextNode.getNum();
		node = nextNode;
		i++;
	}
	
	return root;
}

// ノード間の距離コストを計算
int PuzzleExplorer::getCost(Node node1, Node node2)
{
	int cost = (node1.getPositionX() - node2.getPositionX())*(node1.getPositionX() - node2.getPositionX()) + (node1.getPositionY() - node2.getPositionY())*(node1.getPositionY() - node2.getPositionY());
	
	return cost;
}
