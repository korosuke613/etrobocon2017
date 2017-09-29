#include "BasicWalker.h"

BasicWalker::BasicWalker () {
	ev3_speaker_set_volume ( 100 ) ;
}

void BasicWalker::setPidWithoutTarget ( double valueP, double valueI, double valueD ) {
	p_value = valueP ;
	i_value = valueI ;
	d_value = valueD ;
}

void BasicWalker::reset ( void ) {
	walker.reset () ;
}

void BasicWalker::spin ( bool rotationalDirection, int32_t angle ) {
    int8_t reverseValue = rotationalDirection == SPIN_RIGHT
        ?  1
        : -1;

	reset () ;
	while ( ( walker.get_count_R () * reverseValue ) < ( angle / 0.645 ) ) {	// 数値は角度から回転数への変換に必要な値
		walker.run ( 0, ( 18 * reverseValue ) ) ;
		tslp_tsk ( 4 ) ;
	}
	walker.run ( 0, 0 ) ;
}

void BasicWalker::goStraight ( int32_t target_forward, int32_t distance ) {
	speedControl.setPid ( p_value, i_value, d_value, target_forward ) ;
	while ( ( ( walker.get_count_L () + walker.get_count_R () ) / 2 ) < distance ) {
		forward = speedControl.calculateSpeedForPid ( walker.get_count_L (), walker.get_count_R () ) ;
		walker.run ( forward, 0 ) ;
		tslp_tsk ( 4 ) ;
	}
}

void BasicWalker::backStraight ( int32_t target_forward, int32_t distance ) {
	speedControl.setPid ( p_value, i_value, d_value, target_forward ) ;
	while ( ( ( walker.get_count_L () + walker.get_count_R () ) / 2 ) * -1 < distance ) {
		forward = speedControl.calculateSpeedForPid ( walker.get_count_L (), walker.get_count_R () ) ;
		walker.run ( forward, 0 ) ;
		tslp_tsk ( 4 ) ;
	}
}
