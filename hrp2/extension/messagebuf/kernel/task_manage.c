/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  $Id: task_manage.c 1003 2014-04-23 11:58:48Z ertl-hiro $
 */

/*
 *		タスク管理機能
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "mutex.h"
#include "overrun.h"

/*
 *  トレースログマクロのデフォルト定義
 */
#ifndef LOG_ACT_TSK_ENTER
#define LOG_ACT_TSK_ENTER(tskid)
#endif /* LOG_ACT_TSK_ENTER */

#ifndef LOG_ACT_TSK_LEAVE
#define LOG_ACT_TSK_LEAVE(ercd)
#endif /* LOG_ACT_TSK_LEAVE */

#ifndef LOG_IACT_TSK_ENTER
#define LOG_IACT_TSK_ENTER(tskid)
#endif /* LOG_IACT_TSK_ENTER */

#ifndef LOG_IACT_TSK_LEAVE
#define LOG_IACT_TSK_LEAVE(ercd)
#endif /* LOG_IACT_TSK_LEAVE */

#ifndef LOG_CAN_ACT_ENTER
#define LOG_CAN_ACT_ENTER(tskid)
#endif /* LOG_CAN_ACT_ENTER */

#ifndef LOG_CAN_ACT_LEAVE
#define LOG_CAN_ACT_LEAVE(ercd)
#endif /* LOG_CAN_ACT_LEAVE */

#ifndef LOG_EXT_TSK_ENTER
#define LOG_EXT_TSK_ENTER()
#endif /* LOG_EXT_TSK_ENTER */

#ifndef LOG_EXT_TSK_LEAVE
#define LOG_EXT_TSK_LEAVE(ercd)
#endif /* LOG_EXT_TSK_LEAVE */

#ifndef LOG_TER_TSK_ENTER
#define LOG_TER_TSK_ENTER(tskid)
#endif /* LOG_TER_TSK_ENTER */

#ifndef LOG_TER_TSK_LEAVE
#define LOG_TER_TSK_LEAVE(ercd)
#endif /* LOG_TER_TSK_LEAVE */

#ifndef LOG_CHG_PRI_ENTER
#define LOG_CHG_PRI_ENTER(tskid, tskpri)
#endif /* LOG_CHG_PRI_ENTER */

#ifndef LOG_CHG_PRI_LEAVE
#define LOG_CHG_PRI_LEAVE(ercd)
#endif /* LOG_CHG_PRI_LEAVE */

#ifndef LOG_GET_PRI_ENTER
#define LOG_GET_PRI_ENTER(tskid, p_tskpri)
#endif /* LOG_GET_PRI_ENTER */

#ifndef LOG_GET_PRI_LEAVE
#define LOG_GET_PRI_LEAVE(ercd, tskpri)
#endif /* LOG_GET_PRI_LEAVE */

#ifndef LOG_GET_INF_ENTER
#define LOG_GET_INF_ENTER(p_exinf)
#endif /* LOG_GET_INF_ENTER */

#ifndef LOG_GET_INF_LEAVE
#define LOG_GET_INF_LEAVE(ercd, exinf)
#endif /* LOG_GET_INF_LEAVE */

/*
 *  タスクの起動
 */
#ifdef TOPPERS_act_tsk

