/* kernel_cfg.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#if TKERNEL_PRID != 0x06u
#error "The kernel does not match this configuration file."
#endif

/*
 *  Include Directives (#include)
 */

#include "app.h"
#include "csl.h"
#include "chip_timer.h"
#include "syssvc/syslog.h"
#include "syssvc/banner.h"
#include "target_serial.h"
#include "target_serial_dbsio.h"
#include "syssvc/serial.h"
#include "syssvc/logtask.h"
#include "dmloader.h"

/*
 *  Protection Domain Management Functions
 */

const ID _kernel_tmax_domid = (TMIN_DOMID + TNUM_DOMID - 1);

const DOMINIB _kernel_dominib_kernel = { TACP_KERNEL, INT_PRIORITY(TMIN_TPRI), { 0, 0 } };

const DOMINIB _kernel_dominib_table[TNUM_DOMID] = {
	{ TACP(TDOM_APP), INT_PRIORITY(TMIN_TPRI + 1), { TDOM_APP, _kernel_section_table[INDEX_DOM(TDOM_APP)] } }
};

/*
 *  Task Management Functions
 */

#define TNUM_STSKID	12

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);
const ID _kernel_tmax_stskid = (TMIN_TSKID + TNUM_STSKID - 1);

static STK_T _kernel_sstack_LOGTASK[COUNT_STK_T(LOGTASK_STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_BRICK_BTN_TSK[COUNT_STK_T(DEFAULT_SSTKSZ)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_LCD_REFRESH_TSK[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_CONSOLE_BTN_TSK[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_BT_TSK[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_BT_QOS_TSK[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_USBMSC_TSK[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_EV3_INIT_TASK[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_PLATFORM_BUSY_TASK[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_EV3RT_LOGTASK[COUNT_STK_T(LOGTASK_STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_APP_TERM_TASK[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));
static STK_T _kernel_sstack_ZMODEM_RECV_TASK[COUNT_STK_T(STACK_SIZE)] __attribute__((section(".prsv_kernel"),nocommon));

static STK_T _kernel_ustack_BRICK_BTN_TSK[COUNT_STK_T(4096)] __attribute__((section(".ustack_BRICK_BTN_TSK"),nocommon));

const TINIB _kernel_tinib_table[TNUM_STSKID] = {
	{ &_kernel_dominib_kernel, (TA_ACT), (intptr_t)(LOGTASK_PORTID), ((TASK)(logtask_main)), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_sstack_LOGTASK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ &_kernel_dominib_table[INDEX_DOM(TDOM_APP)], (TA_NULL), (intptr_t)(0), ((TASK)(brick_button_task)), INT_PRIORITY(TMIN_APP_TPRI), ROUND_STK_T(DEFAULT_SSTKSZ), _kernel_sstack_BRICK_BTN_TSK, ROUND_STK_T(4096), _kernel_ustack_BRICK_BTN_TSK, (TA_NULL), (NULL), { TACP(TDOM_APP), TACP(TDOM_APP), TACP(TDOM_APP), TACP(TDOM_APP) }},
	{ &_kernel_dominib_kernel, (TA_NULL), (intptr_t)(NULL), ((TASK)(lcd_refresh_tsk)), INT_PRIORITY(TPRI_EV3_LCD_TASK), ROUND_STK_T(STACK_SIZE), _kernel_sstack_LCD_REFRESH_TSK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ &_kernel_dominib_kernel, (TA_ACT), (intptr_t)(0), ((TASK)(console_button_task)), INT_PRIORITY(TPRI_EV3_MONITOR), ROUND_STK_T(STACK_SIZE), _kernel_sstack_CONSOLE_BTN_TSK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ &_kernel_dominib_kernel, (TA_NULL), (intptr_t)(NULL), ((TASK)(btstack_task)), INT_PRIORITY(TPRI_BLUETOOTH_HIGH), ROUND_STK_T(STACK_SIZE), _kernel_sstack_BT_TSK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ &_kernel_dominib_kernel, (TA_NULL), (intptr_t)(NULL), ((TASK)(bluetooth_qos_task)), INT_PRIORITY(TPRI_BLUETOOTH_QOS), ROUND_STK_T(STACK_SIZE), _kernel_sstack_BT_QOS_TSK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ &_kernel_dominib_kernel, (TA_ACT), (intptr_t)(0), ((TASK)(usbmsc_task)), INT_PRIORITY(TPRI_USBMSC), ROUND_STK_T(STACK_SIZE), _kernel_sstack_USBMSC_TSK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ &_kernel_dominib_kernel, (TA_ACT), (intptr_t)(0), ((TASK)(ev3_main_task)), INT_PRIORITY(TPRI_INIT_TASK), ROUND_STK_T(STACK_SIZE), _kernel_sstack_EV3_INIT_TASK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ &_kernel_dominib_kernel, (TA_ACT), (intptr_t)(0), ((TASK)(platform_busy_task)), INT_PRIORITY(TPRI_PLATFORM_BUSY), ROUND_STK_T(STACK_SIZE), _kernel_sstack_PLATFORM_BUSY_TASK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ &_kernel_dominib_kernel, (TA_NULL), (intptr_t)(0), ((TASK)(ev3rt_logtask)), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_sstack_EV3RT_LOGTASK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ &_kernel_dominib_kernel, (TA_NULL), (intptr_t)(0), ((TASK)(application_terminate_task)), INT_PRIORITY(TPRI_APP_TERM_TASK), ROUND_STK_T(STACK_SIZE), _kernel_sstack_APP_TERM_TASK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ &_kernel_dominib_kernel, (TA_NULL), (intptr_t)(0), ((TASK)(zmodem_recv_task)), INT_PRIORITY(TMIN_APP_TPRI), ROUND_STK_T(STACK_SIZE), _kernel_sstack_ZMODEM_RECV_TASK, 0, NULL, (TA_NULL), (NULL), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }}
};

TINIB _kernel_atinib_table[48];

TCB _kernel_tcb_table[TNUM_TSKID];

const ID _kernel_torder_table[TNUM_STSKID] = {
	LOGTASK, BRICK_BTN_TSK, LCD_REFRESH_TSK, CONSOLE_BTN_TSK, BT_TSK, BT_QOS_TSK, USBMSC_TSK, EV3_INIT_TASK, PLATFORM_BUSY_TASK, EV3RT_LOGTASK, APP_TERM_TASK, ZMODEM_RECV_TASK
};

/*
 *  Semaphore Functions
 */

#define TNUM_SSEMID	14

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);
const ID _kernel_tmax_ssemid = (TMIN_SEMID + TNUM_SSEMID - 1);

	const SEMINIB _kernel_seminib_table[TNUM_SSEMID] = {
	{ (TA_TPRI), (0), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_TPRI), (1), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_TPRI), (0), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_TPRI), (1), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_TPRI), (0), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_TPRI), (1), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_TPRI), (0), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_TPRI), (1), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), (1), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), (1), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), (0), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), (1), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), (1), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), (1), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }}
};

