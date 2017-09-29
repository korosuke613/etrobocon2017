#ifndef _INC_NODE
#define _INC_NODE

#include "BlockColor.h"

#include<cstdlib>


class Node{
public:
	Node();
	~Node();
	void setNeighbor(Node** nodes);
	Node** getNeighbor();
	int getNum();
	BlockColor getColor();
	void setHasBlock(bool exists);
	bool getHasBlock();
	void setPosition(int x, int y);
	int getPositionX();
	int getPositionY();
	void setNum(int num);
	void setColor();
	
private:
	int nodeNum;
	Node* neighbor[5];
	BlockColor color;
	bool hasBlock;
	int positionX;
	int positionY;

};

#endif //INC_NODE
