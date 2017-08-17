#ifndef _INC_PUZZLE_EXPLORER_
#define _INC_PUZZLE_EXPLORER

#include "Block.h"
#include "Node.h"

#include <array>
#include <queue>

using namespace std;

class PuzzleExplorer
{
private:
	int myPosition;
	array<Block, 5> blockList;
	array<Node, 16> nodeList;
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
	void setNodes();
	void setBlocks(array<int, 5> blockPositions);
	void setNeighborNode();

public:
	PuzzleExplorer();
	~PuzzleExplorer();
	void init(array<int, 5> blockPositions);
	BlockColor getNodeColor(int num);
	vector<Node> getMyNeighbor();
	void setMyPosition(int num);
	int getNearestBlockPosition();

};

#endif //_INC_PUZZLE_EXPLORER