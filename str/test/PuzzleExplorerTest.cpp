
#include <gtest/gtest.h>
#include <PuzzleExplorer.h>

TEST(codeCoversionTest, return10_1_3_8Set12008)
{
	
	// �R���X�g���N�^�̈�����12008������ƁA12008�Ƃ������l�������l�Ƃ���萔�ɑ��
	PuzzleCodeConverter converter(12008);
	// 12008�������ʒu�R�[�h�v�Z���ɏ]���ĉ����ă����o�ϐ��Ɋi�[
	converter.resolvePositionCode();
	
	// ���̃u���b�N�̈ʒu��Ԃ�
	ASSERT_EQ( converter.getPosition(BlockColor::Black), 10);
	
	// �Ԃ̃u���b�N�̈ʒu��Ԃ�
	ASSERT_EQ( converter.getPosition(BlockColor::Red), 1);
	
	// ���̃u���b�N�̈ʒu��Ԃ�
	ASSERT_EQ( converter.getPosition(BlockColor::Yellow), 3);
	
	//�̃u���b�N�̈ʒu��Ԃ�
	ASSERT_EQ( converter.getPosition(BlockColor::Blue), 8);
	
}
