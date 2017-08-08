#ifndef _INC_PUZZLE_EXPLORER_
#define _INC_PUZZLE_EXPLORER

#include "Block.h"
#include <array>

using namespace std;

class PuzzleExplorer
{
public:
	PuzzleExplorer(array<int, 5> blockPositions);
	~PuzzleExplorer();
	int getNearestBlockPosition();
	
private:
	array<int, 5> blockPositions;
	int myPosition;
};

#endif //_INC_PUZZLE_EXPLORER