#pragma once

/*
 *  コールバックルーチンの識別番号
 */
#define SIO_RDY_SND    1U        /* 送信可能コールバック */
#define SIO_RDY_RCV    2U        /* 受信通知コールバック */

#define TNUM_PORT 4

/**
 * ID of SIO ports
 */
#define SIO_PORT_UART (1)
#define SIO_PORT_BT   (2)
#define SIO_PORT_LCD  (3)
#define SIO_PORT_SPP_MASTER_TEST  (4)

#define SERIAL_RCV_BUFSZ2 (4096 * 2)
#define SERIAL_SND_BUFSZ2 (4096 * 2)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  シリアルI/Oポート管理ブロックの定義
 */
typedef struct sio_port_control_block SIOPCB;

/*
 *  低レベル出力シリアルI/Oの初期化
 */
extern void sio_initialize_low();

/*
 *  シリアルI/Oポートのオープン
 */
extern SIOPCB *sio_opn_por(ID siopid, intptr_t exinf);

/*
 *  シリアルI/Oポートのクローズ
 */
extern void sio_cls_por(SIOPCB *p_siopcb);

/*
 *  SIOの割込みハンドラ
 */
extern void uart_sio_isr(/*ID siopid*/intptr_t exinf);

extern void uart_sio_cyc(/*ID siopid*/intptr_t exinf);

/*
 *  シリアルI/Oポートへの文字送信
 */
extern bool_t sio_snd_chr(SIOPCB *siopcb, char c);

/*
 *  シリアルI/Oポートからの文字受信
 */
extern int_t sio_rcv_chr(SIOPCB *siopcb);

/*
 *  シリアルI/Oポートからのコールバックの許可
 */
extern void sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn);

/*
 *  シリアルI/Oポートからのコールバックの禁止
 */
extern void sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn);

/*
 *  シリアルI/Oポートからの送信可能コールバック
 */
extern void sio_irdy_snd(intptr_t exinf);

/*
 *  シリアルI/Oポートからの受信通知コールバック
 */
extern void sio_irdy_rcv(intptr_t exinf);

extern void bt_rcv_handler(const uint8_t *data, uint16_t size);

extern void bt_sio_cyc(intptr_t exinf);

/**
 * Fetch the send buffer of Bluetooth into @buf.
 * The send buffer will be cleared (switched).
 * @param buf   a pointer to store base address of fetched send buffer.
 * @param bytes a pointer to store data size of fetched send buffer.
 */
extern void bt_fetch_snd_buf(uint8_t **buf, uint32_t *bytes);

/**
 * Send a character to the LCD console
 */
void lcd_console_send_character(char c);

#endif /* TOPPERS_MACRO_ONLY */
