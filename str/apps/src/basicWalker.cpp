#include "basicWalker.h"

basicWalker::basicWalker ():
	leftWheel ( PORT_C ), rightWheel ( PORT_B ) {
	ev3_speaker_set_volume ( 100 ) ;
}

void basicWalker::spinRightAngle ( int32_t forward, int32_t reverseValue ) {
	leftWheel.reset () ;
	rightWheel.reset () ;
	tslp_tsk ( 100 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
	msg_f ( "Spin...", 2 ) ;
	leftWheel.setBrake ( false ) ;
	rightWheel.setBrake ( false ) ;
	leftReverseValue = reverseValue ;
	rightReverseValue = reverseValue * -1 ;
	while ( ( leftWheel.getCount () * leftReverseValue ) < 132 ) {
		leftWheel.setPWM ( forward * leftReverseValue ) ;
		rightWheel.setPWM ( forward * rightReverseValue ) ;
		tslp_tsk ( 2 ) ;
	}
	leftWheel.setPWM ( 0 ) ;
	rightWheel.setPWM ( 0 ) ;
}

void basicWalker::goStraight ( int32_t forward, int32_t distance ) {
	leftWheel.reset () ;
	rightWheel.reset () ;
	tslp_tsk ( 100 ) ;
	//ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
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

void basicWalker::backStraight ( int32_t forward, int32_t distance ) {
	leftWheel.reset () ;
	rightWheel.reset () ;
	tslp_tsk ( 100 ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
	msg_f ( "Go...", 3 ) ;
	leftWheel.setBrake ( false ) ;
	rightWheel.setBrake ( false ) ;
	while ( ( ( leftWheel.getCount () + rightWheel.getCount () ) / 2 ) > distance ) {
		leftWheel.setPWM ( forward ) ;
		rightWheel.setPWM ( forward ) ;
		tslp_tsk ( 4 ) ;
	}
	leftWheel.setPWM ( 0 ) ;
	rightWheel.setPWM ( 0 ) ;
}

void basicWalker::parkingLeft ( void ) {
	goStraight ( 30, 300 ) ;
	
	
	goStraight ( 30, 300 ) ;
	spinRightAngle ( 30, SPIN_LEFT ) ;
	ev3_speaker_play_tone ( NOTE_FS6, 100 ) ;
}