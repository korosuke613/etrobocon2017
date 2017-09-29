#include "PuzzleField.h"

PuzzleField::PuzzleField ():
	colorSensor ( PORT_3 ),
	traceDistance ( 0 ) {
	lineTracer.isLeftsideLine ( false ),
	ev3_speaker_set_volume ( 5 ) ;
	basicWalker.setPidWithoutTarget ( 2.0, 2.0, 0.1 ) ;
}

void PuzzleField::preparatePuzzle ( void ) {
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
	basicWalker.goStraight ( 10, 60 ) ;
	walker.run ( 0, 0 ) ;
	walker.reset () ;
	tslp_tsk ( 100 ) ;
}

void PuzzleField::runPuzzleField ( int8_t currentPosition, int8_t beforePosition, int8_t nextPosition ) {
	runPuzzleFieldVectorChange ( currentPosition, beforePosition, nextPosition, 0 ) ;
}

void PuzzleField::avoidBlock ( int8_t currentPosition, int8_t beforePosition, int8_t nextPosition ) {
	basicWalker.backStraight ( allconnectNumber[currentPosition][connectNumberManager[currentPosition][beforePosition]][DISTANCE] ) ;
	walker.run ( 0, 0 ) ;
	runPuzzleFieldVectorChange ( currentPosition, beforePosition, nextPosition, 180 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 75 ) ;
	tslp_tsk ( 500 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 75 ) ;
	tslp_tsk ( 500 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 75 ) ;
}

void PuzzleField::runPuzzleFieldVectorChange ( int8_t currentPosition, int8_t beforePosition, int8_t nextPosition, int32_t vectorStatus )
{
	char msg[32] ;
	// 現在位置からの接続番号の付与
	connectNumber = connectNumberManager[currentPosition][nextPosition] ;
	// 行先への角度を取得する
	if ( beforePosition == X ) {
		currentDegree = 60 ;
	} else {
		beforeconnectNumber = connectNumberManager[beforePosition][currentPosition] ;
		currentDegree = allconnectNumber[beforePosition][beforeconnectNumber][DEGREE] - vectorStatus ;
		if ( vectorStatus == 180 && currentDegree < -180 ) {
			currentDegree += 360 ;
		}
	}
	nextDegree = allconnectNumber[currentPosition][connectNumber][DEGREE] ;
	spinDegree = nextDegree - currentDegree ;
	if ( spinDegree < 0 ) {
		spinVector = SPIN_RIGHT ;
		spinDegree *= -1 ;
		sprintf ( msg, "Spin Vector:SPIN_RIGHT" ) ;
		msg_f ( msg, 6 ) ;
	} else if ( 180 < spinDegree ) {
		spinVector = SPIN_RIGHT ;
		spinDegree -= 360 ;
		spinDegree *= -1 ;
		sprintf ( msg, "Spin Vector:SPIN_RIGHT" ) ;
		msg_f ( msg, 6 ) ;
	} else {
		spinVector = SPIN_LEFT ;
		sprintf ( msg, "Spin Vector:SPIN_LEFT " ) ;
		msg_f ( msg, 6 ) ;
	}
	// 行先までの距離を取得する
	nextDistance = allconnectNumber[currentPosition][connectNumber][DISTANCE] ;
	// 値が取れているか確認用のログ
	sprintf ( msg, "Degree>Current:%ld,Next:%ld", currentDegree, nextDegree ) ;
	msg_f ( msg, 4 ) ;
	sprintf ( msg, "          Spin:%ld", spinDegree ) ;
	msg_f ( msg, 5 ) ;
    sprintf ( msg, "Position>Current:%d->Next:%d", currentPosition, nextPosition ) ; 
    msg_f ( msg, 7 ) ;
	sprintf ( msg, "Distance>Next:%ld", nextDistance ) ;
	msg_f ( msg, 8 ) ;
	// 車体を動かして角度を合わせる
	ev3_speaker_play_tone ( NOTE_FS5, 100 ) ;
	basicWalker.spin ( spinVector, spinDegree ) ;
	tslp_tsk ( 100 ) ;
	// ラインをトレースする
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
	msg_f ( "OK", 9 ) ;
	if ( connectNumber < 4 && nextPosition != 0 ) {
		tslp_tsk ( 100 ) ;
		ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
		distance.resetDistance ( walker.get_count_L (), walker.get_count_R () ) ;
		traceDistance = 0 ;
		lineTracer.speedControl.setPid ( 2.0, 4.0, 0.1, 45.0 ) ;
		lineTracer.turnControl.setPid ( 4.0, 1.0, 0.06, 45.0 ) ;
		while ( traceDistance < nextDistance ) {
			traceDistance = distance.getDistanceTotal ( walker.get_count_L (), walker.get_count_R () ) ;
			color = colorSensor.getBrightness () ;
			lineTracer.runLine ( walker.get_count_L (), walker.get_count_R (), color ) ;
			walker.run ( lineTracer.getForward (), lineTracer.getTurn () ) ;
			if ( nextDistance - 180 < traceDistance ) {
				if ( colorSensor.getColorNumber () == COLOR_RED || colorSensor.getColorNumber () == COLOR_BLUE || colorSensor.getColorNumber () == COLOR_GREEN || colorSensor.getColorNumber () == COLOR_YELLOW ) {
					basicWalker.reset () ;
					basicWalker.goStraight ( 90, 140 ) ;
					break ;
				}
			}
			tslp_tsk ( 4 ) ;
		}
		walker.run ( 0, 0 ) ;
		walker.reset () ;
		tslp_tsk ( 100 ) ;
	} else {
		basicWalker.goStraight ( 60, nextDistance ) ;
		walker.run ( 0, 0 ) ;
	}
	tslp_tsk ( 100 ) ;
	ev3_speaker_play_tone ( NOTE_FS5, 100 ) ;
	tslp_tsk ( 1000 ) ;
}

void PuzzleField::testRun ( void ) {
	basicWalker.setPidWithoutTarget ( 2.0, 2.0, 0.1 ) ;
	basicWalker.spin ( SPIN_LEFT, 90 ) ;
	basicWalker.goStraight ( 160, 1000 ) ;
} 

void PuzzleField::testGame ( void ) {
	runPuzzleField ( 10,  X,  1 ) ;
	runPuzzleField (  1, 10,  5 ) ;
	runPuzzleField (  5,  1,  8 ) ;
	runPuzzleField (  8,  5,  6 ) ;
	runPuzzleField (  6,  8,  0 ) ;
	avoidBlock (  6,  0,  9 ) ;
	runPuzzleField (  9,  6, 14 ) ;
	runPuzzleField ( 14,  9,  8 ) ;
	runPuzzleField (  8, 14,  2 ) ;
	runPuzzleField (  2,  8,  3 ) ;
	runPuzzleField (  3,  2,  9 ) ;
	runPuzzleField (  9,  3, 15 ) ;
	runPuzzleField ( 15,  9, 11 ) ;
	
	basicWalker.goStraight ( 20, 640 ) ;
	basicWalker.spin ( SPIN_LEFT, 60 ) ;

}