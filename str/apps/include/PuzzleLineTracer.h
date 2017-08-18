#ifndef __PUZZLELINETRACER__
#define __PUZZLELINETRACER__

#include "LeftNormalCourse.h"

#define X 0x00

#define PUZZLE_POSITION_CURRENT 16
#define PUZZLE_POSITION_NEXT    16
#define PUZZLE_POSITION_DESTINATE 5
#define PUZZLE_POLAR_COODINATE 2

#define DEGREE   0
#define DISTANCE 1

#define PUZZLE_LINE_LONG   1080
#define PUZZLE_LINE_NORMAL 720
#define PUZZLE_LINE_SHORT  450

using namespace ev3api;

class PuzzleLineTracer {
public:
	PuzzleLineTracer () ;
	void preparatePuzzle ( void ) ;
	void puzzleLineTrace ( int8_t, int8_t ) ;

private:
	Walker walker ;
	LineTracer lineTracer;
	Distance distance;
	LeftNormalCourse leftNormalCourse ;
	int8_t forward;
    int32_t traceDistance ;
	int8_t currentDegree ;
	int8_t leftMotorDeg ;
	int8_t rightMotorDeg ;
	int8_t destinatePosition ;
	int8_t nextDegree ;
	int32_t nextDistance ;
	int8_t moveDegree ;
	int8_t destinateNumberManager[PUZZLE_POSITION_CURRENT][PUZZLE_POSITION_NEXT] = {
	/* 接続ノード番号付与テーブル　( 'X'は非接続を示す )                                        */
	/*                                     N E X T                               */
	/*            0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, */
	/*      0 */{ X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X },
	/*      1 */{ X,  X,  0,  X,  X,  1,  X,  X,  X,  X,  2,  X,  X,  X,  X,  X },
	/*      2 */{ X,  0,  X,  1,  X,  2,  3,  X,  X,  X,  X,  X,  X,  X,  X,  X },
	/*      3 */{ X,  X,  0,  X,  1,  X,  2,  3,  X,  X,  X,  X,  X,  X,  X,  X },
	/*  C   4 */{ X,  X,  X,  0,  X,  X,  X,  1,  X,  X,  X,  2,  X,  X,  X,  X },
	/*  U   5 */{ X,  0,  1,  X,  X,  X,  X,  X,  2,  X,  3,  X,  X,  X,  X,  X },
	/*  R   6 */{ 0,  X,  1,  2,  X,  X,  X,  X,  3,  4,  X,  X,  X,  X,  X,  X },
	/*  R   7 */{ X,  X,  X,  0,  1,  X,  X,  X,  X,  2,  X,  3,  X,  X,  X,  X },
	/*  E   8 */{ 0,  X,  X,  X,  X,  1,  2,  X,  X,  X,  X,  X,  3,  4,  X,  X },
	/*  N   9 */{ 0,  X,  X,  X,  X,  X,  1,  2,  X,  X,  X,  X,  X,  X,  3,  4 },
	/*  T  10 */{ X,  0,  X,  X,  X,  1,  X,  X,  X,  X,  X,  X,  2,  X,  X,  X },
	/*     11 */{ X,  X,  X,  X,  0,  X,  X,  1,  X,  X,  X,  X,  X,  X,  X,  2 },
	/*     12 */{ X,  X,  X,  X,  X,  X,  X,  X,  0,  X,  1,  X,  X,  2,  X,  X },
	/*     13 */{ 0,  X,  X,  X,  X,  X,  X,  X,  1,  X,  X,  X,  2,  X,  3,  X },
	/*     14 */{ 0,  X,  X,  X,  X,  X,  X,  X,  X,  1,  X,  X,  X,  2,  X,  3 },
	/*     15 */{ X,  X,  X,  X,  X,  X,  X,  X,  X,  0,  X,  1,  X,  X,  2,  X }
	} ;
	int32_t puzzleConnectPosition[PUZZLE_POSITION_CURRENT][PUZZLE_POSITION_DESTINATE][PUZZLE_POLAR_COODINATE] = {
		{
			{ X, X }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
			{ 0, PUZZLE_LINE_LONG }, { -30, PUZZLE_LINE_SHORT }, { -75, PUZZLE_LINE_NORMAL }, { 0, 0 }, { 0, 0 }
		},
		{
			{ 180, PUZZLE_LINE_LONG }, { 0, PUZZLE_LINE_LONG }, { -150, PUZZLE_LINE_SHORT }, { -30, PUZZLE_LINE_SHORT }, { X, X }
		},
		{
			{ 180, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_LONG }, { -150, PUZZLE_LINE_SHORT }, { -30, PUZZLE_LINE_SHORT }, { X, X }
		},
		{
			{ 180, PUZZLE_LINE_LONG }, { -150, PUZZLE_LINE_SHORT }, { -105, PUZZLE_LINE_NORMAL }, { 0, 0 }, { X, X }
		},
		{
			{ 150, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { -120, PUZZLE_LINE_SHORT }, { -30, PUZZLE_LINE_SHORT }, { X, X }
		},
		{
			{ 150, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { -150, PUZZLE_LINE_SHORT }, { -30, PUZZLE_LINE_SHORT }, { X, X }
		},
		{
			{ 150, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { -150, PUZZLE_LINE_SHORT }, { -60, PUZZLE_LINE_SHORT }, { X, X }
		},
		{
			{ 150, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { -120, PUZZLE_LINE_SHORT }, { -60, PUZZLE_LINE_SHORT }, { X, X }
		},
		{
			{ 150, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { -120, PUZZLE_LINE_SHORT }, { -60, PUZZLE_LINE_SHORT }, { X, X }
		},
		{
			{ 105, PUZZLE_LINE_NORMAL }, { 60, PUZZLE_LINE_SHORT }, { -30, PUZZLE_LINE_SHORT }, { 0, 0 }, { X, X }
		},
		{
			{ 75, PUZZLE_LINE_NORMAL }, { 120, PUZZLE_LINE_SHORT }, { -150, PUZZLE_LINE_SHORT }, { 0, 0 }, { X, X }
		},
		{
			{ 150, PUZZLE_LINE_SHORT }, { 60, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_SHORT }, { 0, 0 }, { X, X }
		},
		{
			{ 120, PUZZLE_LINE_SHORT }, { 180, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_SHORT }, { 0, 0 }, { X, X }
		},
		{
			{ 60, PUZZLE_LINE_SHORT }, { 180, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_SHORT }, { 0, 0 }, { X, X }
		},
		{
			{ 120, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { 180, PUZZLE_LINE_SHORT }, { 0, 0 }, { X, X }
		},
	} ;
		
} ;

#endif