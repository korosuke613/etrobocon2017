#include "basicWalker.h"

BasicWalker::BasicWalker ():
	leftWheel ( PORT_C ), rightWheel ( PORT_B ) {
	ev3_speaker_set_volume ( 100 ) ;
}

void BasicWalker::spin ( int32_t forward, int32_t reverseValue, int32_t angle ) {
	leftWheel.reset () ;
	rightWheel.reset () ;
	tslp_tsk ( 100 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
	msg_f ( "Spin...", 2 ) ;
	leftWheel.setBrake ( false ) ;
	rightWheel.setBrake ( false ) ;
	leftReverseValue = reverseValue ;
	rightReverseValue = reverseValue * -1 ;
	while ( ( leftWheel.getCount () * leftReverseValue ) < ( angle * 1.64 ) ) {	// 1.65は角度から回転数への変換に必要な値
		leftWheel.setPWM ( forward * leftReverseValue ) ;
		rightWheel.setPWM ( forward * rightReverseValue ) ;
		tslp_tsk ( 2 ) ;
	}
	leftWheel.setPWM ( 0 ) ;
	rightWheel.setPWM ( 0 ) ;
}

void BasicWalker::goStraight ( int32_t forward, int32_t distance ) {
	leftWheel.reset () ;
	rightWheel.reset () ;
	tslp_tsk ( 100 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
	msg_f ( "Go...", 3 ) ;
	leftWheel.setBrake ( false ) ;
	rightWheel.setBrake ( false ) ;
	while ( ( ( leftWheel.getCount () + rightWheel.getCount () ) / 2 ) < distance ) {
		leftWheel.setPWM ( forward ) ;
		rightWheel.setPWM ( forward ) ;
		tslp_tsk ( 4 ) ;
	}
	leftWheel.setPWM ( 0 ) ;
	rightWheel.setPWM ( 0 ) ;
}

void BasicWalker::backStraight ( int32_t forward, int32_t distance ) {
	leftWheel.reset () ;
	rightWheel.reset () ;
	tslp_tsk ( 100 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
	msg_f ( "Go...", 3 ) ;
	leftWheel.setBrake ( false ) ;
	rightWheel.setBrake ( false ) ;
	while ( ( ( leftWheel.getCount () + rightWheel.getCount () ) / 2 ) > ( -1 * distance ) ) {
		leftWheel.setPWM ( -1 * forward ) ;
		rightWheel.setPWM ( -1 * forward ) ;
		tslp_tsk ( 4 ) ;
	}
	leftWheel.setPWM ( 0 ) ;
	rightWheel.setPWM ( 0 ) ;
}

void BasicWalker::parkingLeft ( void ) {
	char msg[32] ;
	sprintf ( msg, "Parking..." ) ;
	msg_f ( msg, 0 ) ;
	goStraight ( 30, 300 ) ;
	spin ( 30, SPIN_LEFT, 90 ) ;
	goStraight ( 30, 300 ) ;
	spin ( 30, SPIN_RIGHT, 90 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
}