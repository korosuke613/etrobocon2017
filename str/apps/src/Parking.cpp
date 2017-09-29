/**
 * @file Parking.cpp
 * @brief 駐車クラス
 * @author Keisuke MORI
 */

#include "Parking.h"

Parking::Parking():
    colorSensor( PORT_3 ) {
}

void Parking::runParallel()
{
    BasicWalker basicWalker;

	msg_f( "Do ParallelParking...", 0 );

	basicWalker.goStraight( 30, 300 );
	basicWalker.spin( basicWalker.SPIN_LEFT, 90 );
	basicWalker.goStraight( 30, 300 );
	basicWalker.spin( basicWalker.SPIN_RIGHT, 90 );

    waitThreeTimes();
}

void Parking::runParpendicular()
{
    BasicWalker basicWalker;

	msg_f( "Do ParpendicularParking...", 0 );

    basicWalker.reset();
    basicWalker.setPidWithoutTarget( 4.0, 2.0, 0.02 );
    basicWalker.goStraight( 150, 450 );
    basicWalker.setPidWithoutTarget( 1.0, 2.0, 0.02 );
    basicWalker.goStraight( 50, 150 );
    basicWalker.reset();

    basicWalker.spin( basicWalker.SPIN_RIGHT, 90 );
    basicWalker.reset();
    tslp_tsk( 100 );

    basicWalker.goStraight( 150, 550 );
    basicWalker.setPidWithoutTarget( 1.0, 2.0, 0.02 );
    basicWalker.goStraight( 50, 250 );
    basicWalker.reset();

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
