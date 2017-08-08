#include "cmsis_os.h"
#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>

#include <cstdlib>
#include <cstring>
#include <type_traits>

#define DEBUG_RT_CMSIS

#if defined(DEBUG_RT_CMSIS)

#define CHECK_SVC(expr) check_svc(__FILE__, __LINE__, #expr, (expr))
static inline
ER check_svc(const char *file, int_t line, const char *expr, ER ercd) {
    if (ercd < 0) {
        t_perror(LOG_ERROR, file, line, expr, ercd);
    }
    return ercd;
}
#define acre_tsk(...) CHECK_SVC(acre_tsk(__VA_ARGS__))
#define get_tid(...)  CHECK_SVC(get_tid(__VA_ARGS__))
#define ter_tsk(...)  CHECK_SVC(ter_tsk(__VA_ARGS__))
#define dly_tsk(...)  CHECK_SVC(dly_tsk(__VA_ARGS__))
#define acre_dtq(...) CHECK_SVC(acre_dtq(__VA_ARGS__))
#define tsnd_dtq(...) CHECK_SVC(tsnd_dtq(__VA_ARGS__))
//#define trcv_dtq(...) CHECK_SVC(trcv_dtq(__VA_ARGS__))
#define acre_mpf(...) CHECK_SVC(acre_mpf(__VA_ARGS__))
#define tget_mpf(...) CHECK_SVC(tget_mpf(__VA_ARGS__))
#define rel_mpf(...)  CHECK_SVC(rel_mpf(__VA_ARGS__))
#define acre_sem(...) CHECK_SVC(acre_sem(__VA_ARGS__))
#define twai_sem(...) CHECK_SVC(twai_sem(__VA_ARGS__))
#define sig_sem(...)  CHECK_SVC(sig_sem(__VA_ARGS__))
#define del_sem(...)  CHECK_SVC(del_sem(__VA_ARGS__))
#define acre_mtx(...) CHECK_SVC(acre_mtx(__VA_ARGS__))
#define tloc_mtx(...) CHECK_SVC(tloc_mtx(__VA_ARGS__))
#define unl_mtx(...)  CHECK_SVC(unl_mtx(__VA_ARGS__))
#define del_mtx(...)  CHECK_SVC(del_mtx(__VA_ARGS__))

#endif

// Cast a CMSIS type to TOPPERS type
#define C2T_ID(id) ((ID)(id)) 
#define C2T_PRI(pri) (TMAX_TPRI-(pri)) // TODO: how to decide this mapping?
//#define C2T_PRI(pri) (TMIN_TPRI-(pri)+3) // TODO: how to decide this mapping?
//#define C2T_PRI(pri) (TMIN_TPRI-(pri)+6) // TODO: how to decide this mapping?

#if TKERNEL_PRVER == UINT_C(0x2021)
#define C2T_TMO(ms) (((ms) == osWaitForever) ? TMO_FEVR : (ms)) // millisec -> TMO
#define C2T_RELTIM(ms) ((RELTIM)(ms)) // millisec -> RELTIM
#else
#error "Only HRP2 kernel is supported."
#define C2T_TMO(ms) (((ms) == osWaitForever) ? TMO_FEVR : (ms * 1000UL)) // millisec -> TMO (in us)
#define C2T_RELTIM(ms) ((RELTIM)((ms) * 1000UL)) // millisec -> RELTIM (in us)
// handle TMO_FEVR
#endif