SEMINIB _kernel_aseminib_table[16];

SEMCB _kernel_semcb_table[TNUM_SEMID];

/*
 *  Eventflag Functions
 */

#define TNUM_SFLGID	4

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);
const ID _kernel_tmax_sflgid = (TMIN_FLGID + TNUM_SFLGID - 1);

const FLGINIB _kernel_flginib_table[TNUM_SFLGID] = {
	{ (TA_CLR), (0), { TACP_KERNEL, TACP_SHARED, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_CLR), (0), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_CLR), (0), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), (APP_STATUS_UNLOAD), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }}
};

FLGINIB _kernel_aflginib_table[16];

FLGCB _kernel_flgcb_table[TNUM_FLGID];

/*
 *  Dataqueue Functions
 */

#define TNUM_SDTQID	0

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);
const ID _kernel_tmax_sdtqid = (TMIN_DTQID + TNUM_SDTQID - 1);

TOPPERS_EMPTY_LABEL(const DTQINIB, _kernel_dtqinib_table);

DTQINIB _kernel_adtqinib_table[80];

DTQCB _kernel_dtqcb_table[TNUM_DTQID];

/*
 *  Priority Dataqueue Functions
 */

#define TNUM_SPDQID	0

const ID _kernel_tmax_pdqid = (TMIN_PDQID + TNUM_PDQID - 1);
const ID _kernel_tmax_spdqid = (TMIN_PDQID + TNUM_SPDQID - 1);

TOPPERS_EMPTY_LABEL(const PDQINIB, _kernel_pdqinib_table);

PDQINIB _kernel_apdqinib_table[16];

PDQCB _kernel_pdqcb_table[TNUM_PDQID];

/*
 *  Mutex Functions
 */

#define TNUM_SMTXID	5

const ID _kernel_tmax_mtxid = (TMIN_MTXID + TNUM_MTXID - 1);
const ID _kernel_tmax_smtxid = (TMIN_MTXID + TNUM_SMTXID - 1);

