/*
 *  TOPPERS/HRP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      High Reliable system Profile Kernel
 * 
 *  Copyright (C) 2005-2012 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: bit_kernel.c 833 2012-12-26 13:55:48Z ertl-hiro $
 */

/*
 *		カーネルの整合性検査
 */

#include "kernel/kernel_impl.h"
#include "kernel/task.h"
#include "kernel/wait.h"
#include "kernel/semaphore.h"
#include "kernel/eventflag.h"
#include "kernel/dataqueue.h"
#include "kernel/pridataq.h"
#include "kernel/mutex.h"
#include "kernel/mempfix.h"
#include "kernel/time_event.h"

/*
 *   エラーコードの定義
 */
#define E_SYS_LINENO	ERCD(E_SYS, -(__LINE__))

/*
 *  管理ブロックのアドレスの正当性のチェック
 */
#define VALID_TCB(p_tcb) \
		((((char *) p_tcb) - ((char *) tcb_table)) % sizeof(TCB) == 0 \
			&& TMIN_TSKID <= TSKID(p_tcb) && TSKID(p_tcb) <= tmax_tskid)

#define VALID_SEMCB(p_semcb) \
		((((char *) p_semcb) - ((char *) semcb_table)) % sizeof(SEMCB) == 0 \
			&& TMIN_SEMID <= SEMID(p_semcb) && SEMID(p_semcb) <= tmax_semid)
				
#define VALID_FLGCB(p_flgcb) \
		((((char *) p_flgcb) - ((char *) flgcb_table)) % sizeof(FLGCB) == 0 \
			&& TMIN_FLGID <= FLGID(p_flgcb) && FLGID(p_flgcb) <= tmax_flgid)

#define VALID_DTQCB(p_dtqcb) \
		((((char *) p_dtqcb) - ((char *) dtqcb_table)) % sizeof(DTQCB) == 0 \
			&& TMIN_DTQID <= DTQID(p_dtqcb) && DTQID(p_dtqcb) <= tmax_dtqid)

#define VALID_PDQCB(p_pdqcb) \
		((((char *) p_pdqcb) - ((char *) pdqcb_table)) % sizeof(PDQCB) == 0 \
			&& TMIN_PDQID <= PDQID(p_pdqcb) && PDQID(p_pdqcb) <= tmax_pdqid)

#define VALID_MTXCB(p_mtxcb) \
		((((char *) p_mtxcb) - ((char *) mtxcb_table)) % sizeof(MTXCB) == 0 \
			&& TMIN_MTXID <= MTXID(p_mtxcb) && MTXID(p_mtxcb) <= tmax_mtxid)

#define VALID_MPFCB(p_mpfcb) \
		((((char *) p_mpfcb) - ((char *) mpfcb_table)) % sizeof(MPFCB) == 0 \
			&& TMIN_MPFID <= MPFID(p_mpfcb) && MPFID(p_mpfcb) <= tmax_mpfid)

/*
 *  キューのチェックのための関数
 *
 *  p_queueにp_entryが含まれているかを調べる．含まれていればtrue，含ま
 *  れていない場合にはfalseを返す．ダブルリンクの不整合の場合にも，
 *  falseを返す．
 */
static bool_t
in_queue(QUEUE *p_queue, QUEUE *p_entry)
{
	QUEUE	*p_current, *p_next;

	p_current = p_queue->p_next;
	if (p_current->p_prev != p_queue) {
		return(false);					/* ダブルリンクの不整合 */
	}
	while (p_current != p_queue) {
		if (p_current == p_entry) {
			return(true);				/* p_entryが含まれていた */
		}

		/*
		 *  キューの次の要素に進む
		 */
		p_next = p_current->p_next;
		if (p_next->p_prev != p_current) {
			return(false);				 /* ダブルリンクの不整合 */
		}
		p_current = p_next;
	}
	return(false);
}

/*
 *  システムスタック上を指しているかの検査
 */
static bool_t
on_stack(void *addr, const TINIB *p_tinib)
{
#ifdef USE_TSKINICTXB
	/*
	 *  この関数の実装はターゲット依存になる．
	 */
	return(true);
#else /* USE_TSKINICTXB */
	if (p_tinib->sstk <= addr
			&& addr < (void *)((char *)(p_tinib->sstk) + p_tinib->sstksz)) {
		return(true);
	}
	return(false);
#endif /* USE_TSKINICTXB */
}

/*
 *  タスク毎の整合性検査
 */
