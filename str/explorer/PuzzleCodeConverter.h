#ifndef _INC_PUZZLE_CONVERTER
#define _INC_PUZZLE_CONVERTER

#include "BlockColor.h"
#include <map>

class PuzzleCodeConverter
{
private:
	int mPuzzleCode;
	std::map<std::string, int> blockMap;

public:
	PuzzleCodeConverter();
	PuzzleCodeConverter(int puzzleCode);
	~PuzzleCodeConverter();
	void resolvePositionCode();
	int getPosition(BlockColor color);
	int redToBlackPosition(int redNum);
	int yellowToBlackPosition(int yellowNum);
	int blueToBlackPosition(int blueNum);
};


#endif //_INC_PUZZLE_CONVERTER