const MTXINIB _kernel_mtxinib_table[TNUM_SMTXID] = {
	{ (TA_NULL), INT_PRIORITY(0), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), INT_PRIORITY(0), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), INT_PRIORITY(0), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), INT_PRIORITY(0), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), INT_PRIORITY(0), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }}
};

MTXINIB _kernel_amtxinib_table[16];

MTXCB _kernel_mtxcb_table[TNUM_MTXID];

/*
 *  Fixed-sized Memorypool Functions
 */

#define TNUM_SMPFID	0

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);
const ID _kernel_tmax_smpfid = (TMIN_MPFID + TNUM_SMPFID - 1);

TOPPERS_EMPTY_LABEL(const MPFINIB, _kernel_mpfinib_table);

MPFINIB _kernel_ampfinib_table[4];

MPFCB _kernel_mpfcb_table[TNUM_MPFID];

/*
 *  Cyclic Handler Functions
 */

#define TNUM_SCYCID	4

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);
const ID _kernel_tmax_scycid = (TMIN_CYCID + TNUM_SCYCID - 1);

const CYCINIB _kernel_cycinib_table[TNUM_SCYCID] = {
	{ (TA_STA), (intptr_t)(NULL), (bt_sio_cyc), (5), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_STA), (intptr_t)(&dbsio_spp_master_test), (dbsio_cyc), (5), (1), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), (intptr_t)(0), (brick_button_cyc), (10), (0), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }},
	{ (TA_NULL), (intptr_t)(0), (bluetooth_dma_cyc), (1), (0), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }}
};

CYCINIB _kernel_acycinib_table[16];

CYCCB _kernel_cyccb_table[TNUM_CYCID];

/*
 *  Alarm Handler Functions
 */

#define TNUM_SALMID	1

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);
const ID _kernel_tmax_salmid = (TMIN_ALMID + TNUM_SALMID - 1);

const ALMINIB _kernel_alminib_table[TNUM_SALMID] = {
	{ (TA_NULL), (intptr_t)(0), (sound_device_stop), { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_KERNEL }}
};

TOPPERS_EMPTY_LABEL(ALMINIB, _kernel_aalminib_table);

ALMCB _kernel_almcb_table[TNUM_ALMID];

/*
 *  System State Management Functions
 */

const ACVCT _kernel_sysstat_acvct = { TACP_KERNEL, TACP_KERNEL, TACP_KERNEL, TACP_SHARED };

/*
 *  Interrupt Management Functions
 */

const uint_t _kernel_tnum_isr_queue = 16;

const ISR_ENTRY _kernel_isr_queue_list[16] = {
	{ 3, &(_kernel_isr_queue_table[0]) },
	{ 4, &(_kernel_isr_queue_table[1]) },
	{ 11, &(_kernel_isr_queue_table[2]) },
	{ 12, &(_kernel_isr_queue_table[3]) },
	{ 21, &(_kernel_isr_queue_table[4]) },
	{ 25, &(_kernel_isr_queue_table[5]) },
	{ 42, &(_kernel_isr_queue_table[6]) },
	{ 43, &(_kernel_isr_queue_table[7]) },
	{ 44, &(_kernel_isr_queue_table[8]) },
	{ 45, &(_kernel_isr_queue_table[9]) },
	{ 46, &(_kernel_isr_queue_table[10]) },
	{ 47, &(_kernel_isr_queue_table[11]) },
	{ 48, &(_kernel_isr_queue_table[12]) },
	{ 49, &(_kernel_isr_queue_table[13]) },
	{ 50, &(_kernel_isr_queue_table[14]) },
	{ 53, &(_kernel_isr_queue_table[15]) }
};

QUEUE _kernel_isr_queue_table[16];

void
_kernel_inthdr_3(void)
{
	i_begin_int(3);
	_kernel_call_isr(&(_kernel_isr_queue_table[0]));
	i_end_int(3);
}

void
_kernel_inthdr_4(void)
{
	i_begin_int(4);
	_kernel_call_isr(&(_kernel_isr_queue_table[1]));
	i_end_int(4);
}

void
_kernel_inthdr_11(void)
{
	i_begin_int(11);
	_kernel_call_isr(&(_kernel_isr_queue_table[2]));
	i_end_int(11);
}

void
_kernel_inthdr_12(void)
{
	i_begin_int(12);
	_kernel_call_isr(&(_kernel_isr_queue_table[3]));
	i_end_int(12);
}

void
_kernel_inthdr_21(void)
{
	i_begin_int(21);
	_kernel_call_isr(&(_kernel_isr_queue_table[4]));
	i_end_int(21);
}

void
_kernel_inthdr_25(void)
{
	i_begin_int(25);
	_kernel_call_isr(&(_kernel_isr_queue_table[5]));
	i_end_int(25);
}

