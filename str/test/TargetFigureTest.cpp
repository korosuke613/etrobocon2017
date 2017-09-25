#include <gtest/gtest.h>
#include <TargetFigure.h>

//�u���b�N�̏����ʒu����ڕW�Ƃ���}�`�����肷��

TEST(TargetFigureTest, returnBlack0Red1Yellow5Blue2Green10SetBlack8Red13Yellow9Blue6Green14)
{
	TargetFigure targetFigure;
	
	// �e�u���b�N�̏����ʒu�����
	int initPositions[5] = {8,13,9,6,14};// �� �� �� �� ��
	targetFigure.set(initPositions); 
	// �����ʒu��]�����A�ڕW�}�`�����肷��
	targetFigure.evaluate();
	
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Black), 0);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Red), 1);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Yellow), 5);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Blue), 2);
	ASSERT_EQ( targetFigure.getTargetNum(BlockColor::Green), 10);
	
}