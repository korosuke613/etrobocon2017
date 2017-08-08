/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2005-2014 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  $Id: allfunc.h 994 2014-04-18 08:48:40Z ertl-hiro $
 */

/*
 *		すべての関数をコンパイルするための定義
 */

#ifndef TOPPERS_ALLFUNC_H
#define TOPPERS_ALLFUNC_H

/* startup.c */
#define TOPPERS_sta_ker
#define TOPPERS_ext_ker
#define TOPPERS_kermem

/* task.c */
#define TOPPERS_tskini
#define TOPPERS_tsksched
#define TOPPERS_tskrun
#define TOPPERS_tsknrun
#define TOPPERS_tskdmt
#define TOPPERS_tskact
#define TOPPERS_tskpri
#define TOPPERS_tskrot
#define TOPPERS_tsktex

/* wait.c */
#define TOPPERS_waimake
#define TOPPERS_waicmp
#define TOPPERS_waitmo
#define TOPPERS_waitmook
#define TOPPERS_wairel
#define TOPPERS_wobjwai
#define TOPPERS_wobjwaitmo
#define TOPPERS_iniwque

/* memory.c */
#define TOPPERS_memini
#define TOPPERS_memsearch
#define TOPPERS_memprbw
#define TOPPERS_memprbr
#define TOPPERS_memvalm
#define TOPPERS_memvalk
#define TOPPERS_secini

/* time_event.c */
#define TOPPERS_tmeini
#define TOPPERS_tmeup
#define TOPPERS_tmedown
#define TOPPERS_tmeins
#define TOPPERS_tmedel
#define TOPPERS_tmeltim
#define TOPPERS_sigtim

/* task_manage.c */
#define TOPPERS_acre_tsk
#define TOPPERS_sac_tsk
#define TOPPERS_del_tsk
#define TOPPERS_act_tsk
#define TOPPERS_iact_tsk
#define TOPPERS_can_act
#define TOPPERS_ext_tsk
#define TOPPERS_ter_tsk
#define TOPPERS_chg_pri
#define TOPPERS_get_pri
#define TOPPERS_get_inf

/* task_refer.c */
#define TOPPERS_ref_tsk

/* task_sync.c */
#define TOPPERS_slp_tsk
#define TOPPERS_tslp_tsk
#define TOPPERS_wup_tsk
#define TOPPERS_iwup_tsk
#define TOPPERS_can_wup
#define TOPPERS_rel_wai
#define TOPPERS_irel_wai
#define TOPPERS_sus_tsk
#define TOPPERS_rsm_tsk
#define TOPPERS_dis_wai
#define TOPPERS_idis_wai
#define TOPPERS_ena_wai
#define TOPPERS_iena_wai
#define TOPPERS_dly_tsk

/* task_except.c */
#define TOPPERS_def_tex
#define TOPPERS_ras_tex
#define TOPPERS_iras_tex
#define TOPPERS_dis_tex
#define TOPPERS_ena_tex
#define TOPPERS_sns_tex
#define TOPPERS_ref_tex

/* semaphore.c */
#define TOPPERS_semini
#define TOPPERS_acre_sem
#define TOPPERS_sac_sem
#define TOPPERS_del_sem
#define TOPPERS_sig_sem
#define TOPPERS_isig_sem
#define TOPPERS_wai_sem
#define TOPPERS_pol_sem
#define TOPPERS_twai_sem
#define TOPPERS_ini_sem
#define TOPPERS_ref_sem

/* eventflag.c */
#define TOPPERS_flgini
#define TOPPERS_flgcnd
#define TOPPERS_acre_flg
#define TOPPERS_sac_flg
#define TOPPERS_del_flg
#define TOPPERS_set_flg
#define TOPPERS_iset_flg
#define TOPPERS_clr_flg
#define TOPPERS_wai_flg
#define TOPPERS_pol_flg
#define TOPPERS_twai_flg
#define TOPPERS_ini_flg
#define TOPPERS_ref_flg

/* dataqueue.c */
#define TOPPERS_dtqini
#define TOPPERS_dtqenq
#define TOPPERS_dtqfenq
#define TOPPERS_dtqdeq
#define TOPPERS_dtqsnd
#define TOPPERS_dtqfsnd
#define TOPPERS_dtqrcv
#define TOPPERS_acre_dtq
#define TOPPERS_sac_dtq
#define TOPPERS_del_dtq
#define TOPPERS_snd_dtq
#define TOPPERS_psnd_dtq
#define TOPPERS_ipsnd_dtq
#define TOPPERS_tsnd_dtq
#define TOPPERS_fsnd_dtq
#define TOPPERS_ifsnd_dtq
#define TOPPERS_rcv_dtq
#define TOPPERS_prcv_dtq
#define TOPPERS_trcv_dtq
#define TOPPERS_ini_dtq
#define TOPPERS_ref_dtq

