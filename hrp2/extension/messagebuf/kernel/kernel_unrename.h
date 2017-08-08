/* This file is generated from kernel_rename.def by genrename. */

/* This file is included only when kernel_rename.h has been included. */
#ifdef TOPPERS_KERNEL_RENAME_H
#undef TOPPERS_KERNEL_RENAME_H

/*
 *  startup.c
 */
#undef kerflg
#undef exit_kernel

/*
 *  task.c
 */
#undef p_runtsk
#undef rundom
#undef p_ctxdom
#undef p_schedtsk
#undef reqflg
#undef ipmflg
#undef disdsp
#undef dspflg
#undef ready_queue
#undef ready_primap
#undef initialize_task
#undef search_schedtsk
#undef make_runnable
#undef make_non_runnable
#undef make_dormant
#undef make_active
#undef change_priority
#undef rotate_ready_queue
#undef call_texrtn_stask
#undef calltex_stask

/*
 *  memory.c
 */
#undef initialize_memory
#undef search_meminib
#undef probe_mem_write
#undef probe_mem_read
#undef initialize_sections

/*
 *  wait.c
 */
#undef make_wait_tmout
#undef wait_dequeue_wobj
#undef wait_complete
#undef wait_tmout
#undef wait_tmout_ok
#undef wait_release
#undef wobj_make_wait
#undef wobj_make_wait_tmout
#undef wobj_change_priority
#undef init_wait_queue

/*
 *  time_event.c
 */
#undef current_time
#undef min_time
#undef next_time
#undef next_subtime
#undef last_index
#undef initialize_tmevt
#undef tmevt_up
#undef tmevt_down
#undef tmevtb_insert
#undef tmevtb_delete
#undef tmevt_lefttim
#undef signal_time

/*
 *  semaphore.c
 */
#undef initialize_semaphore

/*
 *  eventflag.c
 */
#undef initialize_eventflag
#undef check_flg_cond

/*
 *  dataqueue.c
 */
#undef initialize_dataqueue
#undef enqueue_data
#undef force_enqueue_data
#undef dequeue_data
#undef send_data
#undef force_send_data
#undef receive_data

/*
 *  pridataq.c
 */
#undef initialize_pridataq
#undef enqueue_pridata
#undef dequeue_pridata
#undef send_pridata
#undef receive_pridata

/*
 *  mutex.c
 */
#undef mtxhook_check_ceilpri
#undef mtxhook_scan_ceilmtx
#undef mtxhook_release_all
#undef initialize_mutex
#undef mutex_check_ceilpri
#undef mutex_scan_ceilmtx
#undef mutex_calc_priority
#undef mutex_release
#undef mutex_release_all

/*
 *  messagebuf.c
 */
#undef mbfhook_dequeue_wobj
#undef mbfhook_change_priority
#undef initialize_messagebuf
#undef enqueue_message
#undef dequeue_message
#undef send_message
#undef messagebuf_signal
#undef receive_message
#undef messagebuf_dequeue_wobj
#undef messagebuf_change_priority

/*
 *  mempfix.c
 */
#undef initialize_mempfix
#undef get_mpf_block

/*
 *  cyclic.c
 */
#undef initialize_cyclic
#undef call_cychdr

/*
 *  alarm.c
 */
#undef initialize_alarm
#undef call_almhdr

/*
 *  overrun.c
 */
#undef initialize_overrun
#undef ovrtimer_start
#undef ovrtimer_stop
#undef call_ovrhdr

/*
 *  interrupt.c
 */
#undef initialize_interrupt

/*
 *  exception.c
 */
#undef initialize_exception

/*
 *  svc_table.c
 */
#undef svc_table

/*
 *  kernel_cfg.c
 */
#undef initialize_object
#undef call_inirtn
#undef call_terrtn
#undef tmax_domid
#undef dominib_table
#undef dominib_kernel
#undef tmax_tskid
#undef tinib_table
#undef torder_table
#undef tcb_table
#undef tmax_semid
#undef seminib_table
#undef semcb_table
#undef tmax_flgid
#undef flginib_table
#undef flgcb_table
#undef tmax_dtqid
#undef dtqinib_table
#undef dtqcb_table
#undef tmax_pdqid
#undef pdqinib_table
#undef pdqcb_table
#undef tmax_mtxid
#undef mtxinib_table
#undef mtxcb_table
#undef tmax_mbfid
#undef mbfinib_table
#undef mbfcb_table
#undef tmax_mpfid
#undef mpfinib_table
#undef mpfcb_table
#undef tmax_cycid
#undef cycinib_table
#undef cyccb_table
#undef tmax_almid
#undef alminib_table
#undef almcb_table
#undef ovrinib
#undef sysstat_acvct
#undef tnum_meminib
#undef memtop_table
#undef meminib_table
#undef tnum_meminfo
#undef meminfo_table
#undef tnum_inhno
#undef inhinib_table
#undef tnum_intno
#undef intinib_table
#undef tnum_excno
#undef excinib_table
#undef tmax_fncd
#undef svcinib_table
#undef tmevt_heap
#undef istksz
#undef istk
#undef istkpt
#undef tnum_datasec
#undef datasecinib_table
#undef tnum_bsssec
#undef bsssecinib_table


#ifdef TOPPERS_LABEL_ASM

/*
 *  startup.c
 */
#undef _kerflg
#undef _exit_kernel

