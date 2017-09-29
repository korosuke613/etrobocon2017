#ifndef _INC_TARGET_FIGURE
#define _INC_TARGET_FIGURE

#include "BlockColor.h"

#include <array>

using namespace std;

class TargetFigure
{
private:
	int initPositions[5];
	const int leftSquare[5] = {0, 1, 5, 2, 10};
	const int pentagon[5] = {8, 14, 13, 9, 6};
	const int rightSquare[5] = {0, 7, 3, 4, 11};
	int targets[5];
	
public:
	TargetFigure();
	~TargetFigure();
	void set(int positions[5]);
	void evaluate();
	int getTargetNum(BlockColor color);
	int getNumberInLeftSquare(int[]);
};

#endif //_INC_TARGET_FIGURE