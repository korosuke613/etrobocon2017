#ifndef __COMMON_DEFINITION__
#define __COMMON_DEFINITION__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



#define DRIVING_POWER		30
/* ���L�̃}�N���͌�/���ɍ��킹�ĕύX����K�v������܂� */
#define GYRO_OFFSET           0  /* �W���C���Z���T�I�t�Z�b�g�l(�p���x0[deg/sec]��) */
#define LIGHT_WHITE          40  /* ���F�̌��Z���T�l */
#define LIGHT_BLACK           0  /* ���F�̌��Z���T�l */
#define SONAR_ALERT_DISTANCE 30  /* �����g�Z���T�ɂ���Q�����m����[cm] */
#define TAIL_ANGLE_STAND_UP  93  /* ���S��~���̊p�x[�x] */
#define TAIL_ANGLE_DRIVE      3  /* �o�����X���s���̊p�x[�x] */
#define P_GAIN             2.5F  /* ���S��~�p���[�^������W�� */
#define PWM_ABS_MAX          60  /* ���S��~�p���[�^����PWM��΍ő�l */
//#define DEVICE_NAME     "ET0"  /* Bluetooth�� hrp2/target/ev3.h BLUETOOTH_LOCAL_NAME�Őݒ� */
//#define PASS_KEY        "1234" /* �p�X�L�[    hrp2/target/ev3.h BLUETOOTH_PIN_CODE�Őݒ� */
#define CMD_START         '1'    /* �����[�g�X�^�[�g�R�}���h */
#define BLACK  2
#define WHITE 47
#define GREY (BLACK+WHITE)/2

/* LCD�t�H���g�T�C�Y */
#define CALIB_FONT (EV3_FONT_SMALL)
#define CALIB_FONT_WIDTH (6/*TODO: magic number*/)
#define CALIB_FONT_HEIGHT (8/*TODO: magic number*/)

#define DRIVE_L	   EV3_PORT_C
#define DRIVE_R	   EV3_PORT_B
#define ARM        EV3_PORT_A
#define TAIL       EV3_PORT_D
#define ULTRASONIC EV3_PORT_3
#define TOUCH	   EV3_PORT_1
#define IR	   EV3_PORT_2
#define GYRO       EV3_PORT_4
#define DEL 0.004

#endif

