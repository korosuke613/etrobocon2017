#include "TargetFigure.h"


TargetFigure::TargetFigure()
{
	
}

TargetFigure::~TargetFigure()
{
	
}

// �u���b�N�̏����ʒu�ݒ�
void TargetFigure::set(int8_t *positions)
{
	initPositions = positions;
	analyzer.set(initPositions);
	
}

// �����ʒu��]�����A�ڕW�Ƃ���}�`�����肷��
void TargetFigure::evaluate()
{
	// �����l�p�`�ɂ���u���b�N�̌���3�ȏ�ł��� ���� �܊p�`�ɂ���u���b�N�������p�^�[���ł���ꍇ �܂��� �����l�p�`�ɂ���u���b�N�̌���2�ȉ��ł��� ���� �����l�p�`�ɂ���u���b�N�������p�^�[���ł��� ���� �܊p�`�ɂ���u���b�N�������p�^�[���ł���ꍇ
	if((analyzer.getInLeftSquareCount() >= 3 && analyzer.hasExchangePatternOnPentagon() == true) || (analyzer.getInLeftSquareCount() <= 2 && analyzer.hasExchangePatternOnLeftSquare() == true && analyzer.hasExchangePatternOnPentagon() == true))
	{
		// �ڕW�}�`���E���l�p�`�Ƃ���
		for(int i=0; i<5; i++)
		{
			targets[i] = rightSquare[i];
		}
	}else 
	// �����l�p�`�ɂ���u���b�N�̌���2�ȉ��ł��� ���� �����l�p�`�ɂ���u���b�N�������p�^�[���łȂ� ���� �������E���ɂ���u���b�N��2�ȉ��ł���ꍇ
	if(analyzer.getInLeftSquareCount() <= 2 && analyzer.hasExchangePatternOnLeftSquare() == false && analyzer.getInRightSideCount() <= 2)
	{
		// �ڕW�}�`�����l�p�`�Ƃ���
		for(int i=0; i<5; i++)
		{
			targets[i] = leftSquare[i];
		}
	}else
	{
		// �ڕW�}�`���܊p�`�Ƃ���
		for(int i=0; i<5; i++)
		{
			targets[i] = pentagon[i];
		}
	}
	
}

// �e�F�̖ڕW�Ƃ���ʒu�ԍ����擾����
int8_t TargetFigure::getTargetNum(BlockColor color)
{
	int8_t targetNum = 0;
	
	switch(color)
	{
	case BlockColor::Black:
		targetNum = targets[0];
		break;
		
	case BlockColor::Red:
		targetNum = targets[1];
		break;
		
	case BlockColor::Yellow:
		targetNum = targets[2];
		break;
		
	case BlockColor::Blue:
		targetNum = targets[3];
		break;
		
	case BlockColor::Green:
		targetNum = targets[4];
		break;
	}
	
	return targetNum;
}

