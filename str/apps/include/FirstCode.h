/**
 * @file FirstCode.h
 * @brief 初期位置コードクラス
 * @author Keisuke MORI
 */
#ifndef __FIRST_CODE__
#define __FIRST_CODE__

#include <stdint.h>

/*! @class FirstCode FirstCode.h "FirstCode.h"
 *  @brief 初期位置コードクラス
 */
class FirstCode {
public:
    FirstCode();

    /**
     * 任意の桁数の数値を上げる。
     * その桁数の数値が9の場合は0になる。
     */
    void upDigit( int8_t );

    /**
     * 任意の桁数の数値を下げる。
     * その桁数の数値が0の場合は9になる。
     */
    void downDigit( int8_t );

    /**
     * 初期位置コードの値を返す。
     */
    int32_t getFirstCode();

private:
    int firstCodeDigit[ 5 ];
};


#endif
