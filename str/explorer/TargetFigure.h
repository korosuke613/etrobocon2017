#ifndef _INC_TARGET_FIGURE
#define _INC_TARGET_FIGURE

#include "BlockColor.h"

#include <array>

class TargetFigure
{
private:
	array<int, 5> initPositions;
	const array<int, 5> leftSquare = {0, 1, 5, 2, 10};
	const array<int, 5> pentagon = {8, 14, 13, 9, 6};
	const array<int, 5> rightSquare = {0, 7, 3, 4, 11};
	array<int, 5> targets;
	
public:
	TargetFigure();
	~TargetFigure();
	void set(array<int, 5> positions);
	void evaluate();
	int getTargetNum(BlockColor color);
};

#endif //_INC_TARGET_FIGURE