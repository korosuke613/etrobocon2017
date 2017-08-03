
#include <gtest/gtest.h>
#include <PuzzleExplorer.h>

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
