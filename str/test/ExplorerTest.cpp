#include<iostream>
#include<bits/stdc++.h>
#include"Explorer.h"

using namespace std;


int main(){
	int start,goal;
	int p1, p2, p3, p4;
	Explorer* explorer = new Explorer();

	cout << "set Blocks" << '\n';
	cin >> p1 >> p2 >> p3 >> p4;
	explorer->setBlocks(p1, p2, p3, p4);
	
	//cout << "set start&goal" << '\n';
	//cin >> start >> goal;
	explorer->set(15, explorer->goalExplore(15, "green"));

	explorer->print();

	explorer->search();


	return 0;
}