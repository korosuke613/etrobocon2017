/**
 * AddTest.cpp
 * �w�b�_�t�@�C���͏����Ȃ��Ă������炵��
 */

// googletest/googletest/include���̃f�B���N�g������уt�@�C�����C���N���[�h����B
#include <gtest/gtest.h>

// �Ȃ񂩂̃e�X�g�R�[�h
int add( int x, int y )
{
    return x + y;
}

// �e�X�g�P�[�X���ƃe�X�g���e���L�q����B
// �e�X�g�P�[�X���͂��̃e�X�g�N���X���A�e�X�g���e�͋�̓I�ȃe�X�g���\�b�h��������Ƃ��������B
TEST( AddTest, get3add1and2 )
{
    // �݂�ȑ�D��assertEqual��
    // assertThat���ɑ���������̂͂Ȃ����ۂ����ǁAASSERT_EQ���ŃG���[�������������ɂ́A�������R���\�[����ɕ\�����Ă���銮�S��ʌ݊�
    ASSERT_EQ( add( 1, 2 ), 3 );
}