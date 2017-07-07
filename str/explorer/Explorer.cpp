
#include"Explorer.h"

//コンストラクタ
Explorer::Explorer(){
	//memset(field, '*', sizeof(field));
	for(int i=0; i<16; i++){
	nodeList.push_back(new Node(i));
	nodeList[i]->setEdge(i);
	}
}
//デストラクタ
Explorer::‾Explorer(){}

//スタート＆ゴール位置設定
void Explorer::set(int start, int goal){
	nodeList[start]->setState('s');
	nodeList[goal]->setState('g');

	for(int i=0; i<16; i++){
		nodeList[i]->setCost(nodeList[i]->distance(nodeList[goal]));
	}

	startNode = nodeList[start];
	goalNode = nodeList[goal];

	return;
}

//フィールド出力
void Explorer::print(){
	for(int i=0; i<16; i++){
		cout << nodeList[i]->getState();
		if(i != 0 && i%4 == 3){
			cout << '¥n';
		}
	}
	return;
}

void Explorer::search(){
	Node* target = startNode;
	Node* next = startNode;
	root.push_back(target->getNodeNum());

	while(next != goalNode){
		int nodeCost = 100;
		root.push_back(target->getNodeNum());
		for(int i=0; i<(int )target->getNextNode().size(); i++){
			if(nodeCost > nodeList[target->getNextNode()[i]]->getCost() && nodeList[target->getNextNode()[i]]->getState() != 'b' && !contains((nodeList[target->getNextNode()[i]])->getNodeNum())){
				root.pop_back();
				nodeCost = nodeList[target->getNextNode()[i]]->getCost();
				next = nodeList[target->getNextNode()[i]];
				root.push_back(next->getNodeNum());
			}
		}
		target = next;
	}

	for(int i=0; i<(int )root.size(); i++){
		cout << root[i] << " ";
	}
	return;
}

void Explorer::setBlocks(int p1, int p2, int p3, int p4){
	blockList.push_back(new Block(p1));
	blockList.push_back(new Block(p2));
	blockList.push_back(new Block(p3));
	blockList.push_back(new Block(p4));

	nodeList[p1]->setState('b');
	nodeList[p2]->setState('b');
	nodeList[p3]->setState('b');
	nodeList[p4]->setState('b');
}

bool Explorer::contains(int num){
	for(int i=0; i<root.size(); i++){
		if(root[i] == num){
			return true;
		}
	}
	return false;
}

//スタート地点から一番近い指定の色のノードを探す
int Explorer::goalExplore(int nowNodeNum, char* color){
	int goalCost=100;
	Node* target;
	int goalNum = 100;

	for(int i=0; i<nodeList.size(); i++){
		target = nodeList[i];
		if(target->distance(nodeList[nowNodeNum]) < goalCost && strcmp(color, target->getNodeColor()) == 0 && target->getState() != 'b'){
			goalNum = target->getNodeNum();
			goalCost = target->distance(nodeList[nowNodeNum]);
		}
	}

	return goalNum;
}
