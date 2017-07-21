#include "Distance.h"

int32_t Distance::getDistanceTotal(){
	leftMotorDegTotal = walker.get_count_L () ;
	rightMotorDegTotal = walker.get_count_R () ;
	return (leftMotorDegTotal + rightMotorDegTotal) / 2;
}

int32_t Distance::getDistanceCurrent(){
	leftMotorDeg = walker.get_count_L () - leftMotorDegOld;
	rightMotorDeg = walker.get_count_R () - rightMotorDegOld;

	return (leftMotorDeg + rightMotorDeg) / 2;
}

void Distance::resetDistance(){
	getDistanceTotal();
	leftMotorDegOld = leftMotorDegTotal;
	rightMotorDegOld = rightMotorDegTotal;
}