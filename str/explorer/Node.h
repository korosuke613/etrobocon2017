#ifndef _INC_NODE
#define _INC_NODE

#include<cstdlib>
#include<iostream>
#include<vector>

using namespace std;

class Node{
private:
	int nodeNum;
	char state;
	vector<int> nextNode;
	int cost;
	char nodeColor[8];

public:
	Node(int num);
	void setEdge(int nodeNum);
	void setState(char state);
	char getState();
	int distance(Node* node);
	vector<int> getNextNode();
	int getNodeNum();
	int getCost();
	char* getNodeColor();
	void setCost(int num);
	~Node();

};

#endif //INC_NODE