static ER
bit_task(ID tskid)
{
	TCB			*p_tcb;
	const TINIB	*p_tinib;
	uint_t		tstat, tstat_wait, pri;
	TMEVTB		*p_tmevtb;
	SEMCB		*p_semcb;
	FLGCB		*p_flgcb;
	DTQCB		*p_dtqcb;
	PDQCB		*p_pdqcb;
	MTXCB		*p_mtxcb;
	MPFCB		*p_mpfcb;

	if (!(TMIN_TSKID <= (tskid) && (tskid) <= tmax_tskid)) {
		return(E_ID);
	}
	p_tcb = get_tcb(tskid);
	p_tinib = p_tcb->p_tinib;
	tstat = p_tcb->tstat;
	tstat_wait = (tstat & TS_WAIT_MASK);
	pri = p_tcb->priority;

	/*
	 *  初期化ブロックへのポインタの検査
	 */
	if (p_tinib != &(tinib_table[INDEX_TSK(tskid)])) {
		return(E_SYS_LINENO);
	}

	/*
	 *  tstatの検査
	 */
	switch (tstat & (TS_RUNNABLE | TS_WAITING | TS_SUSPENDED)) {
	case TS_DORMANT:
		if (tstat != TS_DORMANT) {
			return(E_SYS_LINENO);
		}
		break;
	case TS_RUNNABLE:
		if (tstat != TS_RUNNABLE) {
			return(E_SYS_LINENO);
		}
		break;
	case TS_WAITING:
	case (TS_WAITING | TS_SUSPENDED):
		if (!(TS_WAIT_DLY <= tstat_wait && tstat_wait <= TS_WAIT_MTX)
											|| tstat_wait == TS_WAIT_MBX) {
			return(E_SYS_LINENO);
		}
		if ((tstat & ~(TS_WAIT_MASK | TS_RUNNABLE | TS_WAITING | TS_SUSPENDED))
																	!= 0U) {
			return(E_SYS_LINENO);
		}
		break;
	case TS_SUSPENDED:
		if (tstat != TS_SUSPENDED) {
			return(E_SYS_LINENO);
		}
		break;
	default:
		return(E_SYS_LINENO);
	}

	/*
	 *  actqueの検査
	 */
	if (TSTAT_DORMANT(tstat) && p_tcb->actque) {
		return(E_SYS_LINENO);
	}

	/*
	 *  タスク優先度の検査
	 */
	if (pri >= TNUM_TPRI) {
		return(E_SYS_LINENO);
	}

	/*
	 *  texptnの検査
	 */
	if (p_tcb->p_tinib->texrtn == NULL && p_tcb->texptn != 0U) {
		return(E_SYS_LINENO);
	}

	/*
	 *  休止状態におけるチェック
	 */
	if (TSTAT_DORMANT(tstat)) {
		if (!(pri == p_tinib->ipriority)
					&& (p_tcb->wupque == false)
					&& (p_tcb->enatex == false)
					&& (p_tcb->texptn == 0U)) {
			return(E_SYS_LINENO);
		}
	}

	/*
	 *  実行できる状態におけるチェック
	 */
	if (TSTAT_RUNNABLE(tstat)) {
		if (!in_queue(&ready_queue[pri], &(p_tcb->task_queue))) {
			return(E_SYS_LINENO);
		}
	}

	/*
	 *  待ち状態におけるチェック
	 */
	if (TSTAT_WAITING(tstat)) {
		if (!on_stack(p_tcb->p_winfo, p_tinib)) {
			return(E_SYS_LINENO);
		}
		p_tmevtb = p_tcb->p_winfo->p_tmevtb;
		if (p_tmevtb != NULL) {
			if (!on_stack(p_tmevtb, p_tinib)) {
				return(E_SYS_LINENO);
			}
			/*
			 *  (*p_tmevtb)の検査（未完成）
			 */
		}

		switch (tstat & TS_WAIT_MASK) {
			case TS_WAIT_SLP:
				if (p_tcb->wupque == true) {
					return(E_SYS_LINENO);
				}
				break;

			case TS_WAIT_DLY:
				if (p_tmevtb == NULL) {
					return(E_SYS_LINENO);
				}
				break;

			case TS_WAIT_SEM:
				p_semcb = ((WINFO_SEM *)(p_tcb->p_winfo))->p_semcb;
				if (!VALID_SEMCB(p_semcb)) {
					return(E_SYS_LINENO);
				}
				if (!in_queue(&(p_semcb->wait_queue), &(p_tcb->task_queue))) {
					return(E_SYS_LINENO);
				}
				break;

			case TS_WAIT_FLG:
				p_flgcb = ((WINFO_FLG *)(p_tcb->p_winfo))->p_flgcb;
				if (!VALID_FLGCB(p_flgcb)) {
					return(E_SYS_LINENO);
				}
				if (!in_queue(&(p_flgcb->wait_queue), &(p_tcb->task_queue))) {
					return(E_SYS_LINENO);
				}
				break;

			case TS_WAIT_SDTQ:
				p_dtqcb = ((WINFO_DTQ *)(p_tcb->p_winfo))->p_dtqcb;
				if (!VALID_DTQCB(p_dtqcb)) {
					return(E_SYS_LINENO);
				}
				if (!in_queue(&(p_dtqcb->swait_queue), &(p_tcb->task_queue))) {
					return(E_SYS_LINENO);
				}
				break;

			case TS_WAIT_RDTQ:
				p_dtqcb = ((WINFO_DTQ *)(p_tcb->p_winfo))->p_dtqcb;
				if (!VALID_DTQCB(p_dtqcb)) {
					return(E_SYS_LINENO);
				}
				if (!in_queue(&(p_dtqcb->rwait_queue), &(p_tcb->task_queue))) {
					return(E_SYS_LINENO);
				}
				break;

			case TS_WAIT_SPDQ:
				p_pdqcb = ((WINFO_PDQ *)(p_tcb->p_winfo))->p_pdqcb;
				if (!VALID_PDQCB(p_pdqcb)) {
					return(E_SYS_LINENO);
				}
				if (!in_queue(&(p_pdqcb->swait_queue), &(p_tcb->task_queue))) {
					return(E_SYS_LINENO);
				}
				break;

			case TS_WAIT_RPDQ:
				p_pdqcb = ((WINFO_PDQ *)(p_tcb->p_winfo))->p_pdqcb;
				if (!VALID_PDQCB(p_pdqcb)) {
					return(E_SYS_LINENO);
				}
				if (!in_queue(&(p_pdqcb->rwait_queue), &(p_tcb->task_queue))) {
					return(E_SYS_LINENO);
				}
				break;

			case TS_WAIT_MTX:
				p_mtxcb = ((WINFO_MTX *)(p_tcb->p_winfo))->p_mtxcb;
				if (!VALID_MTXCB(p_mtxcb)) {
					return(E_SYS_LINENO);
				}
				if (!in_queue(&(p_mtxcb->wait_queue), &(p_tcb->task_queue))) {
					return(E_SYS_LINENO);
				}
				break;

			case TS_WAIT_MPF:
				p_mpfcb = ((WINFO_MPF *)(p_tcb->p_winfo))->p_mpfcb;
				if (!VALID_MPFCB(p_mpfcb)) {
					return(E_SYS_LINENO);
				}
				if (!in_queue(&(p_mpfcb->wait_queue), &(p_tcb->task_queue))) {
					return(E_SYS_LINENO);
				}
				break;
		}
	}

	/*
	 *  tskctxbの検査
	 */
	if (!TSTAT_DORMANT(tstat) && p_tcb != p_runtsk) {
		/*
		 *  ターゲット依存の検査
		 */
#if 0
		if (bit_tskctxb(&(p_tcb->tskctxb))) {
			return(E_SYS_LINENO);
		}
#endif
	}
	return(E_OK);
}

