
#include <gtest/gtest.h>
#include <PuzzleExplorer.h>


// ブロック並べエリアのノードの色を返す
TEST(NodeColorTest, returnRedSetBlockNumber1)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//位置番号1のノードの色
	ASSERT_EQ( explorer.getNodeColor(1), BlockColor::Red);
}

TEST(NodeColorTest, returnBlueSetBlockNumber2)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//位置番号2のノードの色
	ASSERT_EQ( explorer.getNodeColor(2), BlockColor::Blue);
}

TEST(NodeColorTest, returnYellowSetBlockNumber3)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//位置番号3のノードの色
	ASSERT_EQ( explorer.getNodeColor(3), BlockColor::Yellow);
}

TEST(NodeColorTest, returnGreenSetBlockNumber11)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//位置番号1のノードの色
	ASSERT_EQ( explorer.getNodeColor(11), BlockColor::Green);
}

// 隣接ノードの確認テスト
TEST(NeiborNodeTest, returnNode1Node5Node12SetMyPosition11)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	Node** neighbor = explorer.getMyNeighbor();
	
	//位置番号11のノードの隣接ノード
	ASSERT_EQ( neighbor[0]->getNum(), 1);
	ASSERT_EQ( neighbor[1]->getNum(), 5);
	ASSERT_EQ( neighbor[2]->getNum(), 12);
	ASSERT_EQ( neighbor[3], nullptr);
	ASSERT_EQ( neighbor[4], nullptr);
}

// 隣接ノードの確認テスト
TEST(NeiborNodeTest, returnNode1Node3Node5Node6SetMyPosition2)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	explorer.setMyPosition(2);
	
	Node** neighbor = explorer.getMyNeighbor();
	
	//位置番号2のノードの隣接ノード
	ASSERT_EQ( neighbor[0]->getNum(), 1);
	ASSERT_EQ( neighbor[1]->getNum(), 3);
	ASSERT_EQ( neighbor[2]->getNum(), 5);
	ASSERT_EQ( neighbor[3]->getNum(), 6);
	ASSERT_EQ( neighbor[4], nullptr);
}

TEST(NeiborNodeTest, returnNode6Node8Node9Node13Node14SetMyPosition0)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	explorer.setMyPosition(0);
	
	Node** neighbor = explorer.getMyNeighbor();
	
	
	//位置番号0のノードの隣接ノード
	ASSERT_EQ( neighbor[0]->getNum(), 6);
	ASSERT_EQ( neighbor[1]->getNum(), 8);
	ASSERT_EQ( neighbor[2]->getNum(), 9);
	ASSERT_EQ( neighbor[3]->getNum(), 13);
	ASSERT_EQ( neighbor[4]->getNum(), 14);
}

TEST(NeiborNodeTest, returnNode1Node2Node8Node10SetMyPosition5)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	explorer.setMyPosition(5);
	
	//隣接ノードの取得
	Node** neighbor = explorer.getMyNeighbor();
	
	//位置番号0のノードの隣接ノード
	ASSERT_EQ( neighbor[0]->getNum(), 1);
	ASSERT_EQ( neighbor[1]->getNum(), 2);
	ASSERT_EQ( neighbor[2]->getNum(), 8);
	ASSERT_EQ( neighbor[3]->getNum(), 10);
	ASSERT_EQ( neighbor[4], nullptr);
}

// ブロックを持つノード判定テスト
TEST(NeiborHasBlockTest, returnNode5SetMyPosition11)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	Node** neighbor = explorer.getMyNeighbor();
	
	//位置番号11のノードの隣接ノード
	ASSERT_EQ( neighbor[0]->getHasBlock(), false);
	ASSERT_EQ( neighbor[1]->getHasBlock(), true);
	ASSERT_EQ( neighbor[2]->getHasBlock(), false);
}

// 最寄りのブロックの位置を探す
TEST(nearestBlockExplorerTest, return5SetBlack2Red5Yello8Blue15Green4)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//最寄りのブロックを探す
	ASSERT_EQ( explorer.getNearestBlockPosition(), 5);
	
}

TEST(nearestBlockExplorerTest, return12SetBlack11Red2Yello6Blue8Green12)
{
	int blockPosition[5] = {11,2,6,8,12};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//最寄りのブロックを探す
	ASSERT_EQ( explorer.getNearestBlockPosition(), 12);
	
}

TEST(nearestBlockExplorerTest, return12SetBlack3Red4Yello11Blue7Green15)
{
	int blockPosition[5] = {3,4,11,7,15};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//最寄りのブロックを探す
	ASSERT_EQ( explorer.getNearestBlockPosition(), 3);
	
}

// ノード間の経路探索テスト
TEST(rootExplorerTest, returnNode10Node5SetStart10goal5)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//ノード10からノード5までの経路を探索
	int* root = explorer.getRoot(10,5);
	ASSERT_EQ( root[0], 10);
	ASSERT_EQ( root[1], 5);
}

TEST(rootExplorerTest, returnNode1Node2Node3Node4SetStart1goal4)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//ノード1からノード4までの経路を探索
	int* root = explorer.getRoot(1,4);
	ASSERT_EQ( root[0], 1);
	ASSERT_EQ( root[1], 2);
	ASSERT_EQ( root[2], 3);
	ASSERT_EQ( root[3], 4);
}

TEST(rootExplorerTest, returnNode1Node2Node3Node7Node11SetStart1goal11)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//ノード1からノード11までの経路を探索
	int* root = explorer.getRoot(1,11);
	ASSERT_EQ( root[0], 1);
	ASSERT_EQ( root[1], 2);
	ASSERT_EQ( root[2], 3);
	ASSERT_EQ( root[3], 7);
	ASSERT_EQ( root[4], 11);
}

TEST(rootExplorerTest, returnNode10Node12Node13Node0SetStart0goal10)
{
	int blockPosition[5] = {2,5,8,15,4};//黒赤黄青緑の位置
	
	PuzzleExplorer explorer;
	explorer.init(blockPosition);
	
	//ノード10からノード0までの経路を探索
	int* root = explorer.getRoot(10,0);
	
	ASSERT_EQ( root[0], 10);
	ASSERT_EQ( root[1], 12);
	ASSERT_EQ( root[2], 13);
	ASSERT_EQ( root[3], 0);

}

