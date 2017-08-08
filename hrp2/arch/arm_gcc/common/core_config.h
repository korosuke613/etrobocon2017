/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2006-2012 by Embedded and Real-Time Systems Laboratory
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
 *  $Id: core_config.h 876 2013-02-18 14:24:58Z ertl-hiro $
 */


/*
 *      コア依存モジュール（ARM用）
 *
 *  このインクルードファイルは，target_config.h（または，そこからインク
 *  ルードされるファイル）のみからインクルードされる．他のファイルから
 *  直接インクルードしてはならない．
 */

#ifndef TOPPERS_CORE_CONFIG_H
#define TOPPERS_CORE_CONFIG_H

/*
 *  ARM依存の定義
 */
#include "arm.h"

/*
 *  ターゲット依存のメモリオブジェクト属性（エラーチェック用）
 */
#define TARGET_MEMATR		(TA_SORDER|TA_WTHROUGH|TA_NONSHARED)

/*
 *  エラーチェック方法の指定
 */
#define CHECK_STKSZ_ALIGN	8		/* スタックサイズのアライン単位 */
#define CHECK_USTKSZ_ALIGN	4096	/* ユーザスタックサイズのアライン単位 */
#ifndef  __thumb__
#define CHECK_FUNC_ALIGN	4		/* 関数のアライン単位 */
#endif /* __thumb__ */
#define CHECK_FUNC_NONNULL			/* 関数の非NULLチェック */
#define CHECK_STACK_ALIGN	4		/* スタック領域のアライン単位 */
#define CHECK_STACK_NONNULL			/* スタック領域の非NULLチェック */
#define CHECK_USTACK_ALIGN	4096	/* ユーザスタック領域のアライン単位 */
#define CHECK_USTACK_NONNULL		/* ユーザスタック領域の非NULLチェック */
#define CHECK_MPF_ALIGN		4		/* 固定長メモリプール領域のアライン単位 */
#define CHECK_MPF_NONNULL			/* 固定長メモリプール領域の非NULLチェック */
#define CHECK_MB_ALIGN		4		/* 管理領域のアライン単位 */

/*
 *  スタック領域のサイズと先頭番地は汎用的な方法で持つ
 */
/* #define USE_TSKINICTXB */

/*
 *  レッドゾーン方式を使用する
 */
#define USE_REDZONE
#define TARGET_DUMMY_STKSZ		ARM_PAGE_SIZE

/*
 *  CPUロックとするCPSRのパターン
 */
#ifndef CPSR_CPULOCK
#define CPSR_CPULOCK     (CPSR_IRQ_BIT)
#endif  /* CPSR_CPULOCK */

/*
 *  割込みロックとするCPSRのパターン
 */
#define CPSR_INTLOCK     (CPSR_FIQ_BIT|CPSR_IRQ_BIT)

/*
 *  CPSRに常にセットするパターン
 */
#ifndef CPSR_ALWAYS_SET
#define CPSR_ALWAYS_SET  0x00
#endif  /* CPSR_ALWAYS_SET */

/*
 *  例外の番号
 */
#define EXCH_NO_RESET     0
#define EXCH_NO_UNDEF     1
#define EXCH_NO_SVC       2
#define EXCH_NO_PABORT    3
#define EXCH_NO_DABORT    4
#define EXCH_NO_IRQ       5
#define EXCH_NO_FIQ       6
#define EXCH_NO_EMU_TEXRTN    7		/* タスク例外実行開始時スタック不正 */
#define EXCH_NO_EMU_RET_TEX   8		/* タスク例外リターン時スタック不正 */

/*
 *  例外の個数
 */  
#define TNUM_EXCH          9

#ifndef DEFAULT_SSTKSZ
#define DEFAULT_SSTKSZ		4096	/* システムスタックのサイズ */
#endif  /* DEFAULT_SSTKSZ */

/*
 *  SWI 割込み番号の定義
 */
#define	SERVICE_CALL_NUM	1
#define	RET_TEX_NUM			2