void
_kernel_inthdr_42(void)
{
	i_begin_int(42);
	_kernel_call_isr(&(_kernel_isr_queue_table[6]));
	i_end_int(42);
}

void
_kernel_inthdr_43(void)
{
	i_begin_int(43);
	_kernel_call_isr(&(_kernel_isr_queue_table[7]));
	i_end_int(43);
}

void
_kernel_inthdr_44(void)
{
	i_begin_int(44);
	_kernel_call_isr(&(_kernel_isr_queue_table[8]));
	i_end_int(44);
}

void
_kernel_inthdr_45(void)
{
	i_begin_int(45);
	_kernel_call_isr(&(_kernel_isr_queue_table[9]));
	i_end_int(45);
}

void
_kernel_inthdr_46(void)
{
	i_begin_int(46);
	_kernel_call_isr(&(_kernel_isr_queue_table[10]));
	i_end_int(46);
}

void
_kernel_inthdr_47(void)
{
	i_begin_int(47);
	_kernel_call_isr(&(_kernel_isr_queue_table[11]));
	i_end_int(47);
}

void
_kernel_inthdr_48(void)
{
	i_begin_int(48);
	_kernel_call_isr(&(_kernel_isr_queue_table[12]));
	i_end_int(48);
}

void
_kernel_inthdr_49(void)
{
	i_begin_int(49);
	_kernel_call_isr(&(_kernel_isr_queue_table[13]));
	i_end_int(49);
}

void
_kernel_inthdr_50(void)
{
	i_begin_int(50);
	_kernel_call_isr(&(_kernel_isr_queue_table[14]));
	i_end_int(50);
}

void
_kernel_inthdr_53(void)
{
	i_begin_int(53);
	_kernel_call_isr(&(_kernel_isr_queue_table[15]));
	i_end_int(53);
}

#define TNUM_SISR	17
#define TNUM_ISR	18

const ID _kernel_tmax_isrid = (TMIN_ISRID + TNUM_ISRID - 1);
const uint_t _kernel_tnum_sisr = TNUM_SISR;

const ISRINIB _kernel_sisrinib_table[TNUM_SISR] = {
	{ (TA_NULL), (0), (INTNO_TIMER), (&(_kernel_isr_queue_table[4])), (target_timer_isr), (TMIN_ISRPRI) },
	{ (TA_NULL), (0), (INTNO_TIMER), (&(_kernel_isr_queue_table[4])), (hires_cyc_isr), (TMIN_ISRPRI) },
	{ (TA_NULL), (0), (INTNO_TIMER), (&(_kernel_isr_queue_table[4])), (hires_alm_isr), (TMIN_ISRPRI) },
	{ (TA_NULL), (0), (GPIO_B0INT), (&(_kernel_isr_queue_table[6])), (gpio_irq_dispatcher), (TMAX_ISRPRI) },
	{ (TA_NULL), (1), (GPIO_B1INT), (&(_kernel_isr_queue_table[7])), (gpio_irq_dispatcher), (TMAX_ISRPRI) },
	{ (TA_NULL), (2), (GPIO_B2INT), (&(_kernel_isr_queue_table[8])), (gpio_irq_dispatcher), (TMAX_ISRPRI) },
	{ (TA_NULL), (3), (GPIO_B3INT), (&(_kernel_isr_queue_table[9])), (gpio_irq_dispatcher), (TMAX_ISRPRI) },
	{ (TA_NULL), (4), (GPIO_B4INT), (&(_kernel_isr_queue_table[10])), (gpio_irq_dispatcher), (TMAX_ISRPRI) },
	{ (TA_NULL), (5), (GPIO_B5INT), (&(_kernel_isr_queue_table[11])), (gpio_irq_dispatcher), (TMAX_ISRPRI) },
	{ (TA_NULL), (6), (GPIO_B6INT), (&(_kernel_isr_queue_table[12])), (gpio_irq_dispatcher), (TMAX_ISRPRI) },
	{ (TA_NULL), (7), (GPIO_B7INT), (&(_kernel_isr_queue_table[13])), (gpio_irq_dispatcher), (TMAX_ISRPRI) },
	{ (TA_NULL), (8), (GPIO_B8INT), (&(_kernel_isr_queue_table[14])), (gpio_irq_dispatcher), (TMAX_ISRPRI) },
	{ (TA_NULL), (INTNO_UART_PORT2), (INTNO_UART_PORT2), (&(_kernel_isr_queue_table[5])), (uart_sensor_isr), (TMIN_ISRPRI) },
	{ (TA_NULL), (INTNO_UART_PORT3), (INTNO_UART_PORT3), (&(_kernel_isr_queue_table[1])), (uart_sensor_isr), (TMIN_ISRPRI) },
	{ (TA_NULL), (INTNO_UART_PORT4), (INTNO_UART_PORT4), (&(_kernel_isr_queue_table[0])), (uart_sensor_isr), (TMIN_ISRPRI) },
	{ (TA_NULL), (0), (SYS_INT_CCINT0), (&(_kernel_isr_queue_table[2])), (EDMA30ComplIsr), (TMIN_ISRPRI) },
	{ (TA_NULL), (SYS_INT_CCERRINT), (SYS_INT_CCERRINT), (&(_kernel_isr_queue_table[3])), (EDMA30CCErrIsr), (TMIN_ISRPRI) }
};

