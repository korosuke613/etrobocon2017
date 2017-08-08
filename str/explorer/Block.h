#ifndef _INC_BLOCK
#define _INC_BLOCK

#include<cstdlib>
#include<iostream>

using namespace std;

class Block{
private:
	int position;
	char* blockColor;
	
public:
	enum Color{Black, Red, Yellow, Blue, Green};
	Block(int nodeNum);
	void setPosition(int nodeNum);
	void setColor(char color[8]);
	int getPosition();
	char* getBlockColor();
	~Block();
};

#endif //INC_BLOCK