ER
act_tsk(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;

	LOG_ACT_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	p_tcb = get_tcb_self(tskid);
	CHECK_ACPTN(p_tcb->p_tinib->acvct.acptn1);

	t_lock_cpu();
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		if (make_active(p_tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (!(p_tcb->actque)) {
		p_tcb->actque = true;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	t_unlock_cpu();

  error_exit:
	LOG_ACT_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_act_tsk */

/*
 *  タスクの起動（非タスクコンテキスト用）
 */
#ifdef TOPPERS_iact_tsk

ER
iact_tsk(ID tskid)
{
	TCB		*p_tcb;
	ER		ercd;

	LOG_IACT_TSK_ENTER(tskid);
	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	p_tcb = get_tcb(tskid);

	i_lock_cpu();
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		if (make_active(p_tcb)) {
			reqflg = true;
		}
		ercd = E_OK;
	}
	else if (!(p_tcb->actque)) {
		p_tcb->actque = true;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	i_unlock_cpu();

  error_exit:
	LOG_IACT_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_iact_tsk */

/*
 *  タスク起動要求のキャンセル
 */
#ifdef TOPPERS_can_act

ER_UINT
can_act(ID tskid)
{
	TCB		*p_tcb;
	ER_UINT	ercd;

	LOG_CAN_ACT_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	p_tcb = get_tcb_self(tskid);
	CHECK_ACPTN(p_tcb->p_tinib->acvct.acptn1);

	t_lock_cpu();
	ercd = p_tcb->actque ? 1 : 0;
	p_tcb->actque = false;
	t_unlock_cpu();

  error_exit:
	LOG_CAN_ACT_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_can_act */

/*
 *  自タスクの終了
 */
#ifdef TOPPERS_ext_tsk

ER
ext_tsk(void)
{
	ER		ercd;

	LOG_EXT_TSK_ENTER();
	CHECK_TSKCTX();

	if (t_sense_lock()) {
		/*
		 *  CPUロック状態でext_tskが呼ばれた場合は，CPUロックを解除し
		 *  てからタスクを終了する．実装上は，サービスコール内でのCPU
		 *  ロックを省略すればよいだけ．
		 */
	}
	else {
		t_lock_cpu();
	}
	if (disdsp) {
		/*
		 *  ディスパッチ禁止状態でext_tskが呼ばれた場合は，ディスパッ
		 *  チ許可状態にしてからタスクを終了する．
		 */
		disdsp = false;
	}
	if (!ipmflg) {
		/*
		 *  割込み優先度マスク（IPM）がTIPM_ENAALL以外の状態でext_tsk
		 *  が呼ばれた場合は，IPMをTIPM_ENAALLにしてからタスクを終了す
		 *  る．
		 */
		t_set_ipm(TIPM_ENAALL);
		ipmflg = true;
	}
	dspflg = true;

	(void) make_non_runnable(p_runtsk);
	if (!queue_empty(&(p_runtsk->mutex_queue))) {
		(void) (*mtxhook_release_all)(p_runtsk);
	}
#ifdef TOPPERS_SUPPORT_OVRHDR
	ovrtimer_stop();
#endif /* TOPPERS_SUPPORT_OVRHDR */
	make_dormant(p_runtsk);
	if (p_runtsk->actque) {
		p_runtsk->actque = false;
		(void) make_active(p_runtsk);
	}
	exit_and_dispatch();
	ercd = E_SYS;

  error_exit:
	LOG_EXT_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ext_tsk */

/*
 *  タスクの強制終了
 */
#ifdef TOPPERS_ter_tsk

ER
ter_tsk(ID tskid)
{
	TCB		*p_tcb;
	bool_t	dspreq = false;
	ER		ercd;

	LOG_TER_TSK_ENTER(tskid);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	p_tcb = get_tcb(tskid);
	CHECK_NONSELF(p_tcb);
	CHECK_ACPTN(p_tcb->p_tinib->acvct.acptn2);

	t_lock_cpu();
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
		if (TSTAT_RUNNABLE(p_tcb->tstat)) {
			/*
			 *  p_tcbは自タスクでないため，（シングルプロセッサでは）実
			 *  行状態でなく，make_non_runnable(p_tcb)でタスクディスパッ
			 *  チが必要になることはない．
			 */
			(void) make_non_runnable(p_tcb);
		}
		else if (TSTAT_WAITING(p_tcb->tstat)) {
			if (wait_dequeue_wobj(p_tcb)) {
				dspreq = true;
			}
			wait_dequeue_tmevtb(p_tcb);
		}
		if (!queue_empty(&(p_tcb->mutex_queue))) {
			if ((*mtxhook_release_all)(p_tcb)) {
				dspreq = true;
			}
		}
		make_dormant(p_tcb);
		if (p_tcb->actque) {
			p_tcb->actque = false;
			if (make_active(p_tcb)) {
				dspreq = true;
			}
		}
		if (dspreq) {
			dispatch();
		}
		ercd = E_OK;
	}
	t_unlock_cpu();

  error_exit:
	LOG_TER_TSK_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_ter_tsk */

/*
 *  タスクのベース優先度の変更
 */
#ifdef TOPPERS_chg_pri

ER
chg_pri(ID tskid, PRI tskpri)
{
	TCB		*p_tcb;
	uint_t	newbpri;
	ER		ercd;

	LOG_CHG_PRI_ENTER(tskid, tskpri);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	CHECK_TPRI_INI(tskpri);
	p_tcb = get_tcb_self(tskid);
	CHECK_ACPTN(p_tcb->p_tinib->acvct.acptn2);
	newbpri = (tskpri == TPRI_INI) ? p_tcb->p_tinib->ipriority
										: INT_PRIORITY(tskpri);
	if (rundom != TACP_KERNEL) {
		CHECK_ILUSE(newbpri >= p_runtsk->p_tinib->p_dominib->minpriority);
	}

	t_lock_cpu();
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if ((!queue_empty(&(p_tcb->mutex_queue))
										|| TSTAT_WAIT_MTX(p_tcb->tstat))
						&& !((*mtxhook_check_ceilpri)(p_tcb, newbpri))) {
		ercd = E_ILUSE;
	}
	else {
		p_tcb->bpriority = newbpri;
		if (queue_empty(&(p_tcb->mutex_queue))
								|| !((*mtxhook_scan_ceilmtx)(p_tcb))) {
			if (change_priority(p_tcb, newbpri, false)) {
				dispatch();
			}
		}
		ercd = E_OK;
	}
	t_unlock_cpu();

  error_exit:
	LOG_CHG_PRI_LEAVE(ercd);
	return(ercd);
}

#endif /* TOPPERS_chg_pri */

/*
 *  タスク優先度の参照
 */
#ifdef TOPPERS_get_pri

ER
get_pri(ID tskid, PRI *p_tskpri)
{
	TCB		*p_tcb;
	ER		ercd;

	LOG_GET_PRI_ENTER(tskid, p_tskpri);
	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	CHECK_MACV_WRITE(p_tskpri, PRI);
	p_tcb = get_tcb_self(tskid);
	CHECK_ACPTN(p_tcb->p_tinib->acvct.acptn4);

	t_lock_cpu();
	if (TSTAT_DORMANT(p_tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
		*p_tskpri = EXT_TSKPRI(p_tcb->priority);
		ercd = E_OK;
	}
	t_unlock_cpu();

  error_exit:
	LOG_GET_PRI_LEAVE(ercd, *p_tskpri);
	return(ercd);
}

#endif /* TOPPERS_get_pri */

/*
 *  自タスクの拡張情報の参照
 */
#ifdef TOPPERS_get_inf

ER
get_inf(intptr_t *p_exinf)
{
	ER		ercd;

	LOG_GET_INF_ENTER(p_exinf);
	CHECK_TSKCTX_UNL();
	CHECK_MACV_WRITE(p_exinf, intptr_t);

	t_lock_cpu();
	*p_exinf = p_runtsk->p_tinib->exinf;
	ercd = E_OK;
	t_unlock_cpu();

  error_exit:
	LOG_GET_INF_LEAVE(ercd, *p_exinf);
	return(ercd);
}

#endif /* TOPPERS_get_inf */
