
#include <gtest/gtest.h>
#include <PuzzleCodeConverter.h>

TEST(codeCoversionTest, return10_1_3_8Set12008)
{
	
	// コンストラクタの引数に12008を入れると、12008という数値を初期値とする定数に代入
	PuzzleCodeConverter converter(12008);
	// 12008を初期位置コード計算式に従って解いてメンバ変数に格納
	converter.resolvePositionCode();
	
	// 黒のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Black), 10);
	
	// 赤のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Red), 1);
	
	// 黄のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Yellow), 3);
	
	//青のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Blue), 8);
	
}

TEST(codeConversionTest, return3_1_6_9Set2725)
{

	// コンストラクタの引数に2725を入れると、2725という数値を初期値とする定数に代入
	PuzzleCodeConverter converter(2725);
	// 2725を初期位置コード計算式に従って解いてメンバ変数に格納
	converter.resolvePositionCode();
	
	// 黒のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Black), 3);
	
	// 赤のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Red), 1);
	
	// 黄のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Yellow), 6);
	
	//青のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Blue), 9);
}

TEST(codeConversionTest, return1_2_3_4Set146)
{
	// コンストラクタの引数に146を入れると、146という数値を初期値とする定数に代入
	PuzzleCodeConverter converter(146);
	// 146を初期位置コード計算式に従って解いてメンバ変数に格納
	converter.resolvePositionCode();
	
	// 黒のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Black), 1);
	
	// 赤のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Red), 2);
	
	// 黄のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Yellow), 3);
	
	//青のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Blue), 4);
}

//入力の最大値
TEST(codeConversionTest, return15_11_11_11Set19964)
{
	// コンストラクタの引数に19964を入れると、19964という数値を初期値とする定数に代入
	PuzzleCodeConverter converter(19964);
	// 19964を初期位置コード計算式に従って解いてメンバ変数に格納
	converter.resolvePositionCode();
	
	// 黒のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Black), 15);
	
	// 赤のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Red), 11);
	
	// 黄のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Yellow), 11);
	
	//青のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Blue), 11);
}

//入力の最小値
TEST(codeConversionTest, return1_1_3_2Set23)
{
	// コンストラクタの引数に23を入れると、23という数値を初期値とする定数に代入
	PuzzleCodeConverter converter(23);
	// 23を初期位置コード計算式に従って解いてメンバ変数に格納
	converter.resolvePositionCode();
	
	// 黒のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Black), 1);
	
	// 赤のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Red), 1);
	
	// 黄のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Yellow), 3);
	
	//青のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Blue), 2);
}

//境界値-最後のループでresultが11になるとき
TEST(codeConversionTest, return11_11_11_9Set16102)
{
	// コンストラクタの引数に14638を入れると、14638という数値を初期値とする定数に代入
	PuzzleCodeConverter converter(14638);
	// 14638を初期位置コード計算式に従って解いてメンバ変数に格納
	converter.resolvePositionCode();
	
	// 黒のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Black), 11);
	
	// 赤のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Red), 11);
	
	// 黄のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Yellow), 11);
	
	//青のブロックの位置を返す
	ASSERT_EQ( converter.getPosition(BlockColor::Blue), 9);
}