ISRINIB _kernel_aisrinib_table[1];

ISRCB _kernel_isrcb_table[TNUM_ISR];

#define TNUM_INHNO	18
const uint_t _kernel_tnum_inhno = TNUM_INHNO;

INTHDR_ENTRY(INTNO_I2C_TIMER, 23, inthdr_i2c_timer)
INTHDR_ENTRY(SYS_INT_USB0, 58, USB0DeviceIntHandler)
INTHDR_ENTRY(3, 3, _kernel_inthdr_3)
INTHDR_ENTRY(4, 4, _kernel_inthdr_4)
INTHDR_ENTRY(11, 11, _kernel_inthdr_11)
INTHDR_ENTRY(12, 12, _kernel_inthdr_12)
INTHDR_ENTRY(21, 21, _kernel_inthdr_21)
INTHDR_ENTRY(25, 25, _kernel_inthdr_25)
INTHDR_ENTRY(42, 42, _kernel_inthdr_42)
INTHDR_ENTRY(43, 43, _kernel_inthdr_43)
INTHDR_ENTRY(44, 44, _kernel_inthdr_44)
INTHDR_ENTRY(45, 45, _kernel_inthdr_45)
INTHDR_ENTRY(46, 46, _kernel_inthdr_46)
INTHDR_ENTRY(47, 47, _kernel_inthdr_47)
INTHDR_ENTRY(48, 48, _kernel_inthdr_48)
INTHDR_ENTRY(49, 49, _kernel_inthdr_49)
INTHDR_ENTRY(50, 50, _kernel_inthdr_50)
INTHDR_ENTRY(53, 53, _kernel_inthdr_53)

const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {
	{ (INTNO_I2C_TIMER), (TA_NULL), (FP)(INT_ENTRY(INTNO_I2C_TIMER, inthdr_i2c_timer)) },
	{ (SYS_INT_USB0), (TA_NULL), (FP)(INT_ENTRY(SYS_INT_USB0, USB0DeviceIntHandler)) },
	{ (3), (TA_NULL), (FP)(INT_ENTRY(3, _kernel_inthdr_3)) },
	{ (4), (TA_NULL), (FP)(INT_ENTRY(4, _kernel_inthdr_4)) },
	{ (11), (TA_NULL), (FP)(INT_ENTRY(11, _kernel_inthdr_11)) },
	{ (12), (TA_NULL), (FP)(INT_ENTRY(12, _kernel_inthdr_12)) },
	{ (21), (TA_NULL), (FP)(INT_ENTRY(21, _kernel_inthdr_21)) },
	{ (25), (TA_NULL), (FP)(INT_ENTRY(25, _kernel_inthdr_25)) },
	{ (42), (TA_NULL), (FP)(INT_ENTRY(42, _kernel_inthdr_42)) },
	{ (43), (TA_NULL), (FP)(INT_ENTRY(43, _kernel_inthdr_43)) },
	{ (44), (TA_NULL), (FP)(INT_ENTRY(44, _kernel_inthdr_44)) },
	{ (45), (TA_NULL), (FP)(INT_ENTRY(45, _kernel_inthdr_45)) },
	{ (46), (TA_NULL), (FP)(INT_ENTRY(46, _kernel_inthdr_46)) },
	{ (47), (TA_NULL), (FP)(INT_ENTRY(47, _kernel_inthdr_47)) },
	{ (48), (TA_NULL), (FP)(INT_ENTRY(48, _kernel_inthdr_48)) },
	{ (49), (TA_NULL), (FP)(INT_ENTRY(49, _kernel_inthdr_49)) },
	{ (50), (TA_NULL), (FP)(INT_ENTRY(50, _kernel_inthdr_50)) },
	{ (53), (TA_NULL), (FP)(INT_ENTRY(53, _kernel_inthdr_53)) }
};

