/**
 * @file Distance.cpp
 * @brief Distanceクラスの関数を定義<br>
 * @author Futa HIRAKOBA
 */

#include "Distance.h"

int32_t Distance::getDistanceTotal(int32_t countL, int32_t countR){
	leftMotorDegTotal = countL;
	rightMotorDegTotal = countR;
	return (leftMotorDegTotal + rightMotorDegTotal) / 2;
}

int32_t Distance::getDistanceCurrent(int32_t countL, int32_t countR){
	int32_t leftMotorDeg = countL - leftMotorDegOld;
	int32_t rightMotorDeg = countR - rightMotorDegOld;

	return (leftMotorDeg + rightMotorDeg) / 2;
}

void Distance::resetDistance(int32_t countL, int32_t countR){
	getDistanceTotal(countL, countR);
	leftMotorDegOld = leftMotorDegTotal;
	rightMotorDegOld = rightMotorDegTotal;
}