#ifndef __PUZZLELINETRACER__
#define __PUZZLELINETRACER__

#include "ev3api.h"
#include "Walker.h"
#include "ColorSensor.h"
#include "Distance.h"
#include "LineTracer.h"
#include "BasicWalker.h"

#define X 0x00

#define PUZZLE_POSITION_CURRENT 16
#define PUZZLE_POSITION_NEXT    16
#define PUZZLE_POSITION_DESTINATE 9
#define PUZZLE_POLAR_COODINATE 2

#define DEGREE   0
#define DISTANCE 1

#define PUZZLE_LINE_LONG   580
#define PUZZLE_LINE_NORMAL 400
#define PUZZLE_LINE_SHORT  240

using namespace ev3api;

class PuzzleLineTracer {
public:
	PuzzleLineTracer () ;
	void preparatePuzzle ( void ) ;
	void puzzleLineTrace ( int8_t, int8_t, int8_t ) ;
	void avoidBlock ( int8_t, int8_t, int8_t ) ;
	void testGame ( void ) ;

private:
	Walker walker ;
	BasicWalker basicWalker ;
	ColorSensor colorSensor;
	LineTracer lineTracer;
	Distance distance;
	int8_t color ;
	int8_t forward;
    int32_t traceDistance ;
	int32_t currentDegree ;
	int8_t leftMotorDeg ;
	int8_t rightMotorDeg ;
	int8_t connectPosition ;
	int8_t beforeConnectPosition ;
	int32_t beforeDegree ;
	int32_t nextDegree ;
	int32_t nextDistance ;
	int32_t spinDegree ;
	int32_t spinVector ;
	int8_t connectNumberManager[PUZZLE_POSITION_CURRENT][PUZZLE_POSITION_NEXT] = {
	/* 接続ノード番号付与テーブル　( 'X'は非接続を示す )                                        */
	/*                                     N E X T                               */
	/*            0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, */
	/*      0 */{ X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X,  X },
	/*      1 */{ X,  X,  0,  X,  X,  1,  X,  X,  X,  X,  2,  X,  X,  X,  X,  X },
	/*      2 */{ X,  0,  X,  1,  X,  2,  3,  X,  4,  X,  X,  X,  X,  X,  X,  X },
	/*      3 */{ X,  X,  0,  X,  1,  X,  2,  3,  X,  4,  X,  X,  X,  X,  X,  X },
	/*  C   4 */{ X,  X,  X,  0,  X,  X,  X,  1,  X,  X,  X,  2,  X,  X,  X,  X },
	/*  U   5 */{ X,  0,  1,  X,  X,  X,  4,  X,  2,  X,  3,  X,  5,  X,  X,  X },
	/*  R   6 */{ 8,  X,  0,  1,  X,  4,  X,  5,  2,  3,  X,  X,  X,  6,  7,  X },
	/*  R   7 */{ X,  X,  X,  0,  1,  X,  4,  X,  X,  2,  X,  3,  X,  X,  X,  5 },
	/*  E   8 */{ 8,  X,  4,  X,  X,  0,  1,  X,  X,  5,  6,  X,  2,  3,  7,  X },
	/*  N   9 */{ 8,  X,  X,  4,  X,  X,  0,  1,  5,  X,  X,  5,  X,  7,  2,  3 },
	/*  T  10 */{ X,  0,  X,  X,  X,  1,  X,  X,  3,  X,  X,  X,  2,  X,  X,  X },
	/*     11 */{ X,  X,  X,  X,  0,  X,  X,  1,  X,  3,  X,  X,  X,  X,  X,  2 },
	/*     12 */{ X,  X,  X,  X,  X,  3,  X,  X,  0,  X,  1,  X,  X,  2,  X,  X },
	/*     13 */{ 5,  X,  X,  X,  X,  X,  3,  X,  0,  4,  X,  X,  1,  X,  2,  X },
	/*     14 */{ 5,  X,  X,  X,  X,  X,  3,  X,  4,  0,  X,  X,  X,  1,  X,  2 },
	/*     15 */{ X,  X,  X,  X,  X,  X,  X,  3,  X,  0,  X,  1,  X,  X,  2,  X }
	} ;
	int32_t allConnectPosition[PUZZLE_POSITION_CURRENT][PUZZLE_POSITION_DESTINATE][PUZZLE_POLAR_COODINATE] = {
		{
		/*  0 */{ X, X }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  1 */{ 0, PUZZLE_LINE_LONG }, { -45, PUZZLE_LINE_SHORT }, { -110, PUZZLE_LINE_NORMAL }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  2 */{ 264, PUZZLE_LINE_LONG }, { 0, PUZZLE_LINE_LONG }, { -220, PUZZLE_LINE_SHORT }, { -45, PUZZLE_LINE_SHORT }, { -132, PUZZLE_LINE_SHORT }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  3 */{ 264, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_LONG }, { -220, PUZZLE_LINE_SHORT }, { -45, PUZZLE_LINE_SHORT }, { -132, PUZZLE_LINE_SHORT }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  4 */{ 264, PUZZLE_LINE_LONG }, { -220, PUZZLE_LINE_SHORT }, { -156, PUZZLE_LINE_NORMAL }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  5 */{ 220, PUZZLE_LINE_SHORT }, { 45, PUZZLE_LINE_SHORT }, { -45, PUZZLE_LINE_SHORT }, { -176, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_LONG }, { -110, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  6 */{ 220, PUZZLE_LINE_SHORT }, { 45, PUZZLE_LINE_SHORT }, { -220, PUZZLE_LINE_SHORT }, { -45, PUZZLE_LINE_SHORT }, { 264, PUZZLE_LINE_LONG }, { 0, PUZZLE_LINE_LONG }, { -154, PUZZLE_LINE_LONG }, { -110, PUZZLE_LINE_LONG }, { -132, PUZZLE_LINE_SHORT }
		},
		{
		/*  7 */{ 220, PUZZLE_LINE_SHORT }, { 45, PUZZLE_LINE_SHORT }, { -220, PUZZLE_LINE_SHORT }, { -132, PUZZLE_LINE_SHORT }, { 264, PUZZLE_LINE_LONG }, { -154, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  8 */{ 220, PUZZLE_LINE_SHORT }, { 45, PUZZLE_LINE_SHORT }, { -176, PUZZLE_LINE_SHORT }, { -132, PUZZLE_LINE_SHORT }, { 132, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_LONG }, { -210, PUZZLE_LINE_LONG }, { -90, PUZZLE_LINE_LONG }, { -30, PUZZLE_LINE_SHORT }
		},
		{
		/*  9 */{ 220, PUZZLE_LINE_SHORT }, { 45, PUZZLE_LINE_SHORT }, { -176, PUZZLE_LINE_SHORT }, { -132, PUZZLE_LINE_SHORT }, { 132, PUZZLE_LINE_SHORT }, { 264, PUZZLE_LINE_LONG }, { -54, PUZZLE_LINE_LONG }, { -174, PUZZLE_LINE_LONG }, { -234, PUZZLE_LINE_SHORT }
		},
		{
		/* 10 */{ 156, PUZZLE_LINE_NORMAL }, { 132, PUZZLE_LINE_SHORT }, { -45, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/* 11 */{ 110, PUZZLE_LINE_NORMAL }, { 176, PUZZLE_LINE_SHORT }, { -220, PUZZLE_LINE_SHORT }, { 234, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/* 12 */{ 132, PUZZLE_LINE_SHORT }, { 220, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_SHORT }, { 154, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/* 13 */{ 0, 0 }, { 176, PUZZLE_LINE_SHORT }, { 264, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_SHORT }, { 110, PUZZLE_LINE_LONG }, { 90, PUZZLE_LINE_LONG }, { 100, PUZZLE_LINE_SHORT }, { X, X }, { X, X }
		},
		{
		/* 14 */{ 132, PUZZLE_LINE_SHORT }, { 264, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_SHORT }, { 154, PUZZLE_LINE_LONG }, { 174, PUZZLE_LINE_LONG }, { 164, PUZZLE_LINE_SHORT }, { X, X }, { X, X }, { X, X }
		},
		{
		/* 15 */{ 176, PUZZLE_LINE_SHORT }, { 45, PUZZLE_LINE_SHORT }, { 264, PUZZLE_LINE_SHORT }, { 210, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }
		},
	} ;
		
} ;

#endif