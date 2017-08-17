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
	vector<Node> neighbor;
	int cost;
	BlockColor color;
	bool hasBlock;

public:
	Node() = default;
	Node(int num);
	void setNeighbor(vector<Node> nodes);
	vector<Node> getNeighbor();
	int getNum();
	BlockColor getColor();
	void setHasBlock(bool exists);
	bool getHasBlock();
	~Node();

};

#endif //INC_NODE
