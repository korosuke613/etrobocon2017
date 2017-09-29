#ifndef _INC_PUZZLE_EXPLORER_
#define _INC_PUZZLE_EXPLORER

#include "Block.h"
#include "Node.h"
#include <stdio.h>

#include <queue>

using namespace std;

#define TARGET_BLACK 0
#define TARGET_RED 1
#define TARGET_YELLOW 5
#define TARGET_BLUE 2
#define TARGET_GREEN 10

class PuzzleExplorer
{
public:
	PuzzleExplorer();
	~PuzzleExplorer();
	void init(int *blockPositions);
	BlockColor getNodeColor(int num);
	Node** getMyNeighbor();
	void setMyPosition(int num);
	int getNearestBlockPosition();
	int* getRoot(int startNode, int goalNode);
	int getCost(Node node1, Node node2);
	
private:
	int myPosition;
	Block blockList[5];
	Node nodeList[16];
	const int neighborList[16][5] = {
		{6,8,9,13,14},
		{2,5,10,-1,-1},
		{1,3,5,6,-1},
		{2,4,6,7,-1},
		{3,7,11,-1,-1},
		{1,2,8,10,-1},
		{0,2,3,8,9},
		{3,4,9,11,-1},
		{0,5,6,12,13},
		{0,6,7,14,15},
		{1,5,12,-1,-1},
		{4,7,15,-1,-1},
		{8,10,13,-1,-1},
		{0,8,12,14,-1},
		{0,9,13,15,-1},
		{9,11,14,-1,-1}
	};
	const int nodePositionList[16][2] = {
		{6,3},
		{0,0},
		{4,0},
		{8,0},
		{12,0},
		{2,1},
		{6,1},
		{10,1},
		{4,2},
		{8,2},
		{1,3},
		{11,3},
		{3,4},
		{5,4},
		{7,4},
		{9,4}
	};
	int root[16]={};
	void setNodes();
	void setBlocks(int *blockPositions);
	void setNeighborNode();

};

#endif //_INC_PUZZLE_EXPLORER