extern "C" {

// ==== Thread Management ====

/// Create a thread and add it to Active Threads and set it to state READY
osThreadId osThreadCreate (const osThreadDef_t *thread_def, void *argument) {
    assert(thread_def->instances <= 1); // TODO: is thread_def->instances == 0 OK?
    assert(thread_def->tpriority >= osPriorityIdle && thread_def->tpriority <= osPriorityRealtime);

    T_CTSK ctsk;
    static_assert(sizeof(ctsk.exinf) == sizeof(argument), "thread argument must have same size with exinf in TSK");
    static_assert(std::is_same<decltype(thread_def->pthread(NULL)), decltype(ctsk.task(0))>::value, "thread return value must be void");
    ctsk.tskatr  = TA_ACT; 
    ctsk.tskatr |= TA_DOM(TDOM_KERNEL); // FIXME: only system tasks are supported
    ctsk.exinf   = (intptr_t)argument;
    ctsk.task    = (TASK)thread_def->pthread;
    ctsk.itskpri = C2T_PRI(thread_def->tpriority);
    ctsk.stksz   = thread_def->stacksize ? thread_def->stacksize : DEFAULT_STACK_SIZE;
    ctsk.stk     = (STK_T*)thread_def->stack_pointer;
    ctsk.sstksz  = 0; // 4096/*DEFAULT_SSTKSZ*/; // FIXME: we are system tasks, we do not need sstk (hard coded, should we use DEFAULT_SSTKSZ?, or use a extern symbol to get this value
    ctsk.sstk    = NULL; // TODO: should we pass NULL to kernel?

    ER_ID ercd = acre_tsk(&ctsk);
    if (ercd <= 0) {
        return NULL;
    }
    return (osThreadId)ercd;
}

/// Terminate execution of a thread and remove it from ActiveThreads
osStatus osThreadTerminate (osThreadId thread_id) {
    ER ercd;

    ID cur_tid;
    ercd = get_tid(&cur_tid);
    if (ercd == E_CTX) return osErrorISR;
    if (cur_tid == C2T_ID(thread_id)) ext_tsk();

    ercd = ter_tsk(C2T_ID(thread_id));
    return osOK;
}

// ==== Generic Wait Functions ====

/// Wait for Timeout (Time Delay)
osStatus osDelay (uint32_t millisec) {
    static_assert(sizeof(millisec) <= sizeof(RELTIM), "millisec must be in range of RELTIM");
    assert(millisec >= 1);

    ER ercd = dly_tsk(C2T_RELTIM(millisec));
    if (ercd == E_CTX) return osErrorISR; // Not allowed in ISR
    return osOK;
}

// ==== Mutex Management ====

/// Create and Initialize a Mutex object
osMutexId osMutexCreate (const osMutexDef_t *mutex_def) {
    T_CMTX cmtx;
    cmtx.mtxatr  = TA_NULL;
    cmtx.mtxatr |= TA_DOM(TDOM_KERNEL); // FIXME: belong to kernel domain by default

    ER_ID ercd = acre_mtx(&cmtx);
    // FIXME: handle exceptions
    return (osMutexId)ercd;
}

/// Wait until a Mutex becomes available
osStatus osMutexWait (osMutexId mutex_id, uint32_t millisec) {
    assert(millisec < (1UL << (sizeof(TMO) * 8 - 1)) || millisec == osWaitForever); // FIXME: TMO is not unsigned!, TMO in Gen3 kernel is microseconds

    ER ercd = tloc_mtx(C2T_ID(mutex_id), C2T_TMO(millisec));
    // FIXME: handle exceptions
    if (ercd == E_TMOUT) return osErrorTimeoutResource;
    return osOK;
}

/// Release a Mutex that was obtained with osMutexWait
osStatus osMutexRelease (osMutexId mutex_id) {
    ER ercd = unl_mtx(C2T_ID(mutex_id));
    // FIXME: handle exceptions
    return osOK;
}

/// Delete a Mutex that was created by osMutexCreate
osStatus osMutexDelete (osMutexId mutex_id) {
    ER ercd = del_mtx(C2T_ID(mutex_id));
    // FIXME: handle exceptions
    return osOK;
}

// ==== Semaphore Management ====

/// Create and Initialize a Semaphore object
osSemaphoreId osSemaphoreCreate (const osSemaphoreDef_t *semaphore_def, int32_t count) {
    static_assert(osFeature_Semaphore <= TMAX_MAXSEM, "maximum count of semaphore is out of range");
    assert(count <= osFeature_Semaphore);

    T_CSEM csem;
    csem.sematr  = TA_NULL;
    csem.sematr |= TA_DOM(TDOM_KERNEL); // FIXME: belong to kernel domain by default
    csem.isemcnt = count;               // NOTE: count in mbed seems to be init value other than a max limit
    csem.maxsem  = osFeature_Semaphore;

    ER_ID ercd = acre_sem(&csem);
    // FIXME: handle exceptions
    return (osSemaphoreId)ercd;
}

/// Wait until a Semaphore becomes available
int32_t osSemaphoreWait (osSemaphoreId semaphore_id, uint32_t millisec) {
    assert(millisec < (1UL << (sizeof(TMO) * 8 - 1)) || millisec == osWaitForever); // FIXME: TMO is not unsigned!, TMO in Gen3 kernel is microseconds

    ER ercd = twai_sem(C2T_ID(semaphore_id), C2T_TMO(millisec));
    // FIXME: only 0 or osFeature_Semaphore will be returned
    if (ercd == E_TMOUT) return 0;
    return osFeature_Semaphore;
}

/// Release a Semaphore
osStatus osSemaphoreRelease (osSemaphoreId semaphore_id) {
    ER ercd = sig_sem(C2T_ID(semaphore_id));
    // FIXME: handle exceptions
    return osOK;
}

/// Delete a Semaphore that was created by osSemaphoreCreate
osStatus osSemaphoreDelete (osSemaphoreId semaphore_id) {
    ER ercd = del_sem(C2T_ID(semaphore_id));
    // FIXME: handle exceptions
    return osOK;
}

// ==== Message Queue Management Functions ====

osMessageQId osMessageCreate (const osMessageQDef_t *queue_def, osThreadId thread_id) {
    assert(thread_id == NULL);   

    T_CDTQ cdtq;
    cdtq.dtqatr = TA_NULL;
    cdtq.dtqatr|= TA_DOM(TDOM_KERNEL); // FIXME: belong to kernel domain by default
    cdtq.dtqcnt = queue_def->queue_sz;
    cdtq.dtqmb  = queue_def->pool;
    assert(cdtq.dtqmb != NULL);

    ER_ID ercd = acre_dtq(&cdtq);
    if (ercd <= 0) {
        syslog(LOG_ERROR, "%s() called, cnt:%d, mb:0x%p", __FUNCTION__, cdtq.dtqcnt, cdtq.dtqmb);
        while(1)tslp_tsk(10);
        return NULL;
    }
    return (osMessageQId)ercd;
}

osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec) {
    static_assert(sizeof(info) == sizeof(intptr_t), "message must have same size with data in DTQ");
    assert(millisec < (1UL << (sizeof(TMO) * 8 - 1)) || millisec == osWaitForever); // FIXME: TMO is not unsigned!, TMO in Gen3 kernel is microseconds

    ER ercd = tsnd_dtq(C2T_ID(queue_id), info, C2T_TMO(millisec)); // FIXME: interrupt context is not supported yet

    if (ercd == E_TMOUT) return osErrorTimeoutResource;
    return osOK;
}

