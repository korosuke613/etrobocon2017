#ifndef __PUZZLEFIELD__
#define __PUZZLEFIELD__

#include "ev3api.h"
#include "Walker.h"
#include "ColorSensor.h"
#include "Distance.h"
#include "LineTracerWalker.h"
#include "BasicWalker.h"

#define X -1

#define PUZZLE_POSITION_CURRENT 16
#define PUZZLE_POSITION_NEXT    16
#define PUZZLE_POSITION_DESTINATE 9
#define PUZZLE_POLAR_COODINATE 2

#define DEGREE   0
#define DISTANCE 1

#define PUZZLE_LINE_LONG      1100
#define PUZZLE_LINE_NORMAL     920
#define PUZZLE_LINE_SHORT      660
#define PUZZLE_LINE_VERY_SHORT 345

using namespace ev3api;

class PuzzleField {
public:
	PuzzleField () ;
	void preparatePuzzle ( void ) ;
	void testGame ( void ) ;

private:
	Walker walker ;
	BasicWalker basicWalker ;
	ColorSensor colorSensor;
	LineTracerWalker lineTracer;
	Distance distance;
	int modifiedSpinVector ;
	int32_t modifiedSpinDegree ;
	int8_t color ;
	int8_t forward;
    int32_t traceDistance ;
	int32_t currentDegree ;
	int8_t leftMotorDeg ;
	int8_t rightMotorDeg ;
	int8_t connectNumber ;
	int8_t beforeconnectNumber ;
	int32_t beforeDegree ;
	int32_t nextDegree ;
	int32_t nextDistance ;
	int32_t spinDegree ;
	bool spinVector ;
	int8_t connectNumberManager[PUZZLE_POSITION_CURRENT][PUZZLE_POSITION_NEXT] = {
	/* 接続ノード番号付与テーブル　( 'X'は非接続を示す )                                        */
	/*                                     N E X T                               */
	/*            0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, */
	/*      0 */{ X,  X,  X,  X,  X,  X,  0,  X,  1,  2,  X,  X,  X,  3,  4,  X },
	/*      1 */{ X,  X,  0,  X,  X,  1,  X,  X,  X,  X,  2,  X,  X,  X,  X,  X },
	/*      2 */{ X,  0,  X,  1,  X,  2,  3,  X,  5,  X,  X,  X,  X,  X,  X,  X },
	/*      3 */{ X,  X,  0,  X,  1,  X,  2,  3,  X,  5,  X,  X,  X,  X,  X,  X },
	/*  C   4 */{ X,  X,  X,  0,  X,  X,  X,  1,  X,  X,  X,  2,  X,  X,  X,  X },
	/*  U   5 */{ X,  0,  1,  X,  X,  X,  4,  X,  2,  X,  3,  X,  5,  X,  X,  X },
	/*  R   6 */{ 8,  X,  0,  1,  X,  4,  X,  5,  2,  3,  X,  X,  X,  6,  7,  X },
	/*  R   7 */{ X,  X,  X,  0,  1,  X,  4,  X,  X,  2,  X,  3,  X,  X,  X,  5 },
	/*  E   8 */{ 8,  X,  4,  X,  X,  0,  1,  X,  X,  5,  6,  X,  2,  3,  7,  X },
	/*  N   9 */{ 8,  X,  X,  4,  X,  X,  0,  1,  5,  X,  X,  6,  X,  7,  2,  3 },
	/*  T  10 */{ X,  0,  X,  X,  X,  1,  X,  X,  5,  X,  X,  X,  2,  X,  X,  X },
	/*     11 */{ X,  X,  X,  X,  0,  X,  X,  1,  X,  5,  X,  X,  X,  X,  X,  2 },
	/*     12 */{ X,  X,  X,  X,  X,  5,  X,  X,  0,  X,  1,  X,  X,  2,  X,  X },
	/*     13 */{ 7,  X,  X,  X,  X,  X,  5,  X,  0,  6,  X,  X,  1,  X,  2,  X },
	/*     14 */{ 7,  X,  X,  X,  X,  X,  5,  X,  6,  0,  X,  X,  X,  1,  X,  2 },
	/*     15 */{ X,  X,  X,  X,  X,  X,  X,  5,  X,  0,  X,  1,  X,  X,  2,  X }
	} ;
	int32_t allconnectNumber[PUZZLE_POSITION_CURRENT][PUZZLE_POSITION_DESTINATE][PUZZLE_POLAR_COODINATE] = {
		{
		/*  0 */{ 90, PUZZLE_LINE_VERY_SHORT }, { 160, PUZZLE_LINE_VERY_SHORT }, { 10, PUZZLE_LINE_VERY_SHORT }, { -120, PUZZLE_LINE_VERY_SHORT }, { -60, PUZZLE_LINE_VERY_SHORT }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  1 */{ 0, PUZZLE_LINE_LONG }, { -30, PUZZLE_LINE_SHORT }, { -75, PUZZLE_LINE_NORMAL }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  2 */{ 180, PUZZLE_LINE_LONG }, { 0, PUZZLE_LINE_LONG }, { -150, PUZZLE_LINE_SHORT }, { -30, PUZZLE_LINE_SHORT }, { X, X }, { -90, PUZZLE_LINE_SHORT }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  3 */{ 180, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_LONG }, { -150, PUZZLE_LINE_SHORT }, { -30, PUZZLE_LINE_SHORT }, { X, X }, { -90, PUZZLE_LINE_SHORT }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  4 */{ 180, PUZZLE_LINE_LONG }, { -150, PUZZLE_LINE_SHORT }, { -108, PUZZLE_LINE_NORMAL }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  5 */{ 150, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { -30, PUZZLE_LINE_SHORT }, { -120, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_LONG }, { -75, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  6 */{ 150, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { -150, PUZZLE_LINE_SHORT }, { -30, PUZZLE_LINE_SHORT }, { 180, PUZZLE_LINE_LONG }, { 0, PUZZLE_LINE_LONG }, { -130, PUZZLE_LINE_LONG }, { -75, PUZZLE_LINE_LONG }, { -90, PUZZLE_LINE_VERY_SHORT }
		},
		{
		/*  7 */{ 150, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { -150, PUZZLE_LINE_SHORT }, { -90, PUZZLE_LINE_SHORT }, { 180, PUZZLE_LINE_LONG }, { -130, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }
		},
		{
		/*  8 */{ 150, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { -120, PUZZLE_LINE_SHORT }, { -90, PUZZLE_LINE_SHORT }, { 90, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_LONG }, { -210, PUZZLE_LINE_LONG }, { -90, PUZZLE_LINE_LONG }, { -30, PUZZLE_LINE_VERY_SHORT }
		},
		{
		/*  9 */{ 150, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { -120, PUZZLE_LINE_SHORT }, { -60, PUZZLE_LINE_SHORT }, { 108, PUZZLE_LINE_SHORT }, { 180, PUZZLE_LINE_LONG }, { -30, PUZZLE_LINE_LONG }, { -174, PUZZLE_LINE_LONG }, { -234, PUZZLE_LINE_VERY_SHORT }
		},
		{
		/* 10 */{ 105, PUZZLE_LINE_NORMAL }, { 108, PUZZLE_LINE_SHORT }, { -30, PUZZLE_LINE_SHORT }, { X, X }, { 30, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/* 11 */{ 75, PUZZLE_LINE_NORMAL }, { 120, PUZZLE_LINE_SHORT }, { -150, PUZZLE_LINE_SHORT }, { X, X }, { 234, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/* 12 */{ 108, PUZZLE_LINE_SHORT }, { 150, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_SHORT }, { X, X }, { 130, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }, { X, X }
		},
		{
		/* 13 */{ 120, PUZZLE_LINE_SHORT }, { 180, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_SHORT }, { X, X }, { X, X }, { 75, PUZZLE_LINE_LONG }, { 108, PUZZLE_LINE_LONG }, { 100, PUZZLE_LINE_SHORT }, { X, X }
		},
		{
		/* 14 */{ 108, PUZZLE_LINE_SHORT }, { 180, PUZZLE_LINE_SHORT }, { 0, PUZZLE_LINE_SHORT }, { X, X }, { X, X }, { 130, PUZZLE_LINE_LONG }, { 160, PUZZLE_LINE_NORMAL }, { 120, PUZZLE_LINE_VERY_SHORT }, { X, X }
		},
		{
		/* 15 */{ 120, PUZZLE_LINE_SHORT }, { 30, PUZZLE_LINE_SHORT }, { 180, PUZZLE_LINE_SHORT }, { X, X }, { 210, PUZZLE_LINE_LONG }, { X, X }, { X, X }, { X, X }, { X, X }
		},
	} ;

	void runPuzzleField ( int8_t, int8_t, int8_t ) ;
	void runPuzzleFieldVectorChange ( int8_t, int8_t, int8_t, int32_t ) ;
	void avoidBlock ( int8_t, int8_t, int8_t ) ;
} ;

#endif