/*
 *  task.c
 */
#undef _p_runtsk
#undef _rundom
#undef _p_ctxdom
#undef _p_schedtsk
#undef _reqflg
#undef _ipmflg
#undef _disdsp
#undef _dspflg
#undef _ready_queue
#undef _ready_primap
#undef _initialize_task
#undef _search_schedtsk
#undef _make_runnable
#undef _make_non_runnable
#undef _make_dormant
#undef _make_active
#undef _change_priority
#undef _rotate_ready_queue
#undef _call_texrtn_stask
#undef _calltex_stask

/*
 *  memory.c
 */
#undef _initialize_memory
#undef _search_meminib
#undef _probe_mem_write
#undef _probe_mem_read
#undef _initialize_sections

/*
 *  wait.c
 */
#undef _make_wait_tmout
#undef _wait_dequeue_wobj
#undef _wait_complete
#undef _wait_tmout
#undef _wait_tmout_ok
#undef _wait_release
#undef _wobj_make_wait
#undef _wobj_make_wait_tmout
#undef _wobj_change_priority
#undef _init_wait_queue

/*
 *  time_event.c
 */
#undef _current_time
#undef _min_time
#undef _next_time
#undef _next_subtime
#undef _last_index
#undef _initialize_tmevt
#undef _tmevt_up
#undef _tmevt_down
#undef _tmevtb_insert
#undef _tmevtb_delete
#undef _tmevt_lefttim
#undef _signal_time

/*
 *  semaphore.c
 */
#undef _initialize_semaphore

/*
 *  eventflag.c
 */
#undef _initialize_eventflag
#undef _check_flg_cond

/*
 *  dataqueue.c
 */
#undef _initialize_dataqueue
#undef _enqueue_data
#undef _force_enqueue_data
#undef _dequeue_data
#undef _send_data
#undef _force_send_data
#undef _receive_data

/*
 *  pridataq.c
 */
#undef _initialize_pridataq
#undef _enqueue_pridata
#undef _dequeue_pridata
#undef _send_pridata
#undef _receive_pridata

/*
 *  mutex.c
 */
#undef _mtxhook_check_ceilpri
#undef _mtxhook_scan_ceilmtx
#undef _mtxhook_release_all
#undef _initialize_mutex
#undef _mutex_check_ceilpri
#undef _mutex_scan_ceilmtx
#undef _mutex_calc_priority
#undef _mutex_release
#undef _mutex_release_all

/*
 *  messagebuf.c
 */
#undef _mbfhook_dequeue_wobj
#undef _mbfhook_change_priority
#undef _initialize_messagebuf
#undef _enqueue_message
#undef _dequeue_message
#undef _send_message
#undef _messagebuf_signal
#undef _receive_message
#undef _messagebuf_dequeue_wobj
#undef _messagebuf_change_priority

/*
 *  mempfix.c
 */
#undef _initialize_mempfix
#undef _get_mpf_block

/*
 *  cyclic.c
 */
#undef _initialize_cyclic
#undef _call_cychdr

/*
 *  alarm.c
 */
#undef _initialize_alarm
#undef _call_almhdr

/*
 *  overrun.c
 */
#undef _initialize_overrun
#undef _ovrtimer_start
#undef _ovrtimer_stop
#undef _call_ovrhdr

/*
 *  interrupt.c
 */
#undef _initialize_interrupt

/*
 *  exception.c
 */
#undef _initialize_exception

/*
 *  svc_table.c
 */
#undef _svc_table

/*
 *  kernel_cfg.c
 */
#undef _initialize_object
#undef _call_inirtn
#undef _call_terrtn
#undef _tmax_domid
#undef _dominib_table
#undef _dominib_kernel
#undef _tmax_tskid
#undef _tinib_table
#undef _torder_table
#undef _tcb_table
#undef _tmax_semid
#undef _seminib_table
#undef _semcb_table
#undef _tmax_flgid
#undef _flginib_table
#undef _flgcb_table
#undef _tmax_dtqid
#undef _dtqinib_table
#undef _dtqcb_table
#undef _tmax_pdqid
#undef _pdqinib_table
#undef _pdqcb_table
#undef _tmax_mtxid
#undef _mtxinib_table
#undef _mtxcb_table
#undef _tmax_mbfid
#undef _mbfinib_table
#undef _mbfcb_table
#undef _tmax_mpfid
#undef _mpfinib_table
#undef _mpfcb_table
#undef _tmax_cycid
#undef _cycinib_table
#undef _cyccb_table
#undef _tmax_almid
#undef _alminib_table
#undef _almcb_table
#undef _ovrinib
#undef _sysstat_acvct
#undef _tnum_meminib
#undef _memtop_table
#undef _meminib_table
#undef _tnum_meminfo
#undef _meminfo_table
#undef _tnum_inhno
#undef _inhinib_table
#undef _tnum_intno
#undef _intinib_table
#undef _tnum_excno
#undef _excinib_table
#undef _tmax_fncd
#undef _svcinib_table
#undef _tmevt_heap
#undef _istksz
#undef _istk
#undef _istkpt
#undef _tnum_datasec
#undef _datasecinib_table
#undef _tnum_bsssec
#undef _bsssecinib_table


#endif /* TOPPERS_LABEL_ASM */

#include "target_unrename.h"

#endif /* TOPPERS_KERNEL_RENAME_H */