#define TNUM_INTNO	18
const uint_t _kernel_tnum_intno = TNUM_INTNO;

const INTINIB _kernel_intinib_table[TNUM_INTNO] = {
	{ (INTNO_TIMER), (TA_ENAINT|INTATR_TIMER), (INTPRI_TIMER) },
	{ (GPIO_B0INT), (TA_ENAINT), (TMIN_INTPRI) },
	{ (GPIO_B1INT), (TA_ENAINT), (TMIN_INTPRI) },
	{ (GPIO_B2INT), (TA_ENAINT), (TMIN_INTPRI) },
	{ (GPIO_B3INT), (TA_ENAINT), (TMIN_INTPRI) },
	{ (GPIO_B4INT), (TA_ENAINT), (TMIN_INTPRI) },
	{ (GPIO_B5INT), (TA_ENAINT), (TMIN_INTPRI) },
	{ (GPIO_B6INT), (TA_ENAINT), (TMIN_INTPRI) },
	{ (GPIO_B7INT), (TA_ENAINT), (TMIN_INTPRI) },
	{ (GPIO_B8INT), (TA_ENAINT), (TMIN_INTPRI) },
	{ (INTNO_I2C_TIMER), (TA_ENAINT), (INTPRI_I2C_TIMER) },
	{ (INTNO_UART_PORT1), (TA_NULL), (INTPRI_UART_PORT1) },
	{ (INTNO_UART_PORT2), (TA_NULL), (INTPRI_UART_PORT2) },
	{ (INTNO_UART_PORT3), (TA_NULL), (INTPRI_UART_PORT3) },
	{ (INTNO_UART_PORT4), (TA_NULL), (INTPRI_UART_PORT4) },
	{ (SYS_INT_CCINT0), (TA_ENAINT), (TMIN_INTPRI) },
	{ (SYS_INT_CCERRINT), (TA_ENAINT), (TMIN_INTPRI) },
	{ (SYS_INT_USB0), (TA_ENAINT), (INTPRI_USBMSC) }
};

/*
 *  CPU Exception Management Functions
 */

/*
 *  Extended Service Calls
 */

const FN _kernel_tmax_fncd = TMAX_FNCD;

const SVCINIB _kernel_svcinib_table[TMAX_FNCD] = {
	{ (EXTSVC)(extsvc_syslog_wri_log), SSZ_SYSLOG_WRI_LOG },
	{ (EXTSVC)(extsvc_syslog_fwri_log), 0 },
	{ (EXTSVC)(extsvc_syslog_rea_log), SSZ_SYSLOG_REA_LOG },
	{ (EXTSVC)(extsvc_syslog_msk_log), SSZ_SYSLOG_MSK_LOG },
	{ (EXTSVC)(extsvc_syslog_ref_log), SSZ_SYSLOG_REF_LOG },
	{ NULL, 0 },
	{ (EXTSVC)(extsvc_serial_opn_por), SSZ_SERIAL_OPN_POR },
	{ (EXTSVC)(extsvc_serial_cls_por), SSZ_SERIAL_CLS_POR },
	{ (EXTSVC)(extsvc_serial_rea_dat), SSZ_SERIAL_REA_DAT },
	{ (EXTSVC)(extsvc_serial_wri_dat), SSZ_SERIAL_WRI_DAT },
	{ (EXTSVC)(extsvc_serial_ctl_por), SSZ_SERIAL_CTL_POR },
	{ (EXTSVC)(extsvc_serial_ref_por), SSZ_SERIAL_REF_POR },
	{ NULL, 0 },
	{ (EXTSVC)(extsvc_logtask_flush), SSZ_LOGTASK_FLUSH },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ NULL, 0 },
	{ (EXTSVC)(extsvc_dmloader_ins_ldm), 1024 },
	{ (EXTSVC)(extsvc_dmloader_rmv_ldm), 1024 },
	{ (EXTSVC)(extsvc_uart_sensor_config), 1024 },
	{ (EXTSVC)(extsvc_motor_command), 1024 },
	{ (EXTSVC)(extsvc_fetch_brick_info), 1024 },
	{ (EXTSVC)(extsvc_button_set_on_clicked), 1024 },
	{ (EXTSVC)(extsvc_brick_misc_command), 1024 },
	{ (EXTSVC)(extsvc__ev3_acre_cyc), 1024 },
	{ (EXTSVC)(extsvc__ev3_sta_cyc), 1024 },
	{ (EXTSVC)(extsvc__ev3_stp_cyc), 1024 },
	{ (EXTSVC)(extsvc_sound_set_vol), 1024 },
	{ (EXTSVC)(extsvc_sound_play_tone), 1024 },
	{ (EXTSVC)(extsvc_sound_play_wav), 1024 },
	{ (EXTSVC)(extsvc_newlib_open_r), 1024 },
	{ (EXTSVC)(extsvc_newlib_read_r), 1024 },
	{ (EXTSVC)(extsvc_newlib_write_r), 1024 },
	{ (EXTSVC)(extsvc_newlib_close_r), 1024 },
	{ (EXTSVC)(extsvc_newlib_lseek_r), 1024 },
	{ (EXTSVC)(extsvc_filesys_opendir), 1024 },
	{ (EXTSVC)(extsvc_filesys_readdir), 1024 },
	{ (EXTSVC)(extsvc_filesys_closedir), 1024 },
	{ (EXTSVC)(extsvc_start_i2c_transaction), 1024 },
	{ (EXTSVC)(extsvc_spp_master_test_connect), 1024 }
};