/*
 *  タスク例外で使用するユーザスタックサイズ
 */
#define TEX_USP_USE_BYTE	36

#ifndef TOPPERS_MACRO_ONLY

/* 
 *  保護ドメイン初期化コンテキストブロックを使う
 */
#define USE_DOMINICTXB

/*
 *  保護ドメイン初期化コンテキストブロックの定義
 */
typedef	struct domain_initialization_context_block {
	ID				domid;				/* ドメインID（ASIDとして使用）*/
	const uint32_t	*p_section_table;	/* セクションテーブルのアドレス */
} DOMINICTXB;

/*
 *  非タスクコンテキスト用のスタック初期値
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((char *)(istk) + (istksz)))

/*
 *  プロセッサの特殊命令のインライン関数定義
 *  ARMCCの共有のため，コンパイラの引数に指定された順で検索するようにする．
 */
#include <core_insn.h>

/*
 *  タスクコンテキストブロックの定義
 */
typedef struct task_context_block {
	void	*sp;	/* スタックポインタ */
	FP		pc;		/* プログラムカウンタ */
	bool_t	priv;	/* タスクが特権モードを実行している場合にtrue */
} TSKCTXB;

/*
 *  アドレス変換テーブルの領域の定義
 */
extern const uint32_t section_table[][ARM_SECTION_TABLE_ENTRY];
extern const uint32_t page_table[][ARM_PAGE_TABLE_ENTRY];

/*
 *  TOPPERS標準割込み処理モデルの実現
 *
 *  IRQをカーネル管理内，FIQをカーネル管理外の割込みとして扱う．
 * 
 *  ARM依存部では，TOPPERS標準割込み処理モデルのうち，CPUロック状態
 *  のみを取り扱う．割込み優先度マスク，割込み要求禁止フラグに関して
 *  は，各ターゲット依存部で取り扱う
 */

/*
 *  コンテキスト参照のための変数
 */
extern uint32_t excpt_nest_count; /* 例外（割込み/CPU例外）のネスト回数のカウント */

/*
 *  コンテキストの参照
 *
 *  ARMでは，タスクコンテキストと非タスクコンテキストの両方をスーパー
 *  バイザーモードで動作させる．そのため，CPSRの内容では判別できない．
 *  そのため，例外（割込み/CPU例外）のネスト回数をカウントする変数
 *  （excpt_nest_count）を用意し，例外の入り口でインクリメントすること
 *  で，コンテキストを判定する．
 */
Inline bool_t
sense_context(void)
{
	return(excpt_nest_count > 0U);
}

/*
 *  CPUロック状態への移行
 */
Inline void
x_lock_cpu(void)
{
	set_sr(current_sr() | CPSR_CPULOCK | CPSR_ALWAYS_SET);
	/* クリティカルセクションの前後でメモリが書き換わる可能性がある */
	ARM_MEMORY_CHANGED;
}

#define t_lock_cpu()   x_lock_cpu()
#define i_lock_cpu()   x_lock_cpu()

/*
 *  CPUロック状態の解除
 */
Inline void
x_unlock_cpu(void)
{
	/* クリティカルセクションの前後でメモリが書き換わる可能性がある */
	ARM_MEMORY_CHANGED;
	set_sr((current_sr() & (~CPSR_CPULOCK)) | CPSR_ALWAYS_SET);
}

#define t_unlock_cpu() x_unlock_cpu()
#define i_unlock_cpu() x_unlock_cpu()

/*
 *  CPUロック状態の参照
 */
Inline bool_t
x_sense_lock(void)
{
	return((current_sr() & CPSR_CPULOCK) == CPSR_CPULOCK);
}

#define t_sense_lock() x_sense_lock()
#define i_sense_lock() x_sense_lock()

/*
 *  特権モードを実行しているか否かの判別
 *
 *  これらの関数を，インライン関数ではなくマクロ定義としているのは，こ
 *  の時点ではTCBが定義されていないためである．
 */
