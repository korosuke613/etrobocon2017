#include "PuzzleLineTracer.h"

PuzzleLineTracer::PuzzleLineTracer ():
	colorSensor ( PORT_3 ),
	traceDistance ( 0 ) {
	lineTracer.isLeftsideLine ( false ),
	ev3_speaker_set_volume ( 5 ) ;
}

void PuzzleLineTracer::preparatePuzzle ( void )
{
	tslp_tsk ( 100 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
	distance.resetDistance ( walker.get_count_L (), walker.get_count_R () ) ;
	while ( traceDistance < 1860 ) {
		traceDistance = distance.getDistanceTotal ( walker.get_count_L (), walker.get_count_R () ) ;
		lineTracer.speedControl.setPid ( 1.0, 0.8, 0.08, 60.0 ) ;
		lineTracer.turnControl.setPid ( 2.8, 0.8, 0.06, 30.0 ) ;
		color = colorSensor.getBrightness () ;
		lineTracer.runLine ( walker.get_count_L (), walker.get_count_R (), color ) ;
		walker.run( lineTracer.getForward (), lineTracer.getTurn () ) ;
		tslp_tsk ( 4 ) ;
	}
	walker.run ( 0, 0 ) ;
	walker.reset () ;
	tslp_tsk ( 100 ) ;
}

void PuzzleLineTracer::puzzleLineTrace ( int8_t currentPosition, int8_t beforePosition, int8_t nextPosition )
{
	char msg[32] ;
	// 現在位置からの接続番号の付与
	connectPosition = connectNumberManager[currentPosition][nextPosition] ;
	// 行先への角度を取得する
	if ( beforePosition == X ) {
		currentDegree = 100 ;
	} else {
		beforeConnectPosition = connectNumberManager[beforePosition][currentPosition] ;
		currentDegree = allConnectPosition[beforePosition][beforeConnectPosition][DEGREE] ;
	}
	nextDegree = allConnectPosition[currentPosition][connectPosition][DEGREE] ;
	if ( nextDegree < 0 ) {
		spinVector = SPIN_RIGHT ;
		sprintf ( msg, "Spin Vector:SPIN_RIGHT" ) ;
		msg_f ( msg, 8 ) ;
	} else {
		spinVector = SPIN_LEFT ;
		sprintf ( msg, "Spin Vector:SPIN_LEFT" ) ;
		msg_f ( msg, 8 ) ;
	}
	// 行先までの距離を取得する
	nextDistance = allConnectPosition[currentPosition][connectPosition][DISTANCE] ;
	spinDegree = nextDegree - currentDegree ;
	if ( spinDegree < 0 ) {
		spinDegree *= -1 ;
	}
	// 値が取れているか確認用のログ
	sprintf ( msg, "Degree>Current:%ld,Next:%ld", currentDegree, nextDegree ) ;
	msg_f ( msg, 4 ) ;
	sprintf ( msg, "          Spin:%ld", spinDegree ) ;
	msg_f ( msg, 5 ) ;
    sprintf ( msg, "Position>Current:%d->Next:%d", currentPosition, nextPosition ) ; 
    msg_f ( msg, 6 ) ;
	sprintf ( msg, "Distance>Next:%ld", nextDistance ) ;
	msg_f ( msg, 7 ) ;
	// 車体を動かして角度を合わせる
	ev3_speaker_play_tone ( NOTE_FS5, 100 ) ;
	basicWalker.spin ( 30, spinVector, spinDegree ) ;
	tslp_tsk ( 100 ) ;
	// ラインをトレースする
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
	msg_f ( "OK", 9 ) ;
	basicWalker.goStraight ( 30, nextDistance ) ;
	tslp_tsk ( 100 ) ;
	ev3_speaker_play_tone ( NOTE_FS5, 100 ) ;
}

void PuzzleLineTracer::avoidBlock ( int8_t currentPosition, int8_t beforePosition, int8_t nextPosition ) {
	basicWalker.backStraight ( 20, allConnectPosition[beforePosition][connectNumberManager[beforePosition][currentPosition]][DISTANCE] ) ;
	puzzleLineTrace ( beforePosition, currentPosition, nextPosition ) ;
	
}

void PuzzleLineTracer::testGame ( void ) {
	puzzleLineTrace ( 10,  X,  1 ) ;
	tslp_tsk ( 1000 ) ;
	puzzleLineTrace (  1, 10,  5 ) ;
	tslp_tsk ( 1000 ) ;
	puzzleLineTrace (  5,  1,  8 ) ;
	tslp_tsk ( 1000 ) ;
	puzzleLineTrace (  8,  5,  6 ) ;
	tslp_tsk ( 1000 ) ;
	puzzleLineTrace (  6,  8,  0 ) ;
	tslp_tsk ( 1000 ) ;
	avoidBlock (  0,  6,  9 ) ;
	tslp_tsk ( 1000 ) ;
}