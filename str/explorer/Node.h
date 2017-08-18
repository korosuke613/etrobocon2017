#ifndef _INC_NODE
#define _INC_NODE

#include "BlockColor.h"

#include<cstdlib>
#include<array>
#include<vector>

using namespace std;

class Node{
private:
	int nodeNum;
	vector<Node*> neighbor;
	int cost;
	BlockColor color;
	bool hasBlock;
	int positionX;
	int positionY;

public:
	Node();
	void setNeighbor(vector<Node*> nodes);
	vector<Node*> getNeighbor();
	int getNum();
	BlockColor getColor();
	void setHasBlock(bool exists);
	bool getHasBlock();
	void setPosition(int x, int y);
	int getPositionX();
	int getPositionY();
	void setNum(int num);
	void setColor();
	~Node();
	

};

#endif //INC_NODE
