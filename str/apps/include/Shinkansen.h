/**
 * 
 * RコースのShinkansenを走らせるクラス
 * 
 */

#ifndef __SHINKANSEN__
#define __SHINKANSEN__

#include <cstdint>

/**
* RコースのShinkansenを走らせるクラス
*/
class Shinkansen{
public:
	/** コンストラクタ **/
	Shinkansen();
	/** 新幹線が通過したかを知らせる関数 **/
	bool checkPass(std::int16_t distance);
	
private:
	std::int16_t time_counter;
	bool isInFrontOf;
	const std::int16_t TO_PASS;
	const std::int8_t PASS_THRESHOLD;
	const std::int8_t DISTANCE_THRESHOLD;
};

#endif