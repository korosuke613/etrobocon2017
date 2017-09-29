#ifndef _INC_TARGET_FIGURE
#define _INC_TARGET_FIGURE

#include "BlockColor.h"
#include "BoardAnalyzer.h"

#include <array>

using namespace std;

class TargetFigure
{
private:
	int8_t *initPositions;
	const int8_t leftSquare[5] = {0, 1, 5, 2, 10};
	const int8_t pentagon[5] = {8, 14, 13, 9, 6};
	const int8_t rightSquare[5] = {0, 7, 3, 4, 11};
	int8_t targets[5];
	BoardAnalyzer analyzer;
	
public:
	TargetFigure();
	~TargetFigure();
	void set(int8_t *positions);
	void evaluate();
	int8_t getTargetNum(BlockColor color);
};

#endif //_INC_TARGET_FIGURE