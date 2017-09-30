
#include "PuzzleCodeConverter.h"


//コンストラクタ
PuzzleCodeConverter::PuzzleCodeConverter()
{
}

//デストラクタ
PuzzleCodeConverter::~PuzzleCodeConverter(){}

/**
 *	ブロックの初期位置コードから、各ブロックの位置を算出する
 *	@param なし
 */
void PuzzleCodeConverter::resolvePositionCode()
{
	int result = mPuzzleCode;
	
	int ary[4];
	
	//初期位置コードの解釈
	ary[0] = (result % 11) + 1;
	result = result - (ary[0] - 1);
	
	for(int i=1; i<4; i++){
		if(i == 3 && result >= 11){
			ary[i] = (result / 11) + 1;
		}else{
			ary[i] = ((result / 11) % 11) + 1;
			result = (result / 11) - ((result / 11) % 11);
		}
	}
	
	//
	blockMap["Blue"] = ary[0];
	blockMap["Yellow"] = ary[1];
	blockMap["Red"] = ary[2];
	blockMap["Black"] = ary[3];
	
	return;
}

/**
 *	該当する色のブロックの場所を返す
 *	@param BlockColor ブロックの色
 */
int PuzzleCodeConverter::getPosition(BlockColor color)
{
	int result=0;
	
	switch(color){
	case BlockColor::Black:
		result = blockMap["Black"];
		break;
		
	case BlockColor::Red:
		result = blockMap["Red"];
		break;
		
	case BlockColor::Yellow:
		result = blockMap["Yellow"];
		break;
		
	case BlockColor::Blue:
		result = blockMap["Blue"];
		break;
		
	default:
		break;
	}
	
	return result;
	
}

/**
 *	赤ブロックの位置を黒ブロックの位置で返す
 *	@param redNum 赤ブロックの位置
 */
int PuzzleCodeConverter::redToBlackPosition(int redNum)
{
	int blackNum=redNum;
	
	if(redNum > 0)blackNum++;
	if(redNum > 5)blackNum+=2;
	if(redNum > 10)blackNum++;
	
	return blackNum;
}

/**
 *	黄ブロックの位置を黒ブロックの位置で返す
 *	@param yellowNum 黄ブロックの位置
 */
int PuzzleCodeConverter::yellowToBlackPosition(int yellowNum)
{
	int blackNum=yellowNum;	
	
	if(yellowNum > 2)blackNum++;
	if(yellowNum > 3)blackNum++;
	if(yellowNum > 10)blackNum++;
	
	return blackNum;
}

/**
 *	青ブロックの位置を黒ブロックの位置で返す
 *	@param blueNum 青ブロックの位置
 */
int PuzzleCodeConverter::blueToBlackPosition(int blueNum)
{
	int blackNum=blueNum;	
	
	if(blueNum > 1)blackNum++;
	if(blueNum > 2)blackNum++;
	if(blueNum > 6)blackNum++;
	if(blueNum > 7)blackNum++;
	
	return blackNum;
}

void PuzzleCodeConverter::setCode ( int puzzleCode ) {
	mPuzzleCode = puzzleCode ;
}