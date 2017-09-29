#include "PuzzleLineTracer.h"

PuzzleLineTracer::PuzzleLineTracer ():
	colorSensor ( PORT_3 ),
	traceDistance ( 0 ) {
	lineTracer.isLeftsideLine ( false ),
	ev3_speaker_set_volume ( 100 ) ;
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
	// 現在位置からの接続番号の付与
	connectPosition = connectNumberManager[currentPosition][nextPosition] ;
	// 行先への角度を取得する
	if ( beforePosition == 0x00 ) {
		beforeDegree = 0 ;
	} else {
		beforeConnectPosition = connectNumberManager[beforePosition][currentPosition] ;
		beforeDegree = allConnectPosition[beforePosition][beforeConnectPosition][DEGREE] ;
	}
	nextDegree = allConnectPosition[currentPosition][connectPosition][DEGREE] ;
	// 行先までの距離を取得する
	traceDistance = distance.getDistanceCurrent ( walker.get_count_L (), walker.get_count_R () ) ;
	nextDistance = allConnectPosition[currentPosition][connectPosition][DISTANCE] + traceDistance ;
	// 現在の角度と行先への角度から車体を動かす角度を計算する
	moveDegree = nextDegree - beforeDegree ;
	// 値が取れているか確認用のログ
	char msg[32] ;
	sprintf ( msg, "Degree>  Current:%d,Next:%d", currentDegree, nextDegree ) ;
	msg_f ( msg, 4 ) ;
	sprintf ( msg, "         Move:%d", moveDegree ) ;
	msg_f ( msg, 5 ) ;
    sprintf ( msg, "Position>Current:%d,Next:%d", currentPosition, connectPosition ) ; 
    msg_f ( msg, 6 ) ;
	sprintf ( msg, "Distance>Next:%ld,Trace:%ld", nextDistance, traceDistance ) ;
	msg_f ( msg, 7 ) ;
	// 車体を動かして角度を合わせる
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
	tslp_tsk ( 100 ) ;
	for ( int i = 0 ; i < moveDegree ; i++ ) {
		walker.run ( 0, ( ( moveDegree * 3 ) / 4 ) * -1 ) ;
		tslp_tsk ( 4 ) ;
	}
	walker.run ( 0, 0 ) ;
	tslp_tsk ( 100 ) ;
	// ラインをトレースする
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
	msg_f ( "OK", 8 ) ;
	while ( traceDistance < nextDistance ) {
		traceDistance = distance.getDistanceCurrent ( walker.get_count_L (), walker.get_count_R () ) ;
		lineTracer.speedControl.setPid ( 1.2, 2.4, 0.04, 30.0 );
		lineTracer.turnControl.setPid ( 2.4, 0.8, 0.02, 30.0 );
		lineTracer.runLine ( walker.get_count_L (), walker.get_count_R (), colorSensor.getBrightness () ) ;
		walker.run( lineTracer.getForward (), lineTracer.getTurn () ) ;
		tslp_tsk ( 4 ) ;
	}
	lineTracer.setForward ( -1 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
}