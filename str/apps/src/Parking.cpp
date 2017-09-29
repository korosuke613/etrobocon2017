/**
 * @file Parking.cpp
 * @brief 駐車クラス
 * @author Keisuke MORI
 */

#include "Parking.h"

void Parking::runParallel()
{
    BasicWalker basicWalker;

	msg_f( "Do ParallelParking...", 0 );

	basicWalker.goStraight( 30, 300 );
	basicWalker.spin( 30, basicWalker.SPIN_LEFT, 90 );
	basicWalker.goStraight( 30, 300 );
	basicWalker.spin( 30, basicWalker.SPIN_RIGHT, 90 );

    waitThreeTimes();
}

void Parking::runParpendicular()
{
    BasicWalker basicWalker;

	msg_f( "Do ParpendicularParking...", 0 );

    waitThreeTimes();
}

void Parking::waitThreeTimes() {
	ev3_speaker_play_tone( NOTE_FS4, 100 );
    tslp_tsk( 1000 );
	ev3_speaker_play_tone( NOTE_FS4, 100 );
    tslp_tsk( 1000 );
	ev3_speaker_play_tone( NOTE_FS4, 100 );
    tslp_tsk( 1000 );
	ev3_speaker_play_tone( NOTE_FS5, 800 );
}