/*
 *  セマフォ毎の整合性検査
 */
#define INDEX_SEM(semid)	((uint_t)((semid) - TMIN_SEMID))
#define get_semcb(semid)	(&(semcb_table[INDEX_SEM(semid)]))

static ER
bit_semaphore(ID semid)
{
	SEMCB			*p_semcb;
	const SEMINIB	*p_seminib;
	uint_t			semcnt;
	QUEUE			*p_queue;
	TCB				*p_tcb;

	if (!(TMIN_SEMID <= (semid) && (semid) <= tmax_semid)) {
		return(E_ID);
	}
	p_semcb = get_semcb(semid);
	p_seminib = p_semcb->p_seminib;
	semcnt = p_semcb->semcnt;

	/*
	 *  初期化ブロックへのポインタの検査
	 */
	if (p_seminib != &(seminib_table[INDEX_SEM(semid)])) {
		return(E_SYS_LINENO);
	}

	/*
	 *  semcntの検査
	 */
	if (semcnt > p_seminib->maxsem) {
		return(E_SYS_LINENO);
	}

	/*
	 *  wait_queueの検査
	 */
	if (semcnt == 0) {
		p_queue = p_semcb->wait_queue.p_next;
		while (p_queue != &(p_semcb->wait_queue)) {
			p_tcb = (TCB *) p_queue;
			p_queue = p_queue->p_next;
			if (!VALID_TCB(p_tcb)) {
				return(E_SYS_LINENO);
			}
			if (p_tcb->tstat != (TS_WAITING | TS_WAIT_SEM)) {
				return(E_SYS_LINENO);
			}
			if (p_semcb != ((WINFO_SEM *)(p_tcb->p_winfo))->p_semcb) {
				return(E_SYS_LINENO);
			}
		}
	}
	else {
		if (!queue_empty(&(p_semcb->wait_queue))) {
			return(E_SYS_LINENO);
		}
	}
	return(E_OK);
}

/*
 *  整合性検査ルーチン本体
 */
ER
bit_kernel(void)
{
	ID		tskid;
	ID		semid;
	ER		ercd;

	/*
	 *  タスク毎の検査
	 */
	for (tskid = TMIN_TSKID; tskid <= tmax_tskid; tskid++) {
		ercd = bit_task(tskid);
		if (ercd != E_OK) {
			return(ercd);
		}
	}

	/*
	 *  セマフォ毎の検査
	 */
	for (semid = TMIN_SEMID; semid <= tmax_semid; semid++) {
		ercd = bit_semaphore(semid);
		if (ercd != E_OK) {
			return(ercd);
		}
	}

	return(E_OK);
}
