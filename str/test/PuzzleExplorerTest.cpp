
#include <gtest/gtest.h>
#include <PuzzleExplorer.h>

TEST(nearestBlockExplorerTest, return5SetBlack2Red5Yello8Blue15Green4)
{
	array<int, 5> blockPosition{2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer(blockPosition);
	
	//最寄りのブロックを探す
	ASSERT_EQ( explorer.getNearestBlockPosition(), 8);
	
}

TEST(nearestBlockExplorerTest, return12SetBlack11Red2Yello6Blue8Green12)
{
	array<int, 5> blockPosition{11,2,6,8,12};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer(blockPosition);
	
	//最寄りのブロックを探す
	ASSERT_EQ( explorer.getNearestBlockPosition(), 12);
	
}
