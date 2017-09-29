#include "BoardAnalyzer.h"

BoardAnalyzer::BoardAnalyzer()
{
	
}

BoardAnalyzer::~BoardAnalyzer()
{
	
}

// �u���b�N�̔z�u�̓���
void BoardAnalyzer::set(int8_t *initPositions)
{
	positions = initPositions;
}

// �����l�p�`���̃u���b�N�̌�
int8_t BoardAnalyzer::getInLeftSquareCount()
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

// �����l�p�`��̌����p�^�[�������o
bool BoardAnalyzer::hasExchangePatternOnLeftSquare()
{
	bool isExchangePattern = false;
	
	// �����ʒu�̒��ŁA�����l�p�`��ɂ�����̂��擾
	for(int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			if(positions[i] == leftSquare[j] && positions[j] == leftSquare[i])
			{
				isExchangePattern = true;
			}
		}
	}
	
	return isExchangePattern;
}

