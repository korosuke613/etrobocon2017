/* This file is generated from kernel_rename.def by genrename. */

/* This file is included only when kernel_rename.h has been included. */
#ifdef TOPPERS_KERNEL_RENAME_H
#undef TOPPERS_KERNEL_RENAME_H

/*
 *  startup.c
 */
#undef kerflg
#undef exit_kernel
#undef initialize_kmm
#undef kernel_malloc
#undef kernel_free

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
#undef free_tcb
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
#undef valid_memobj
#undef valid_memobj_kernel
#undef initialize_sections

/*
 *  wait.c
 */
#undef make_wait_tmout
#undef wait_complete
#undef wait_tmout
#undef wait_tmout_ok
#undef wait_release
#undef wobj_make_wait
#undef wobj_make_wait_tmout
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
#undef free_semcb
#undef initialize_semaphore

/*
 *  eventflag.c
 */
#undef free_flgcb
#undef initialize_eventflag
#undef check_flg_cond

/*
 *  dataqueue.c
 */
#undef free_dtqcb
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
#undef free_pdqcb
#undef initialize_pridataq
#undef enqueue_pridata
#undef dequeue_pridata
#undef send_pridata
#undef receive_pridata

/*
 *  mutex.c
 */
#undef free_mtxcb
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
 *  mempfix.c
 */
#undef free_mpfcb
#undef initialize_mempfix
#undef get_mpf_block

/*
 *  cyclic.c
 */
#undef free_cyccb
#undef initialize_cyclic
#undef call_cychdr

/*
 *  alarm.c
 */
#undef free_almcb
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
#undef free_isrcb
#undef initialize_isr
#undef call_isr
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
#undef tmax_stskid
#undef tinib_table
#undef atinib_table
#undef torder_table
#undef tcb_table
#undef tmax_semid
#undef tmax_ssemid
#undef seminib_table
#undef aseminib_table
#undef semcb_table
#undef tmax_flgid
#undef tmax_sflgid
#undef flginib_table
#undef aflginib_table
#undef flgcb_table
#undef tmax_dtqid
#undef tmax_sdtqid
#undef dtqinib_table
#undef adtqinib_table
#undef dtqcb_table
#undef tmax_pdqid
#undef tmax_spdqid
#undef pdqinib_table
#undef apdqinib_table
#undef pdqcb_table
#undef tmax_mtxid
#undef tmax_smtxid
#undef mtxinib_table
#undef amtxinib_table
#undef mtxcb_table
#undef tmax_mpfid
#undef tmax_smpfid
#undef mpfinib_table
#undef ampfinib_table
#undef mpfcb_table
#undef tmax_cycid
#undef tmax_scycid
#undef cycinib_table
#undef acycinib_table
#undef cyccb_table
#undef tmax_almid
#undef tmax_salmid
#undef alminib_table
#undef aalminib_table
#undef almcb_table
#undef ovrinib
#undef sysstat_acvct
#undef tnum_meminib
#undef memtop_table
#undef meminib_table
#undef tnum_meminfo
#undef meminfo_table
#undef tnum_isr_queue
#undef isr_queue_table
#undef isr_queue_list
#undef tmax_isrid
#undef tnum_sisr
#undef sisrinib_table
#undef aisrinib_table
#undef isrcb_table
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
#undef kmmsz
#undef kmm
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
#undef _initialize_kmm
#undef _kernel_malloc
#undef _kernel_free

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
#undef _free_tcb
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
#undef _valid_memobj
#undef _valid_memobj_kernel
#undef _initialize_sections

/*
 *  wait.c
 */
#undef _make_wait_tmout
#undef _wait_complete
#undef _wait_tmout
#undef _wait_tmout_ok
#undef _wait_release
#undef _wobj_make_wait
#undef _wobj_make_wait_tmout
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
#undef _free_semcb
#undef _initialize_semaphore

/*
 *  eventflag.c
 */
#undef _free_flgcb
#undef _initialize_eventflag
#undef _check_flg_cond

/*
 *  dataqueue.c
 */
#undef _free_dtqcb
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
#undef _free_pdqcb
#undef _initialize_pridataq
#undef _enqueue_pridata
#undef _dequeue_pridata
#undef _send_pridata
#undef _receive_pridata

/*
 *  mutex.c
 */
#undef _free_mtxcb
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
 *  mempfix.c
 */
#undef _free_mpfcb
#undef _initialize_mempfix
#undef _get_mpf_block

/*
 *  cyclic.c
 */
#undef _free_cyccb
#undef _initialize_cyclic
#undef _call_cychdr

/*
 *  alarm.c
 */
#undef _free_almcb
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
#undef _free_isrcb
#undef _initialize_isr
#undef _call_isr
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
#undef _tmax_stskid
#undef _tinib_table
#undef _atinib_table
#undef _torder_table
#undef _tcb_table
#undef _tmax_semid
#undef _tmax_ssemid
#undef _seminib_table
#undef _aseminib_table
#undef _semcb_table
#undef _tmax_flgid
#undef _tmax_sflgid
#undef _flginib_table
#undef _aflginib_table
#undef _flgcb_table
#undef _tmax_dtqid
#undef _tmax_sdtqid
#undef _dtqinib_table
#undef _adtqinib_table
#undef _dtqcb_table
#undef _tmax_pdqid
#undef _tmax_spdqid
#undef _pdqinib_table
#undef _apdqinib_table
#undef _pdqcb_table
#undef _tmax_mtxid
#undef _tmax_smtxid
#undef _mtxinib_table
#undef _amtxinib_table
#undef _mtxcb_table
#undef _tmax_mpfid
#undef _tmax_smpfid
#undef _mpfinib_table
#undef _ampfinib_table
#undef _mpfcb_table
#undef _tmax_cycid
#undef _tmax_scycid
#undef _cycinib_table
#undef _acycinib_table
#undef _cyccb_table
#undef _tmax_almid
#undef _tmax_salmid
#undef _alminib_table
#undef _aalminib_table
#undef _almcb_table
#undef _ovrinib
#undef _sysstat_acvct
#undef _tnum_meminib
#undef _memtop_table
#undef _meminib_table
#undef _tnum_meminfo
#undef _meminfo_table
#undef _tnum_isr_queue
#undef _isr_queue_table
#undef _isr_queue_list
#undef _tmax_isrid
#undef _tnum_sisr
#undef _sisrinib_table
#undef _aisrinib_table
#undef _isrcb_table
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
#undef _kmmsz
#undef _kmm
#undef _tnum_datasec
#undef _datasecinib_table
#undef _tnum_bsssec
#undef _bsssecinib_table


#endif /* TOPPERS_LABEL_ASM */

#include "target_unrename.h"

#endif /* TOPPERS_KERNEL_RENAME_H */