#define t_sense_priv(p_tcb)    ((p_tcb)->tskctxb.priv)
#define i_sense_priv(p_tcb)    ((p_tcb)->tskctxb.priv)
#define i_sense_priv_runtsk()  (p_runtsk->tskctxb.priv)

/*
 *  ユーザスタックの残りサイズのチェック
 *  ※p_runtskを参照しているためマクロにする必要がある。
 */
#define i_check_tex_runtsk()   \
		((current_usp()-(uint32_t)p_runtsk->p_tinib->ustk) < TEX_USP_USE_BYTE \
		? true : false)

/*
 *  タスクディスパッチャ
 */

/*
 *  最高優先順位タスクへのディスパッチ（core_support.S）
 *
 *  dispatchは，タスクコンテキストから呼び出されたサービスコール処理か
 *  ら呼び出すべきもので，タスクコンテキスト・CPUロック状態・ディスパッ
 *  チ許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さな
 *  ければならない．
 */
extern void dispatch(void);

/*
 *  ディスパッチャの動作開始（core_support.S）
 *
 *  start_dispatchは，カーネル起動時に呼び出すべきもので，すべての割込
 *  みを禁止した状態（割込みロック状態と同等の状態）で呼び出さなければ
 *  ならない．
 */
extern void start_dispatch(void) NoReturn;

/*
 *  現在のコンテキストを捨ててディスパッチ（core_support.S）
 *
 *  exit_and_dispatchは，ext_tskから呼び出すべきもので，タスクコンテキ
 *  スト・CPUロック状態・ディスパッチ許可状態・（モデル上の）割込み優先
 *  度マスク全解除状態で呼び出さなければならない．
 */
extern void exit_and_dispatch(void) NoReturn;

/*
 *  カーネルの終了処理の呼出し（core_support.S）
 *
 *  call_exit_kernelは，カーネルの終了時に呼び出すべきもので，非タスク
 *  コンテキストに切り換えて，カーネルの終了処理（exit_kernel）を呼び出
 *  す．
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *  タスクの終了
 *
 *  ユーザタスクがメインルーチンからリターンした場合に呼ばれるルーチン．
 *  共有領域に配置する． 
 */
extern void call_ext_tsk(void) NoReturn  __attribute__((section(".text_shared")));

/*
 *  タスクコンテキストの初期化
 *
 *  タスクが休止状態から実行できる状態に移行する時に呼ばれる．この時点
 *  でスタック領域を使ってはならない．
 *
 *  activate_contextを，インライン関数ではなくマクロ定義としているのは，
 *  この時点ではTCBが定義されていないためである．
 */
extern void start_stask_r(void);
extern void start_utask_r(void);

#define activate_context(p_tcb) \
{																		\
	(p_tcb)->tskctxb.sp = (void *)((char *)((p_tcb)->p_tinib->sstk)		\
										+ (p_tcb)->p_tinib->sstksz);	\
	if ((p_tcb)->p_tinib->p_dominib->domptn == TACP_KERNEL) {			\
		(p_tcb)->tskctxb.pc = (FP) start_stask_r;						\
	    (p_tcb)->tskctxb.priv = true;									\
	}																	\
	else {																\
		(p_tcb)->tskctxb.pc = (FP) start_utask_r;						\
	    (p_tcb)->tskctxb.priv = false;									\
	}																	\
}

/*
 *  calltexは使用しない
 */
#define OMIT_CALLTEX

/*
 * ターゲット非依存部に含まれる標準の例外管理機能の初期化処理を用いない
 */
#define OMIT_INITIALIZE_EXCEPTION

/*
 * CPU例外ハンドラの初期化
 */
Inline void
initialize_exception(void)
{
}

/*
 *  CPU例外の発生した時のシステム状態の参照
 */

/*
 *  CPU例外の発生した時のコンテキストの参照
 *
 *  CPU例外の発生した時のコンテキストが，タスクコンテキストの時にfalse，
 *  そうでない時にtrueを返す．
 */
Inline bool_t
exc_sense_context(void *p_excinf)
{
	return(((exc_frame_t *)(p_excinf))->nest_count != 0U);
}

