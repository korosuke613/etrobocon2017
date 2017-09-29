#ifndef _INC_BOARD_ANALYZER
#define _INC_BOARD_ANALYZER

#include "BlockColor.h"
#include <stdint.h>

class BoardAnalyzer
{
public:
	BoardAnalyzer();
	~BoardAnalyzer();
	void set(int8_t *initPositions);
	int8_t getInLeftSquareCount();
	bool hasExchangePatternOnLeftSquare();
	bool hasExchangePatternOnPentagon();
	int8_t getInRightSideCount();
	
private:
	int8_t *positions;
	const int8_t leftSquare[5] = {0, 1, 5, 2, 10};
	const int8_t pentagon[5] = {8, 14, 13, 9, 6};
	const int8_t rightSide[6] = {3, 4, 7, 9, 11, 15};
	const BlockColor BlockArea[16] = {
		BlockColor::Black,
		BlockColor::Red,
		BlockColor::Blue,
		BlockColor::Yellow,
		BlockColor::Blue,
		BlockColor::Yellow,
		BlockColor::Green,
		BlockColor::Red,
		BlockColor::Red,
		BlockColor::Blue,
		BlockColor::Green,
		BlockColor::Green,
		BlockColor::Blue,
		BlockColor::Yellow,
		BlockColor::Red,
		BlockColor::Yellow
	};

};

#endif //_INC_BOARD_ANALYZER