/* pridataq.c */
#define TOPPERS_pdqini
#define TOPPERS_pdqenq
#define TOPPERS_pdqdeq
#define TOPPERS_pdqsnd
#define TOPPERS_pdqrcv
#define TOPPERS_acre_pdq
#define TOPPERS_sac_pdq
#define TOPPERS_del_pdq
#define TOPPERS_snd_pdq
#define TOPPERS_psnd_pdq
#define TOPPERS_ipsnd_pdq
#define TOPPERS_tsnd_pdq
#define TOPPERS_rcv_pdq
#define TOPPERS_prcv_pdq
#define TOPPERS_trcv_pdq
#define TOPPERS_ini_pdq
#define TOPPERS_ref_pdq

/* mutex.c */
#define TOPPERS_mtxhook
#define TOPPERS_mtxini
#define TOPPERS_mtxchk
#define TOPPERS_mtxscan
#define TOPPERS_mtxcalc
#define TOPPERS_mtxrel
#define TOPPERS_mtxrela
#define TOPPERS_acre_mtx
#define TOPPERS_sac_mtx
#define TOPPERS_del_mtx
#define TOPPERS_loc_mtx
#define TOPPERS_ploc_mtx
#define TOPPERS_tloc_mtx
#define TOPPERS_unl_mtx
#define TOPPERS_ini_mtx
#define TOPPERS_ref_mtx

/* mempfix.c */
#define TOPPERS_mpfini
#define TOPPERS_mpfget
#define TOPPERS_acre_mpf
#define TOPPERS_sac_mpf
#define TOPPERS_del_mpf
#define TOPPERS_get_mpf
#define TOPPERS_pget_mpf
#define TOPPERS_tget_mpf
#define TOPPERS_rel_mpf
#define TOPPERS_ini_mpf
#define TOPPERS_ref_mpf

/* time_manage.c */
#define TOPPERS_get_tim
#define TOPPERS_get_utm

/* cyclic.c */
#define TOPPERS_cycini
#define TOPPERS_acre_cyc
#define TOPPERS_sac_cyc
#define TOPPERS_del_cyc
#define TOPPERS_sta_cyc
#define TOPPERS_stp_cyc
#define TOPPERS_ref_cyc
#define TOPPERS_cyccal

/* alarm.c */
#define TOPPERS_almini
#define TOPPERS_acre_alm
#define TOPPERS_sac_alm
#define TOPPERS_del_alm
#define TOPPERS_sta_alm
#define TOPPERS_ista_alm
#define TOPPERS_stp_alm
#define TOPPERS_istp_alm
#define TOPPERS_ref_alm
#define TOPPERS_almcal

/* overrun.c */
#define TOPPERS_ovrini
#define TOPPERS_ovrsta
#define TOPPERS_ovrstp
#define TOPPERS_sta_ovr
#define TOPPERS_ista_ovr
#define TOPPERS_stp_ovr
#define TOPPERS_istp_ovr
#define TOPPERS_ref_ovr
#define TOPPERS_ovrcal

/* sys_manage.c */
#define TOPPERS_rot_rdq
#define TOPPERS_irot_rdq
#define TOPPERS_get_did
#define TOPPERS_get_tid
#define TOPPERS_iget_tid
#define TOPPERS_loc_cpu
#define TOPPERS_iloc_cpu
#define TOPPERS_unl_cpu
#define TOPPERS_iunl_cpu
#define TOPPERS_dis_dsp
#define TOPPERS_ena_dsp
#define TOPPERS_sns_ctx
#define TOPPERS_sns_loc
#define TOPPERS_sns_dsp
#define TOPPERS_sns_dpn
#define TOPPERS_sns_ker

/* mem_manage.c */
#define TOPPERS_prb_mem

/* interrupt.c */
#define TOPPERS_isrini
#define TOPPERS_isrcal
#define TOPPERS_acre_isr
#define TOPPERS_sac_isr
#define TOPPERS_del_isr
#define TOPPERS_intini
#define TOPPERS_dis_int
#define TOPPERS_ena_int
#define TOPPERS_chg_ipm
#define TOPPERS_get_ipm

/* exception.c */
#define TOPPERS_excini
#define TOPPERS_xsns_dpn
#define TOPPERS_xsns_xpn

#endif /* TOPPERS_ALLFUNC_H */
