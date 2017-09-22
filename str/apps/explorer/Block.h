#ifndef _INC_BLOCK
#define _INC_BLOCK

#include <cstdlib>

#include "BlockColor.h"

using namespace std;

class Block{
private:
	int position;
	BlockColor color;
	
public:
	Block() = default;
	Block(int nodeNum);
	void setPosition(int nodeNum);
	void setColor(BlockColor blockColor);
	int getPosition();
	BlockColor getBlockColor();
	~Block();
};

#endif //INC_BLOCK
