/**
 * @file UserInterface.cpp
 * @brief 走行体が走り出す前にユーザが入力するインターフェースを提供するクラス
 * @author Keisuke MORI
 */

#include "UserInterface.h"

void UserInterface::inputFirstCode() {
    char firstCodeText[32];
    int digit = 0;
    bool isChangedFirstCode = false;

    // 初期位置コードを入力してください
    msg_f( "Please set first code", 4 );

    // 初期位置コードの初期値と操作している桁数の初期位置を表示する
    sprintf( firstCodeText, "%05ld", firstCode.getFirstCode() );
    msg_f( firstCodeText, 5 );
    digit = firstCode.getDigit();
    msg_f( getCurrentDigitText( digit ), 6 );

    ev3_speaker_play_tone( 200, 500 );

    // 初期位置コードを入力
    while( 1 ) {
        // ENTERボタンが押されたらループを抜ける
        if( ev3_button_is_pressed( ENTER_BUTTON ) ) {
            isChangedFirstCode = true;
            break;
        }


        if( ev3_button_is_pressed( UP_BUTTON ) ) {
            firstCode.upDigit( digit );
            isChangedFirstCode = true;
        }
        if( ev3_button_is_pressed( DOWN_BUTTON ) ) {
            firstCode.downDigit( digit );
            isChangedFirstCode = true;
        }
        if( ev3_button_is_pressed( RIGHT_BUTTON ) ) {
            firstCode.changeRightDigit();
            isChangedFirstCode = true;
        }
        if( ev3_button_is_pressed( LEFT_BUTTON ) ) {
            firstCode.changeLeftDigit();
            isChangedFirstCode = true;
        }

        digit = firstCode.getDigit();

        // ボタンが押された時に限り画面表示を変更する
        if( isChangedFirstCode ) {
            ev3_speaker_play_tone( 1000, 100 );
            sprintf( firstCodeText, "%05ld", firstCode.getFirstCode() );
            msg_f( firstCodeText, 5 );
            msg_f( getCurrentDigitText( digit ), 6 );
            tslp_tsk( 500 );
        }

        isChangedFirstCode = false;
        tslp_tsk( 4 );
    }

    // 終了
    sprintf( firstCodeText, "Input first code for <%05ld>.", firstCode.getFirstCode() );
    msg_f( firstCodeText, 4 );
    ev3_speaker_play_tone( 1500, 50 );
    tslp_tsk( 100 );
    ev3_speaker_play_tone( 1500, 50 );
}

int32_t UserInterface::getFirstCode() {
    return firstCode.getFirstCode();
}

char* UserInterface::getCurrentDigitText( int8_t currentDigit ) {
    static char text[ 32 ];

    if( currentDigit == 1 ) {
        sprintf( text, "    -" );
    } else if( currentDigit == 2 ) {
        sprintf( text, "   - " );
    } else if( currentDigit == 3 ) {
        sprintf( text, "  -  " );
    } else if( currentDigit == 4 ) {
        sprintf( text, " -   " );
    } else if( currentDigit == 5 ) {
        sprintf( text, "-    " );

    } else {
        // もし1桁から5桁以外を選択している場合
        sprintf( text, "-----" );
    }

    return text;
}

