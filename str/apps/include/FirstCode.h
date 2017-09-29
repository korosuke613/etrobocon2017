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
     * @param 任意の桁数 1から5までの数値に対応する
     */
    void upDigit( int8_t );

    /**
     * 任意の桁数の数値を下げる。
     * その桁数の数値が0の場合は9になる。
     * @param 任意の桁数 1から5までの数値に対応する
     */
    void downDigit( int8_t );

    /**
     * 初期位置コードの値を返す。
     * @return 初期位置コード 数値は0から99999まで
     */
    int32_t getFirstCode();

    /**
     * 現在の操作している桁数を返す。
     * @return 現在操作している桁数 1から5まで
     */
    int8_t getDigit();

    /**
     * 現在の操作している桁数を右にずらす。
     * つまり桁数を下げる。
     * その桁数の数値が1の場合は5になる。
     */
    void changeRightDigit();

    /**
     * 現在の操作している桁数を左にずらす。
     * つまり桁数を上げる。
     * その桁数の数値が5の場合は1になる。
     */
    void changeLeftDigit();

private:
    /**
     * 5桁の初期位置コード
     */
    int firstCodeDigit[ 5 ];

    /**
     * 現在操作している桁数
     */
    int digit;
};


#endif
