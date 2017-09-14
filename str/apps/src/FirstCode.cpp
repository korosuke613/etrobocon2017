/**
 * @file FirstCode.h
 * @brief 初期位置コードクラス
 * @author Keisuke MORI
 */

#include "FirstCode.h"

FirstCode::FirstCode()
{
    firstCodeDigit[ 0 ] = 0;
    firstCodeDigit[ 1 ] = 0;
    firstCodeDigit[ 2 ] = 0;
    firstCodeDigit[ 3 ] = 0;
    firstCodeDigit[ 4 ] = 0;
}

void FirstCode::upDigit( int8_t digitNumber ) {
    digitNumber--;

    firstCodeDigit[ digitNumber ]++;

    if( 10 <= firstCodeDigit[ digitNumber ] ) {
        firstCodeDigit[ digitNumber ] = 0;
    }
}

void FirstCode::downDigit( int8_t digitNumber ) {
    digitNumber--;

    firstCodeDigit[ digitNumber ]--;

    if( firstCodeDigit[ digitNumber ] < 0 ) {
        firstCodeDigit[ digitNumber ] = 9;
    }
}

int32_t FirstCode::getFirstCode() {
    int32_t firstCode = 0;

    firstCode += firstCodeDigit[ 4 ] * 10000;
    firstCode += firstCodeDigit[ 3 ] * 1000;
    firstCode += firstCodeDigit[ 2 ] * 100;
    firstCode += firstCodeDigit[ 1 ] * 10;
    firstCode += firstCodeDigit[ 0 ] * 1;

    return firstCode;
}

