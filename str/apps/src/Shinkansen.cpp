#include"Shinkansen.h"

Shinkansen::Shinkansen():
	time_counter(0),
	isInFrontOf(false),
	TO_PASS(300),
	PASS_THRESHOLD(TO_PASS / 60),
	DISTANCE_THRESHOLD(30){
}

bool Shinkansen::checkPass(std::int16_t distance){
	if(isInFrontOf){
		time_counter++;
		//新幹線を検知してからTO_PASS + PASS_THRESHOLD
		if(time_counter > TO_PASS + PASS_THRESHOLD){
			time_counter = 0;
			isInFrontOf = false;
			return true;
		}
	}else{
		//新幹線をDISTANCE_THREHOLD連続で検知するとtime_counterを増やす
		if(distance <= DISTANCE_THRESHOLD){
			time_counter++;
		}else{
			time_counter = 0;
		}
		//time_counterがPASS_THREHOLDを超えると、新幹線がいると判断する
		if(time_counter > PASS_THRESHOLD){
			time_counter = 0;
			isInFrontOf = true;
		}
	}
	return false;
	//新幹線が通るまで待つ処理
    //新幹線が通った後クロスのところまで行く処理
    //90度回転させる処理
    //進む処理
    //ブロックの手前で止まる処理
	//色を見る処理
}