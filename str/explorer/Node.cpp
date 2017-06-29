
#include"Node.h"
#include<string.h>

//コンストラクタ
Node::Node(int num){
	state = '*';
	nodeNum = num;
	
	if(num == 0 || num == 1 || num == 4 || num == 5){
		strcpy(nodeColor, "red");
	}else if(num == 2 || num == 3 || num == 6 || num == 7){
		strcpy(nodeColor, "yellow");
	}else if(num == 8 || num == 9 || num == 12 || num == 13){
		strcpy(nodeColor, "blue");
	}else if(num == 10 || num == 11 || num == 14 || num == 15){
		strcpy(nodeColor, "green");
	}

	//cout << nodeColor << endl;
}

//デストラクタ
Node::~Node(){}

//周囲のノードの設定
void Node::setEdge(int nodeNum){
	int target = nodeNum-5;

	for(int i=0; i<11; i++){
		if((i !=0 && i%4 == 3) || target+i == nodeNum){
			continue;
		}
		nextNode.push_back(target+i);
	}

	//隣り合わないノードの排除
	if(nextNode[0]%4 == 3){
		nextNode[0] = nextNode[3] = nextNode[5] = -1;
	}

	if(nextNode[2]%4 == 0){
		nextNode[2] = nextNode[4] = nextNode[7] = -1;
	}
	
	int count = 0;
	while(count < (int )nextNode.size()){
		if(nextNode[count] < 0 || nextNode[count] > 15){
			nextNode.erase(nextNode.begin()+count);
			count = count-1;
		}
		count++;
	}

	return;
}

void Node::setState(char state){
	this->state = state;
	return;
}

char Node::getState(){
	return state;
}

//任意のノードまでの距離の計算
int Node::distance(Node* node){
	int x = (nodeNum%4 - node->nodeNum%4)*(nodeNum%4 - node->nodeNum%4);
	int y = (nodeNum/4 - node->nodeNum/4)*(nodeNum/4 - node->nodeNum/4);

	return x+y;
}

vector<int> Node::getNextNode(){
	return nextNode;
}

int Node::getNodeNum(){
	return nodeNum;
}

int Node::getCost(){
	return cost;
}

char* Node::getNodeColor(){
	return nodeColor; 
}

void Node::setCost(int num){
	cost = num;
}
