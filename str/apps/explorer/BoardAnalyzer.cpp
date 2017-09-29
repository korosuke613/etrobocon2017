#include "BoardAnalyzer.h"

BoardAnalyzer::BoardAnalyzer()
{
	
}

BoardAnalyzer::~BoardAnalyzer()
{
	
}

// �u���b�N�̔z�u�̓���
void BoardAnalyzer::set(int* initPositions)
{
	positions = initPositions;
}

// �����l�p�`���̃u���b�N�̌�
int BoardAnalyzer::getInLeftSquareCount()
{
	int leftSquareCount = 0;
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			if(positions[i] == leftSquare[j])
			{
				leftSquareCount++;
			}
		}
	}
	
	return leftSquareCount;
}