/*
 *  Stack Area for Non-task Context
 */

#ifdef DEFAULT_ISTK

#define TOPPERS_ISTKSZ		DEFAULT_ISTKSZ
#define TOPPERS_ISTK		DEFAULT_ISTK

#else /* DEAULT_ISTK */

static STK_T _kernel_istack[COUNT_STK_T(DEFAULT_ISTKSZ)] __attribute__((section(".prsv_kernel"),nocommon));

#define TOPPERS_ISTKSZ		ROUND_STK_T(DEFAULT_ISTKSZ)
#define TOPPERS_ISTK		_kernel_istack

#endif /* DEAULT_ISTK */

const SIZE		_kernel_istksz = TOPPERS_ISTKSZ;
STK_T *const	_kernel_istk = TOPPERS_ISTK;

#ifdef TOPPERS_ISTKPT
STK_T *const	_kernel_istkpt = TOPPERS_ISTKPT(TOPPERS_ISTK, TOPPERS_ISTKSZ);
#endif /* TOPPERS_ISTKPT */

/*
 *  Memory Area Allocated by Kernel
 */

static MB_T					_kernel_memory[TOPPERS_COUNT_SZ(KERNEL_HEAP_SIZE, sizeof(MB_T))];
#define TOPPERS_KMMSZ		TOPPERS_ROUND_SZ(KERNEL_HEAP_SIZE, sizeof(MB_T))
#define TOPPERS_KMM			_kernel_memory

const SIZE		_kernel_kmmsz = TOPPERS_KMMSZ;
MB_T *const		_kernel_kmm = TOPPERS_KMM;

/*
 *  Time Event Management
 */

TMEVTN   _kernel_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID];

/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_task();
	_kernel_initialize_semaphore();
	_kernel_initialize_eventflag();
	_kernel_initialize_dataqueue();
	_kernel_initialize_pridataq();
	_kernel_initialize_mutex();
	_kernel_initialize_mempfix();
	_kernel_initialize_cyclic();
	_kernel_initialize_alarm();
	_kernel_initialize_interrupt();
	_kernel_initialize_isr();
	_kernel_initialize_exception();
}

/*
 *  Initialization Routine
 */

void
_kernel_call_inirtn(void)
{
	((INIRTN)(gpio_initialize))((intptr_t)(NULL));
	((INIRTN)(target_timer_initialize))((intptr_t)(0));
	((INIRTN)(syslog_initialize))((intptr_t)(0));
	((INIRTN)(print_banner))((intptr_t)(0));
	((INIRTN)(serial_initialize))((intptr_t)(0));
	((INIRTN)(initialize_brick_dri))((intptr_t)(NULL));
	((INIRTN)(initialize_analog_dri))((intptr_t)(0));
	((INIRTN)(initialize_motor_dri))((intptr_t)(0));
	((INIRTN)(initialize_newlib_dri))((intptr_t)(0));
	((INIRTN)(initialize_i2c_dri))((intptr_t)(0));
	((INIRTN)(initialize_uart_dri))((intptr_t)(0));
	((INIRTN)(soc_edma3_initialize))((intptr_t)(0));
	((INIRTN)(initialize_sound_dri))((intptr_t)(0));
	((INIRTN)(initialize_bluetooth_dri))((intptr_t)(NULL));
	((INIRTN)(initialize_usbmsc_dri))((intptr_t)(0));
	((INIRTN)(initialize_mbed_dri))((intptr_t)(0));
	((INIRTN)(initialize_dmloader))((intptr_t)(NULL));
}

