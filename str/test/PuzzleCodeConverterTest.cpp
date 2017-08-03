
#include <gtest/gtest.h>
#include <PuzzleCodeConverter.h>

//初期位置コードから各ブロックの位置を算出するテスト

TEST(codeCoversionTest, returnBlack10Red1Yellow3Blue8Set12008)
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

TEST(codeConversionTest, returnBlack3Red1Yellow6Blue9Set2725)
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

TEST(codeConversionTest, returnBlack1Red2Yellow3Blue4Set146)
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
TEST(codeConversionTest, returnBlack15Red11Yellow11Blue11Set19964)
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
TEST(codeConversionTest, returnBlack1Red1Yellow3Blue2Set23)
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
TEST(codeConversionTest, returnBlack11Red11Yellow11Blue9Set16102)
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


//各ブロックの位置コードを黒ブロックの位置コードへ統一
TEST(positionConversionTest, returnRed2SetRed1)
{

	PuzzleCodeConverter converter;
	
	// 赤ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.redToBlackPosition(1), 2);
}

TEST(positionCodeConversionTest, returnRed15SetRed11)
{
	PuzzleCodeConverter converter;
	
	//赤ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.redToBlackPosition(11), 15);
}

TEST(positionCodeConversionTest, returnRed9SetRed6)
{
	PuzzleCodeConverter converter;
	
	//赤ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.redToBlackPosition(6), 9);
}

TEST(positionCodeConversionTest, returnRed6SetRed5)
{
	PuzzleCodeConverter converter;
	
	//赤ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.redToBlackPosition(5), 6);
}


//各ブロックの位置コードを黒ブロックの位置コードへ統一
TEST(positionConversionTest, returnYellow1SetYellow1)
{

	PuzzleCodeConverter converter;
	
	// 黄ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.yellowToBlackPosition(1), 1);
}

TEST(positionCodeConversionTest, returnYellow14SetYellow11)
{
	PuzzleCodeConverter converter;
	
	//黄ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.yellowToBlackPosition(11), 14);
}

TEST(positionCodeConversionTest, returnYellow8SetYellow6)
{
	PuzzleCodeConverter converter;
	
	//黄ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.yellowToBlackPosition(6), 8);
}

TEST(positionCodeConversionTest, returnYellow4SetYellow3)
{
	PuzzleCodeConverter converter;
	
	//黄ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.yellowToBlackPosition(3), 4);
}


//各ブロックの位置コードを黒ブロックの位置コードへ統一
TEST(positionConversionTest, returnBlue1SetBlue1)
{

	PuzzleCodeConverter converter;
	
	// 青ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.blueToBlackPosition(1), 1);
}

//各ブロックの位置コードを黒ブロックの位置コードへ統一
TEST(positionConversionTest, returnBlue15SetBlue11)
{

	PuzzleCodeConverter converter;
	
	// 青ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.blueToBlackPosition(11), 15);
}

//各ブロックの位置コードを黒ブロックの位置コードへ統一
TEST(positionConversionTest, returnBlue3SetBlue2)
{

	PuzzleCodeConverter converter;
	
	// 青ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.blueToBlackPosition(2), 3);
}

//各ブロックの位置コードを黒ブロックの位置コードへ統一
TEST(positionConversionTest, returnBlue5SetBlue3)
{

	PuzzleCodeConverter converter;
	
	// 青ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.blueToBlackPosition(3), 5);
}

//各ブロックの位置コードを黒ブロックの位置コードへ統一
TEST(positionConversionTest, returnBlue10SetBlue7)
{

	PuzzleCodeConverter converter;
	
	// 青ブロックの位置を黒ブロックの位置へ変換
	ASSERT_EQ( converter.blueToBlackPosition(7), 10);
}