/*
 *  CPU例外の発生した時の(モデル上の)割込み優先度マスクの参照
 */
Inline PRI
exc_get_ipm(void *p_excinf)
{
	return((PRI)(((exc_frame_t *)(p_excinf))->ipm));
}

/*
 *  CPU例外の発生した時のCPSRの取得
 */
Inline uint32_t
exc_get_sr(void *p_excinf){
	return(((exc_frame_t *)(p_excinf))->cpsr);
}

/*
 * CPUロック状態か
 */
Inline bool_t
exc_sense_lock(void *p_excinf){
	return((exc_get_sr(p_excinf) & CPSR_CPULOCK) == CPSR_CPULOCK);
}

/*
 * 割込みロック状態か
 */
Inline bool_t
exc_sense_int_lock(void *p_excinf){
	return((exc_get_sr(p_excinf) & CPSR_INTLOCK) == CPSR_INTLOCK);
}

/*
 *  CPU例外の発生した時のコンテキストと割込みのマスク状態の参照
 *
 *  CPU例外の発生した時のシステム状態が，カーネル実行中でなく，タスクコ
 *  ンテキストであり，全割込みロック状態でなく，CPUロック状態でなく，割
 *  込み優先度マスク全解除状態である時にtrue，そうでない時にfalseを返す
 *  （CPU例外がカーネル管理外の割込み処理中で発生した場合にもfalseを返
 *  す）．
 *
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
	return(!exc_sense_context(p_excinf)
		   && (exc_get_ipm(p_excinf) == 0U)
		   && !exc_sense_lock(p_excinf)
		   && !exc_sense_int_lock(p_excinf));
}

/*
 *  プロセッサ依存の初期化
 */
extern void core_initialize(void);

/*
 *  プロセッサ依存の終了時処理
 */
extern void core_terminate(void);

/*
 *  ベクターテーブルの命令から参照されるジャンプ先アドレス
 * （start.S）
 */
extern void *vector_ref_tbl;

/*
 *  CPU例外の発生状況のログ出力
 */
#ifdef SUPPORT_XLOG_SYS
extern void xlog_sys(void *p_excinf);
#endif /* SUPPORT_XLOG_SYS */

/*
 *  例外ベクタから直接実行するハンドラを登録
 */ 
extern void x_install_exc(EXCNO excno, FP exchdr);

/*
 *  例外ハンドラ
 */

/*
 *  未定義命令 例外ハンドラ（core_support.S）
 */
extern void undef_handler(void);

/*
 *  SVC 例外ハンドラ（core_support.S）
 */
extern void svc_handler(void);

/*
 *  プリフェッチアボード 例外ハンドラ（core_support.S）
 */
extern void prefetch_handler(void);

/*
 *  データアボード 例外ハンドラ（core_support.S）
 */
extern void data_abort_handler(void);

/*
 *  FIQ 例外ハンドラ（core_support.S）
 */
extern void fiq_handler(void);

/*
 *  未定義の例外が入った場合の処理
 */
extern void default_exc_handler(void *p_excinf);

/*
 *  プリフェッチアボード例外ハンドラ本体
 */
extern void prefetch_handler_body(void *p_excinf);

/*
 *  データアボード例外ハンドラ本体
 */
extern void data_abort_handler_body(void *p_excinf);

/*
 *  タスク例外実行開始時スタック不正ハンドラ
 */
extern void emulate_texrtn_handler(void *p_excinf);

/*
 *  タスク例外リターン時スタック不正ハンドラ
 */
extern void emulate_ret_tex_handler(void *p_excinf);

#if 0
/*
 *  メモリ書き込みアクセス権限判定
 */
extern bool_t probe_mem_write(void *base, SIZE size);

/*
 *  メモリ読み込みアクセス権限判定
 */
extern bool_t probe_mem_read(void *base, SIZE size);
#endif

/*
 *  ユーザスタックのチェック
 */
extern bool_t check_stack(void *base, SIZE size);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_CORE_CONFIG_H */
