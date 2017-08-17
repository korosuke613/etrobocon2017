
#include <gtest/gtest.h>
#include <PuzzleExplorer.h>


// ブロック並べエリアのノードの色を返す
TEST(NodeColorTest, returnRedSetBlockNumber1)
{
	array<int, 5> blockPosition{2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//位置番号1のノードの色
	ASSERT_EQ( explorer.getNodeColor(1), BlockColor::Red);
}

TEST(NodeColorTest, returnBlueSetBlockNumber2)
{
	array<int, 5> blockPosition{2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//位置番号2のノードの色
	ASSERT_EQ( explorer.getNodeColor(2), BlockColor::Blue);
}

TEST(NodeColorTest, returnYellowSetBlockNumber3)
{
	array<int, 5> blockPosition{2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//位置番号3のノードの色
	ASSERT_EQ( explorer.getNodeColor(3), BlockColor::Yellow);
}

TEST(NodeColorTest, returnGreenSetBlockNumber11)
{
	array<int, 5> blockPosition{2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//位置番号1のノードの色
	ASSERT_EQ( explorer.getNodeColor(11), BlockColor::Green);
}

// 隣接ノードの確認テスト
TEST(NeiborNodeTest, returnNode1Node5Node12SetMyPosition11)
{
	array<int, 5> blockPosition{2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	vector<Node> neighbor = explorer.getMyNeighbor();
	
	//位置番号11のノードの隣接ノード
	ASSERT_EQ( neighbor[0].getNum(), 1);
	ASSERT_EQ( neighbor[1].getNum(), 5);
	ASSERT_EQ( neighbor[2].getNum(), 12);
}

TEST(NeiborNodeTest, returnNode6Node8Node9Node13Node14SetMyPosition0)
{
	array<int, 5> blockPosition{2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	explorer.setMyPosition(0);
	
	vector<Node> neighbor = explorer.getMyNeighbor();
	
	
	//位置番号0のノードの隣接ノード
	ASSERT_EQ( neighbor[0].getNum(), 6);
	ASSERT_EQ( neighbor[1].getNum(), 8);
	ASSERT_EQ( neighbor[2].getNum(), 9);
	ASSERT_EQ( neighbor[3].getNum(), 13);
	ASSERT_EQ( neighbor[4].getNum(), 14);
}

TEST(NeiborNodeTest, returnNode1Node2Node8Node10SetMyPosition5)
{
	array<int, 5> blockPosition{2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	explorer.setMyPosition(5);
	
	vector<Node> neighbor = explorer.getMyNeighbor();
	
	
	//位置番号0のノードの隣接ノード
	ASSERT_EQ( neighbor[0].getNum(), 1);
	ASSERT_EQ( neighbor[1].getNum(), 2);
	ASSERT_EQ( neighbor[2].getNum(), 8);
	ASSERT_EQ( neighbor[3].getNum(), 10);
}

// ブロックを持つノード判定テスト
TEST(NeiborHasBlockTest, returnNode5SetMyPosition11)
{
	array<int, 5> blockPosition{2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	vector<Node> neighbor = explorer.getMyNeighbor();
	
	//位置番号11のノードの隣接ノード
	ASSERT_EQ( neighbor[0].getHasBlock(), false);
	ASSERT_EQ( neighbor[1].getHasBlock(), true);
	ASSERT_EQ( neighbor[2].getHasBlock(), false);
}

// 最寄りのブロックの位置を探す
TEST(nearestBlockExplorerTest, return5SetBlack2Red5Yello8Blue15Green4)
{
	array<int, 5> blockPosition{2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//最寄りのブロックを探す
	ASSERT_EQ( explorer.getNearestBlockPosition(), 5);
	
}

TEST(nearestBlockExplorerTest, return12SetBlack11Red2Yello6Blue8Green12)
{
	array<int, 5> blockPosition{11,2,6,8,12};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//最寄りのブロックを探す
	ASSERT_EQ( explorer.getNearestBlockPosition(), 12);
	
}

TEST(nearestBlockExplorerTest, return12SetBlack3Red4Yello11Blue7Green15)
{
	array<int, 5> blockPosition{3,4,11,7,15};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//最寄りのブロックを探す
	ASSERT_EQ( explorer.getNearestBlockPosition(), 3);
	
}

