#include "BoardAnalyzer.h"

BoardAnalyzer::BoardAnalyzer()
{
	
}

BoardAnalyzer::~BoardAnalyzer()
{
	
}

// �u���b�N�̔z�u�̓���
void BoardAnalyzer::set(int *initPositions)
{
	positions = initPositions;
}

// �����l�p�`���̃u���b�N�̌�
int BoardAnalyzer::getInLeftSquareCount()
{
	int leftSquareCount = 0;
	
	// �u���b�N�̏����ʒu�ō����l�p�`��ɂ�����̂��J�E���g
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

bool BoardAnalyzer::hasExchangePatternOnLeftSquare()
{
	// 
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			if()
			{
			
			}
		}
	}
	return ;
}