os_InRegs osEvent osMessageGet (osMessageQId queue_id, uint32_t millisec) {
    osEvent ret;
    static_assert(sizeof(ret.value.v) == sizeof(intptr_t), "message must have same size with data in DTQ");
    assert(millisec < (1UL << (sizeof(TMO) * 8 - 1)) || millisec == osWaitForever); // FIXME: TMO is not unsigned!, TMO in Gen3 kernel is microseconds

    ER ercd = trcv_dtq(C2T_ID(queue_id), (intptr_t*)(&(ret.value.v)), C2T_TMO(millisec)); // FIXME: interrupt context is not supported yet

    if (ercd == E_TMOUT) {
        ret.status = millisec ? osEventTimeout : osOK;
    } else {
        ret.status = osEventMessage;
    }

    return ret;
}

// ==== Mail Queue Management Functions ====

struct os_mailQ_cb {
    osMessageQId qid; // message queue id
    ID           mpf; // fixed-size memory pool
    uint32_t     bsz; // mail block size
};

/// Create and Initialize mail queue
osMailQId osMailCreate (const osMailQDef_t *queue_def, osThreadId thread_id) {
    assert(thread_id == NULL);

    osMessageQDef_t msg_queue_def;
    msg_queue_def.queue_sz = queue_def->queue_sz;
    msg_queue_def.pool     = NULL;
    
    auto msg_queue_id = osMessageCreate(&msg_queue_def, thread_id);
    if (msg_queue_id == NULL) {
        return NULL;
    }

    T_CMPF cmpf;
    cmpf.mpfatr = TA_NULL;
    cmpf.mpfatr|= TA_DOM(TDOM_KERNEL); // FIXME: belong to kernel domain by default
    cmpf.blkcnt = queue_def->queue_sz;
    cmpf.blksz  = queue_def->item_sz;
    cmpf.mpf    = (MPF_T*)queue_def->pool;
    cmpf.mpfmb  = NULL; // TODO: should we pass NULL to kernel?

    ER_ID mpfid = acre_mpf(&cmpf);
    if (mpfid <= 0) {
        return NULL;
    }

    auto queue_id = (osMailQId)malloc(sizeof(struct os_mailQ_cb));
    assert(queue_id != NULL);
    queue_id->qid = msg_queue_id;
    queue_id->mpf = mpfid;
    queue_id->bsz = queue_def->item_sz;

    return queue_id;
}

/// Allocate a memory block from a mail
void *osMailAlloc (osMailQId queue_id, uint32_t millisec) {
    assert(millisec < (1UL << (sizeof(TMO) * 8 - 1)) || millisec == osWaitForever); // FIXME: TMO is not unsigned!, TMO in Gen3 kernel is microseconds

    void *blk = NULL;

    ER ercd = tget_mpf(queue_id->mpf, &blk, C2T_TMO(millisec)); // FIXME: interrupt context is not supported yet
    // FIXME: handle exceptions

    return blk;
}

/// Allocate a memory block from a mail and set memory block to zero
void *osMailCAlloc (osMailQId queue_id, uint32_t millisec) {
    void *blk = osMailAlloc(queue_id, millisec);
    if (blk != NULL) memset(blk, 0, queue_id->bsz);
    return blk;
}

/// Free a memory block from a mail
osStatus osMailFree (osMailQId queue_id, void *mail) {
    ER ercd = rel_mpf(queue_id->mpf, mail); // FIXME: interrupt context is not supported yet
    // FIXME: handle exceptions
    return osOK;
}

/// Get a mail from a queue
os_InRegs osEvent osMailGet (osMailQId queue_id, uint32_t millisec) {
    //FIXME: check parameters
    osEvent ret;
    
    ret = osMessageGet(queue_id->qid, millisec);
    if (ret.status == osEventMessage) ret.status = osEventMail;
    
    return ret;
}

/// Put a mail to a queue
osStatus osMailPut (osMailQId queue_id, void *mail) {
    //FIXME: check parameters
    return osMessagePut(queue_id->qid, (uint32_t)mail, 0); // TODO: what about 64bit arch?
}

}