/*
 *  Termination Routine
 */

void
_kernel_call_terrtn(void)
{
	((TERRTN)(logtask_terminate))((intptr_t)(0));
	((TERRTN)(target_timer_terminate))((intptr_t)(0));
}

/*
 *  Memory Object Management Functions
 */

					
const FP _kernel_exch_tbl[TNUM_EXCH] = {
	(FP)(_kernel_default_exc_handler), /* 0 */
	(FP)(_kernel_default_exc_handler), /* 1 */
	(FP)(_kernel_default_exc_handler), /* 2 */
	(FP)(ldr_prefetch_handler), /* 3 */
	(FP)(ldr_data_abort_handler), /* 4 */
	(FP)(_kernel_default_exc_handler), /* 5 */
	(FP)(_kernel_default_exc_handler), /* 6 */
	(FP)(_kernel_default_exc_handler), /* 7 */
	(FP)(_kernel_default_exc_handler), /* 8 */

};



const uint8_t _kernel_cfgint_tbl[101] = {
 	0U, /* 0x000 */
 	0U, /* 0x001 */
 	0U, /* 0x002 */
 	1U, /* 0x003 */
 	1U, /* 0x004 */
 	0U, /* 0x005 */
 	0U, /* 0x006 */
 	0U, /* 0x007 */
 	0U, /* 0x008 */
 	0U, /* 0x009 */
 	0U, /* 0x00a */
 	1U, /* 0x00b */
 	1U, /* 0x00c */
 	0U, /* 0x00d */
 	0U, /* 0x00e */
 	0U, /* 0x00f */
 	0U, /* 0x010 */
 	0U, /* 0x011 */
 	0U, /* 0x012 */
 	0U, /* 0x013 */
 	0U, /* 0x014 */
 	1U, /* 0x015 */
 	0U, /* 0x016 */
 	1U, /* 0x017 */
 	0U, /* 0x018 */
 	1U, /* 0x019 */
 	0U, /* 0x01a */
 	0U, /* 0x01b */
 	0U, /* 0x01c */
 	0U, /* 0x01d */
 	0U, /* 0x01e */
 	0U, /* 0x01f */
 	0U, /* 0x020 */
 	0U, /* 0x021 */
 	0U, /* 0x022 */
 	0U, /* 0x023 */
 	0U, /* 0x024 */
 	0U, /* 0x025 */
 	0U, /* 0x026 */
 	0U, /* 0x027 */
 	0U, /* 0x028 */
 	0U, /* 0x029 */
 	1U, /* 0x02a */
 	1U, /* 0x02b */
 	1U, /* 0x02c */
 	1U, /* 0x02d */
 	1U, /* 0x02e */
 	1U, /* 0x02f */
 	1U, /* 0x030 */
 	1U, /* 0x031 */
 	1U, /* 0x032 */
 	0U, /* 0x033 */
 	0U, /* 0x034 */
 	1U, /* 0x035 */
 	0U, /* 0x036 */
 	0U, /* 0x037 */
 	0U, /* 0x038 */
 	0U, /* 0x039 */
 	1U, /* 0x03a */
 	0U, /* 0x03b */
 	0U, /* 0x03c */
 	0U, /* 0x03d */
 	0U, /* 0x03e */
 	0U, /* 0x03f */
 	0U, /* 0x040 */
 	0U, /* 0x041 */
 	0U, /* 0x042 */
 	0U, /* 0x043 */
 	0U, /* 0x044 */
 	0U, /* 0x045 */
 	0U, /* 0x046 */
 	0U, /* 0x047 */
 	0U, /* 0x048 */
 	0U, /* 0x049 */
 	0U, /* 0x04a */
 	0U, /* 0x04b */
 	0U, /* 0x04c */
 	0U, /* 0x04d */
 	0U, /* 0x04e */
 	0U, /* 0x04f */
 	0U, /* 0x050 */
 	0U, /* 0x051 */
 	0U, /* 0x052 */
 	0U, /* 0x053 */
 	0U, /* 0x054 */
 	0U, /* 0x055 */
 	0U, /* 0x056 */
 	0U, /* 0x057 */
 	0U, /* 0x058 */
 	0U, /* 0x059 */
 	0U, /* 0x05a */
 	0U, /* 0x05b */
 	0U, /* 0x05c */
 	0U, /* 0x05d */
 	0U, /* 0x05e */
 	0U, /* 0x05f */
 	0U, /* 0x060 */
 	0U, /* 0x061 */
 	0U, /* 0x062 */
 	0U, /* 0x063 */
 	0U, /* 0x064 */

};


